#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include "SynthVoice.h"
#include "EvoSynth.h"
#include "StereoDelay.h"
#include "Effects.h"
#include "Presets.h"

class PolyEvolverAudioProcessor : public juce::AudioProcessor
{
public:
    PolyEvolverAudioProcessor();
    ~PolyEvolverAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override  { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 6.0; }

    // Factory presets are exposed to the host as programs.
    int getNumPrograms() override { return (int) evo::factoryPresets().size(); }
    int getCurrentProgram() override { return currentProgram; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::String getPresetName() const { return apvts.state.getProperty ("presetName", "Init").toString(); }

    // Order matters: apvts must be constructed before 'params', 'presets' and 'synth'.
    juce::AudioProcessorValueTreeState apvts;
    juce::MidiKeyboardState keyboardState;   // (no on-screen keyboard any more, kept for MIDI merging)
    evo::PresetManager presets { apvts };

    std::atomic<float> hostBpm { 120.0f };   // for the LFO lamps in the editor
    std::atomic<int> currentStep { -1 };     // step being played, for the editor (-1 = sequencer idle)

private:
    evo::ParamPointers params;
    evo::SeqState seqState;                  // must be declared before 'synth' (voices point at it)
    evo::PerfState perfState;
    evo::EvoSynth synth { params };
    evo::Distortion distortion;
    evo::Chorus chorus;
    evo::StereoDelay delay;
    evo::SpaceReverb reverb;
    juce::SmoothedValue<float> masterGain;

    double sampleRateHz = 44100.0;
    double internalPpq  = 0.0;               // free-running clock used by the standalone app
    long long lastTick  = 0;
    bool   haveTick     = false;
    bool   prevStepOff  = false;
    int    currentProgram = 0;

    void applyStep (int step);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyEvolverAudioProcessor)
};
