#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SeqLogic.h"

PolyEvolverAudioProcessor::PolyEvolverAudioProcessor()
    : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "STATE", evo::createLayout())
{
    evo::bindPointers (apvts, params);

    synth.addSound (new evo::EvolverSound());

    for (int i = 0; i < evo::numVoices; ++i)
        synth.addVoice (new evo::EvolverVoice (params, seqState, perfState));

    synth.setNoteStealingEnabled (true);
}

void PolyEvolverAudioProcessor::prepareToPlay (double sampleRate, int)
{
    sampleRateHz = sampleRate;
    synth.setCurrentPlaybackSampleRate (sampleRate);
    chorus.prepare (sampleRate);
    delay.prepare (sampleRate);
    reverb.prepare (sampleRate);
    masterGain.reset (sampleRate, 0.02);
    masterGain.setCurrentAndTargetValue (juce::Decibels::decibelsToGain (params.master->load()));
    haveTick = false;
    seqState = {};
    perfState.seqMute = false;
}

bool PolyEvolverAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void PolyEvolverAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;

    const int numSamples = buffer.getNumSamples();
    buffer.clear();

    // Merge notes played on the on-screen keyboard into the host's MIDI stream.
    keyboardState.processNextMidiBuffer (midi, 0, numSamples, true);

    // Mod wheel (CC1) and aftertouch are read from the incoming MIDI and shared with every voice.
    for (const auto meta : midi)
    {
        const auto m = meta.getMessage();
        if (m.isController() && m.getControllerNumber() == 1)
            perfState.modWheel = (float) m.getControllerValue() / 127.0f;
        else if (m.isChannelPressure())
            perfState.aftertouch = (float) m.getChannelPressureValue() / 127.0f;
        else if (m.isAftertouch())
            perfState.aftertouch = (float) m.getAfterTouchValue() / 127.0f;
        else if (m.isAllNotesOff() || m.isAllSoundOff())
            perfState.aftertouch = 0.0f;
    }

    // ---- tempo / transport ------------------------------------------------------------
    bool   playing = false;
    double ppq0 = 0.0, bpm = 120.0;

    if (auto* ph = getPlayHead())
        if (auto pos = ph->getPosition())
        {
            if (auto b = pos->getBpm())
                bpm = juce::jlimit (20.0, 400.0, *b);

            if (pos->getIsPlaying())
                if (auto p = pos->getPpqPosition())
                {
                    ppq0 = *p;
                    playing = true;
                }
        }

    perfState.bpm = (float) bpm;
    hostBpm.store ((float) bpm);

    // ---- step sequencer ---------------------------------------------------------------
    // Locks to the host: it runs while the DAW is playing and follows its tempo and position.
    // The standalone app has no host, so it uses an internal 120 BPM clock instead.
    bool seqRunning = false;

    if (params.seqOn->load() > 0.5f)
    {
        if (playing)
            seqRunning = true;
        else if (wrapperType == wrapperType_Standalone)
        {
            ppq0 = internalPpq;
            seqRunning = true;
        }
    }

    if (seqRunning)
    {
        const double spq   = sampleRateHz * 60.0 / bpm;                  // samples per quarter note
        const double stepQ = evo::seqRateBeats[juce::jlimit (0, evo::numSeqRates - 1, (int) (params.seqRate->load() + 0.5f))];
        const int    len   = juce::jlimit (1, evo::numSteps, juce::roundToInt (params.seqLength->load()));
        const int    dir   = (int) (params.seqDir->load() + 0.5f);
        const float  swing = params.seqSwing->load();
        const bool   gate  = params.seqGate->load() > 0.5f;

        int s = 0;
        while (s < numSamples)
        {
            const double ppq = ppq0 + (double) s / spq;
            const auto   tick = evo::seq::tickAt (ppq, stepQ, swing);

            if (! haveTick || tick.k != lastTick)
            {
                haveTick = true;
                lastTick = tick.k;

                const int step = evo::seq::stepForTick (tick.k, len, dir);
                const bool stepOn = params.seqStepOn[step]->load() > 0.5f;

                applyStep (step);
                currentStep.store (step);
                perfState.seqMute = ! stepOn;

                if (stepOn && (gate || prevStepOff))
                    for (int v = 0; v < synth.getNumVoices(); ++v)
                        if (auto* voice = dynamic_cast<evo::EvolverVoice*> (synth.getVoice (v)))
                            voice->retrigger();

                prevStepOff = ! stepOn;
            }

            // render up to the next step boundary so steps change on the exact sample
            const int toBoundary = juce::jmax (1, (int) std::ceil ((tick.nextBoundary - ppq) * spq - 1.0e-6));
            const int n          = juce::jmin (numSamples - s, toBoundary);

            synth.renderNextBlock (buffer, midi, s, n);
            s += n;
        }

        if (wrapperType == wrapperType_Standalone && ! playing)
            internalPpq += (double) numSamples / spq;
    }
    else
    {
        if (haveTick)
        {
            haveTick = false;
            prevStepOff = false;
            seqState = {};
            perfState.seqMute = false;
            currentStep.store (-1);
        }

        synth.renderNextBlock (buffer, midi, 0, numSamples);
    }

    // ---- effects: distortion -> chorus -> delay -> reverb --------------------------------
    if (buffer.getNumChannels() >= 2)
    {
        auto* l = buffer.getWritePointer (0);
        auto* r = buffer.getWritePointer (1);

        distortion.process (l, r, numSamples, (int) (params.distType->load() + 0.5f), params.distDrive->load(), params.distMix->load());
        chorus.process (l, r, numSamples, params.chRate->load(), params.chDepth->load(), params.chMix->load());

        float delayMs = params.delayTime->load();
        const int syncIdx = juce::jlimit (0, evo::numSyncDivisions - 1, (int) (params.delaySync->load() + 0.5f));
        if (syncIdx > 0)
            delayMs = (float) juce::jlimit (10.0, 2000.0, 60000.0 / bpm * evo::syncBeats[syncIdx]);

        delay.process (l, r, numSamples, delayMs, params.delayFeedback->load(),
                       params.delayTone->load(), params.delayMix->load());

        reverb.process (l, r, numSamples, params.rvSize->load(), params.rvDamp->load(), params.rvMix->load());
    }

    // Master volume + soft clip so a loud patch can't blast your ears or speakers.
    masterGain.setTargetValue (juce::Decibels::decibelsToGain (params.master->load()));

    for (int i = 0; i < numSamples; ++i)
    {
        const float gain = masterGain.getNextValue();
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* data = buffer.getWritePointer (ch);
            data[i] = std::tanh (data[i] * gain);
        }
    }
}

void PolyEvolverAudioProcessor::applyStep (int step)
{
    // All three lanes are always active; the "Lane" selector in the editor only chooses which one the knobs edit.
    seqState.pitch     = (float) juce::roundToInt (params.seqPitch[step]->load() * 12.0f);   // +/- 12 semitones
    seqState.cutoffOct = params.seqCutoff[step]->load() * 3.0f;                              // +/- 3 octaves
    seqState.pan       = params.seqPan[step]->load();                                        // -1 .. +1
}

void PolyEvolverAudioProcessor::setCurrentProgram (int index)
{
    currentProgram = index;
    presets.loadFactory (index);
}

const juce::String PolyEvolverAudioProcessor::getProgramName (int index)
{
    const auto& list = evo::factoryPresets();
    return juce::isPositiveAndBelow (index, (int) list.size()) ? juce::String (list[(size_t) index].name) : juce::String();
}

juce::AudioProcessorEditor* PolyEvolverAudioProcessor::createEditor()
{
    return new PolyEvolverAudioProcessorEditor (*this);
}

void PolyEvolverAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary (*xml, destData);
}

void PolyEvolverAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolyEvolverAudioProcessor();
}
