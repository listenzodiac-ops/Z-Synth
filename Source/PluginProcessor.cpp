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
    presetFade.reset (sampleRate, 0.08);
    presetFade.setCurrentAndTargetValue (1.0f);
    seenPresetChanges = presets.changes.load();
    fadePhase = 0;
    resetEffects();
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

    if (numSamples <= 0)
        return;

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

    // ---- safety: nothing broken or enormous may reach the effects ---------------------------
    // Normal sound is well below 1.0 here and passes through untouched. A NaN, an infinity or an absurd
    // spike is removed, the voices are stopped and every effect tail is emptied, so a glitch can never
    // end up ringing in the delay or reverb.
    {
        bool glitch = false;
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* d = buffer.getWritePointer (ch);
            for (int i = 0; i < numSamples; ++i)
            {
                if (! (std::fabs (d[i]) < 1.0e4f))
                    glitch = true;
                d[i] = evo::softLimit (d[i]);
            }
        }

        if (glitch)
        {
            synth.allNotesOff (0, false);
            resetEffects();
        }
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

    // A preset was just loaded: duck to silence in 6 ms, empty every effect tail (so nothing from the old
    // sound can carry over), then fade the new sound in over 80 ms.
    const int presetChanges = presets.changes.load();
    if (presetChanges != seenPresetChanges)
    {
        seenPresetChanges = presetChanges;
        const float now = presetFade.getCurrentValue();
        presetFade.reset (sampleRateHz, 0.006);
        presetFade.setCurrentAndTargetValue (now);
        presetFade.setTargetValue (0.0f);
        fadePhase = 1;
    }

    bool broken = false;

    for (int i = 0; i < numSamples; ++i)
    {
        if (fadePhase == 1 && ! presetFade.isSmoothing())   // silent now: flush, then bring the new sound in
        {
            resetEffects();
            presetFade.reset (sampleRateHz, 0.08);
            presetFade.setCurrentAndTargetValue (0.0f);
            presetFade.setTargetValue (1.0f);
            fadePhase = 0;
        }

        const float gain = masterGain.getNextValue() * presetFade.getNextValue();
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* data = buffer.getWritePointer (ch);
            float out = std::tanh (data[i] * gain);
            if (! (std::fabs (out) <= 1.0f))   // NaN or infinity: never let it out
            {
                out = 0.0f;
                broken = true;
            }
            data[i] = out;
        }
    }

    if (broken)
    {
        synth.allNotesOff (0, false);
        resetEffects();
    }
}

void PolyEvolverAudioProcessor::resetEffects()
{
    distortion.reset();
    chorus.clear();
    delay.clear();
    reverb.reset();
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
    if (! juce::isPositiveAndBelow (index, (int) list.size()))
        return {};

    const auto& f = list[(size_t) index];
    return juce::String (f.category).isEmpty() ? juce::String (f.name) : juce::String (f.category) + ": " + f.name;   // e.g. "Bass: Velvet Reese"
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
