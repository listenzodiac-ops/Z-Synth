#pragma once

#include <JuceHeader.h>

// All parameter IDs, enums and the pointer cache the voices use to read
// parameters from the audio thread.
namespace evo
{
constexpr int numOscs   = 4;    // osc 1-2: analog-style, osc 3-4: digital wavetable
constexpr int numLfos   = 2;
constexpr int maxUnison = 7;    // unison voices per analog oscillator
constexpr int numVoices = 8;    // voices created; the "Voices" parameter limits how many are used
constexpr int numWaves  = 128;  // waves in the digital wavetable bank
constexpr int numSlots  = 4;    // modulation matrix slots
constexpr int numSteps  = 16;   // sequencer steps

enum LfoDest  { destOff = 0, destPitch, destOscShape, destCutoff, destReso, destAmp, destPan, destFM, destRing };
enum LfoShape { lfoSine = 0, lfoTriangle, lfoSaw, lfoSquare, lfoSampleHold };

// Modulation matrix sources and destinations (the order matches the choice lists in Params.cpp).
enum MatSrc { srcOff = 0, srcLfo1, srcLfo2, srcFiltEnv, srcAmpEnv, srcVelocity, srcModWheel, srcAftertouch, srcKey, srcRandom, numSrc };
enum MatDst { dstOff = 0, dstPitch, dstShape, dstWave, dstCutoff, dstReso, dstAmp, dstPan, dstFM, dstRing, dstNoise, dstDetune, numDst };

enum VoiceMode { modePoly = 0, modeMono, modeLegato };
enum SeqDir    { dirForward = 0, dirBackward, dirPendulum, dirRandom };

// Tempo-sync note lengths in quarter notes. Index 0 means "free" (Hz / ms), used by the LFOs and the delay.
inline constexpr int numSyncDivisions = 13;
inline constexpr double syncBeats[numSyncDivisions] = { 0.0, 4.0, 2.0, 1.0, 0.5, 0.25, 0.125, 2.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0, 1.5, 0.75, 0.375 };

inline constexpr int numSeqRates = 6;
inline constexpr double seqRateBeats[numSeqRates] = { 1.0, 0.5, 0.25, 0.125, 1.0 / 3.0, 1.0 / 6.0 };   // 1/4, 1/8, 1/16, 1/32, 1/8T, 1/16T

inline juce::String oscID (int i, const char* name) { return "osc" + juce::String (i + 1) + "_" + name; }
inline juce::String lfoID (int i, const char* name) { return "lfo" + juce::String (i + 1) + "_" + name; }
inline juce::String mmID  (int i, const char* name) { return "mm" + juce::String (i + 1) + "_" + name; }

struct ParamPointers
{
    std::atomic<float>* oscLevel[numOscs] {};
    std::atomic<float>* oscSemi [numOscs] {};
    std::atomic<float>* oscFine [numOscs] {};  std::atomic<float>* oscPan [numOscs] {};
    std::atomic<float>* oscShape[numOscs] {};
    std::atomic<float>* oscUni   [2] {};     // unison voices (analog oscs)
    std::atomic<float>* oscUniDet[2] {};     // unison detune / stereo spread

    std::atomic<float>* fm43       = nullptr;   // osc 4 -> osc 3 FM amount
    std::atomic<float>* fm34       = nullptr;   // osc 3 -> osc 4 FM amount
    std::atomic<float>* noise      = nullptr;   // white noise level
    std::atomic<float>* sync       = nullptr;   // osc 2 hard-synced to osc 1
    std::atomic<float>* ring       = nullptr;   // ring modulation, osc 3 x osc 4

    std::atomic<float>* cutoff     = nullptr;
    std::atomic<float>* resonance  = nullptr;
    std::atomic<float>* poles      = nullptr;   // 0 = 2-pole, 1 = 4-pole
    std::atomic<float>* filterEnv  = nullptr;
    std::atomic<float>* keyTrack   = nullptr;

    std::atomic<float>* fltA = nullptr; std::atomic<float>* fltD = nullptr;
    std::atomic<float>* fltS = nullptr; std::atomic<float>* fltR = nullptr;
    std::atomic<float>* ampA = nullptr; std::atomic<float>* ampD = nullptr;
    std::atomic<float>* ampS = nullptr; std::atomic<float>* ampR = nullptr;

    std::atomic<float>* lfoRate [numLfos] {};
    std::atomic<float>* lfoSync [numLfos] {};   // 0 = free, otherwise a tempo division
    std::atomic<float>* lfoShape[numLfos] {};
    std::atomic<float>* lfoAmount[numLfos] {};
    std::atomic<float>* lfoDest [numLfos] {};

    std::atomic<float>* mmSrc[numSlots] {};
    std::atomic<float>* mmDst[numSlots] {};
    std::atomic<float>* mmAmt[numSlots] {};

    // voice handling
    std::atomic<float>* voices    = nullptr;   // 0 = 4, 1 = 6, 2 = 8 voices
    std::atomic<float>* voiceMode = nullptr;   // poly / mono / legato
    std::atomic<float>* glide     = nullptr;   // ms
    std::atomic<float>* bendRange = nullptr;   // semitones

    // effects
    std::atomic<float>* distDrive = nullptr;  std::atomic<float>* distMix = nullptr;  std::atomic<float>* distType = nullptr;
    std::atomic<float>* chRate = nullptr;     std::atomic<float>* chDepth = nullptr;   std::atomic<float>* chMix = nullptr;
    std::atomic<float>* delayTime = nullptr;  std::atomic<float>* delaySync = nullptr;
    std::atomic<float>* delayFeedback = nullptr;
    std::atomic<float>* delayTone = nullptr;
    std::atomic<float>* delayMix = nullptr;
    std::atomic<float>* rvSize = nullptr;     std::atomic<float>* rvDamp = nullptr;    std::atomic<float>* rvMix = nullptr;

    // step sequencer
    std::atomic<float>* seqOn   = nullptr;
    std::atomic<float>* seqGate = nullptr;   // retrigger envelopes on every step
    std::atomic<float>* seqRate = nullptr;
    std::atomic<float>* seqDest = nullptr;   // which lane the 16 knobs edit: 0 = pitch, 1 = cutoff, 2 = pan
    std::atomic<float>* seqLength = nullptr; // 1 - 16 steps
    std::atomic<float>* seqDir = nullptr;
    std::atomic<float>* seqSwing = nullptr;
    std::atomic<float>* seqStepOn[numSteps] {};
    std::atomic<float>* seqPitch [numSteps] {};
    std::atomic<float>* seqCutoff[numSteps] {};
    std::atomic<float>* seqPan   [numSteps] {};

    std::atomic<float>* analog = nullptr;   // 0 = clean digital, 1 = full analog drift / polarity wander
    std::atomic<float>* master = nullptr;
};

juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
void bindPointers (juce::AudioProcessorValueTreeState& apvts, ParamPointers& p);

// Names shared between the parameter layout and the preset code.
juce::StringArray syncNames();
} // namespace evo
