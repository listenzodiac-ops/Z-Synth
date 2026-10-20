#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include "WaveTables.h"

namespace evo
{
// ---------------------------------------------------------------------------
// Small DSP helpers
// ---------------------------------------------------------------------------

// PolyBLEP: cheap anti-aliasing correction for saw / pulse edges.
inline float polyBlep (float t, float dt) noexcept
{
    if (t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0f;
    }
    if (t > 1.0f - dt)
    {
        t = (t - 1.0f) / dt;
        return t * t + t + t + 1.0f;
    }
    return 0.0f;
}

// Rational tanh approximation, good enough for saturation and much cheaper.
inline float fastTanh (float x) noexcept
{
    x = juce::jlimit (-3.0f, 3.0f, x);
    const float x2 = x * x;
    return x * (27.0f + x2) / (27.0f + 9.0f * x2);
}

// Moog-style transistor-ladder lowpass: four one-pole stages with tanh
// saturation and global resonance feedback. Take the output from stage 2
// (12 dB/oct) or stage 4 (24 dB/oct), like the Evolver's 2-/4-pole switch.
struct LadderFilter
{
    void reset() noexcept
    {
        for (auto& v : y)  v = 0.0f;
        for (auto& v : ty) v = 0.0f;
    }

    void setCoefficients (float cutoffHz, float resonance01, float sampleRate) noexcept
    {
        g = 1.0f - std::exp (-juce::MathConstants<float>::twoPi * cutoffHz / sampleRate);
        k = resonance01 * 4.0f;   // k = 4 is about where it self-oscillates
    }

    float process (float in, float driveGain, bool fourPole) noexcept
    {
        const float x = fastTanh (in * driveGain - k * y[3]);

        y[0] += g * (x    - ty[0]);  ty[0] = fastTanh (y[0]);
        y[1] += g * (ty[0] - ty[1]); ty[1] = fastTanh (y[1]);
        y[2] += g * (ty[1] - ty[2]); ty[2] = fastTanh (y[2]);
        y[3] += g * (ty[2] - ty[3]); ty[3] = fastTanh (y[3]);

        return fourPole ? y[3] : y[1];
    }

    float y[4] {}, ty[4] {};
    float g = 0.1f, k = 0.0f;
};

// Very slow random wander (a fraction of a Hz), like temperature and supply drift in analog hardware.
// Picks a new random target every few seconds and glides to it. Output is about -1 .. +1.
struct Wander
{
    void seed (juce::Random& r, float secondsBetweenTargets) noexcept
    {
        period = secondsBetweenTargets;
        cur = r.nextFloat() * 2.0f - 1.0f;
        target = r.nextFloat() * 2.0f - 1.0f;
        timer = r.nextFloat() * period;
    }

    float next (juce::Random& r, float dtSeconds) noexcept
    {
        timer -= dtSeconds;
        if (timer <= 0.0f)
        {
            target = alternate ? (target >= 0.0f ? -1.0f : 1.0f) * (0.4f + 0.6f * r.nextFloat())   // always swings to the other side
                               : r.nextFloat() * 2.0f - 1.0f;
            timer = period * (0.6f + 0.8f * r.nextFloat());
        }
        cur += (1.0f - std::exp (-dtSeconds / (0.45f * period))) * (target - cur);
        return cur;
    }

    float cur = 0.0f, target = 0.0f, timer = 1.0f, period = 4.0f;
    bool alternate = false;
};

// Removes the DC the analog bias creates (one-pole high-pass, ~6 Hz).
struct DcBlocker
{
    float process (float x, float R) noexcept
    {
        const float y = x - x1 + R * y1;
        x1 = x; y1 = y;
        return y;
    }
    float x1 = 0.0f, y1 = 0.0f;
};

// Control-rate LFO (evaluated every few samples inside the voice).
struct Lfo
{
    void reset()
    {
        phase = 0.0f;
        held = rng.nextFloat() * 2.0f - 1.0f;
    }

    float next (int shape, float rateHz, int numSamples, float sampleRate)
    {
        float v = 0.0f;

        switch (shape)
        {
            case lfoSine:     v = std::sin (juce::MathConstants<float>::twoPi * phase); break;
            case lfoTriangle: v = 1.0f - 4.0f * std::abs (phase - 0.5f);               break;
            case lfoSaw:      v = 2.0f * phase - 1.0f;                                 break;
            case lfoSquare:   v = phase < 0.5f ? 1.0f : -1.0f;                         break;
            default:          v = held;                                                break;
        }

        phase += rateHz * (float) numSamples / sampleRate;

        if (phase >= 1.0f)
        {
            phase -= std::floor (phase);
            held = rng.nextFloat() * 2.0f - 1.0f;   // new sample for S&H
        }

        return v;
    }

    float phase = 0.0f, held = 0.0f;
    juce::Random rng;
};

// ---------------------------------------------------------------------------
// Sound + Voice
// ---------------------------------------------------------------------------
// Values the step sequencer is currently imposing on every voice. Written by the processor
// between audio segments, read by the voices; both run on the audio thread.
struct SeqState
{
    float pitch = 0.0f;       // semitones
    float cutoffOct = 0.0f;   // octaves
    float pan = 0.0f;         // -1 (left) .. +1 (right)
};

// Host / performance values shared by all voices (also audio thread only).
struct PerfState
{
    float bpm = 120.0f;
    float modWheel = 0.0f;     // 0..1 (MIDI CC1)
    float aftertouch = 0.0f;   // 0..1 (channel pressure)
    bool  seqMute = false;     // current sequencer step is switched off
};

class EvolverSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int) override    { return true; }
    bool appliesToChannel (int) override { return true; }
};

class EvolverVoice : public juce::SynthesiserVoice
{
public:
    EvolverVoice (const ParamPointers& params, const SeqState& seqState, const PerfState& perfState)
        : P (params), seq (seqState), perf (perfState), tables (WaveTables::instance()) {}

    // Restart both envelopes (used by the sequencer's gate mode on every step).
    void retrigger()
    {
        if (isVoiceActive() && isKeyDown())
        {
            ampEnv.noteOn();
            filterEnv.noteOn();
        }
    }

    // Release the envelopes without ending the note (sequencer steps that are switched off).
    void releaseEnvelopes()
    {
        if (isVoiceActive() && isKeyDown())
        {
            ampEnv.noteOff();
            filterEnv.noteOff();
        }
    }

    // The next startNote() glides up/down from this note number.
    void setGlideSource (float fromNote) noexcept { pendingGlideFrom = fromNote; }

    bool canPlaySound (juce::SynthesiserSound* s) override
    {
        return dynamic_cast<EvolverSound*> (s) != nullptr;
    }

    void setCurrentPlaybackSampleRate (double newRate) override
    {
        juce::SynthesiserVoice::setCurrentPlaybackSampleRate (newRate);
        sr = (float) newRate;
        ampEnv.setSampleRate (newRate);
        filterEnv.setSampleRate (newRate);
        wPitch[0].seed (rng, 5.0f); wPitch[1].seed (rng, 6.5f);
        wCut.seed (rng, 4.0f); wPol.seed (rng, 3.5f); wPol.alternate = true; wShape.seed (rng, 5.5f);
        dcCoef = std::exp (-juce::MathConstants<float>::twoPi * 6.0f / sr);
        smoothCoef = 1.0f - std::exp (-(float) controlRate / (sr * 0.012f));
        muteCoef   = 1.0f - std::exp (-1.0f / (sr * 0.003f));
    }

    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int pitchWheel) override
    {
        note = midiNoteNumber;
        vel = velocity;
        bendNorm = (float) (pitchWheel - 8192) / 8192.0f;
        noteRandom = rng.nextFloat() * 2.0f - 1.0f;

        // component tolerances: every note and every voice is a hair different, like real analog circuits
        tolTune = rng.nextFloat() * 2.0f - 1.0f;
        tolCut  = rng.nextFloat() * 2.0f - 1.0f;
        tolBias = rng.nextFloat() * 2.0f - 1.0f;
        biasRamp = 0.0f;

        // Free-running-style random start phases for the analog oscillators.
        for (int o = 0; o < numOscs; ++o)
            phase[o] = 0.0f;

        for (int o = 0; o < 2; ++o)
            for (int u = 0; u < maxUnison; ++u)
                uPhase[o][u] = rng.nextFloat();

        for (auto& l : lfos)
            l.reset();

        // Don't reset the filter if this voice is being re-used while still ringing (avoids clicks).
        const bool wasRinging = ampEnv.isActive();
        if (! wasRinging)
        {
            filter.reset(); filterR.reset();
            prevInL = prevInR = 0.0f;
            needsInit = true;
        }

        readBlockParams();

        if (pendingGlideFrom >= 0.0f && snap.glideMs > 0.5f)
            curNoteF = pendingGlideFrom;
        else
            curNoteF = (float) note;
        pendingGlideFrom = -1.0f;

        lastFilterEnv = 0.0f;
        lastAmpEnv = 0.0f;
        muteG = perf.seqMute ? 0.0f : 1.0f;
        modW = perf.modWheel;
        aftert = perf.aftertouch;
        digOut[0] = digOut[1] = 0.0f;
        controlCounter = 0;

        ampEnv.noteOn();
        filterEnv.noteOn();
    }

    void stopNote (float, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            ampEnv.noteOff();
            filterEnv.noteOff();
        }
        else
        {
            ampEnv.reset();
            filterEnv.reset();
            clearCurrentNote();
        }
    }

    void pitchWheelMoved (int newValue) override
    {
        bendNorm = (float) (newValue - 8192) / 8192.0f;
    }

    void controllerMoved (int, int) override {}

    void renderNextBlock (juce::AudioBuffer<float>& buffer, int startSample, int numSamples) override
    {
        if (! isVoiceActive())
            return;

        readBlockParams();

        float* left  = buffer.getWritePointer (0, startSample);
        float* right = buffer.getNumChannels() > 1 ? buffer.getWritePointer (1, startSample) : nullptr;

        for (int i = 0; i < numSamples; ++i)
        {
            if ((controlCounter++ & (controlRate - 1)) == 0)
                updateControl();

            const float aenv = ampEnv.getNextSample();
            lastAmpEnv       = aenv;
            lastFilterEnv    = filterEnv.getNextSample();

            if (! ampEnv.isActive())
            {
                clearCurrentNote();
                break;
            }

            // --- oscillators ---------------------------------------------------
            float mixL = 0.0f, mixR = 0.0f;

            // Analog oscillators 1 and 2: each is a stack of 1-7 unison voices; osc 2 can be hard-synced to osc 1
            bool  syncHit  = false;
            float syncFrac = 0.0f;

            for (int o = 0; o < 2; ++o)
            {
                if (curLevel[o] <= 0.0001f && ! (o == 0 && snap.sync))
                    continue;

                const int n = snap.uni[o];

                for (int u = 0; u < n; ++u)
                {
                    if (o == 1 && syncHit)
                        uPhase[1][u] = syncFrac * uDt[1][u];

                    const float s = analogSample (uPhase[o][u], uDt[o][u], curShape[o]);

                    uPhase[o][u] += uDt[o][u];
                    if (uPhase[o][u] >= 1.0f)
                    {
                        uPhase[o][u] -= 1.0f;
                        if (o == 0 && u == 0 && snap.sync)
                        {
                            syncHit  = true;
                            syncFrac = uPhase[0][0] / uDt[0][0];   // how far past the wrap we already are
                        }
                    }

                    mixL += s * curLevel[o] * uGL[o][u];
                    mixR += s * curLevel[o] * uGR[o][u];
                }
            }

            // Digital oscillators 3 and 4, with phase-modulation FM between them.
            // An oscillator that is silent in the mix still runs if it is modulating the other one.
            const bool run3 = curLevel[2] > 0.0001f || curFm34 > 0.0001f || curRing > 0.0001f;
            const bool run4 = curLevel[3] > 0.0001f || curFm43 > 0.0001f || curRing > 0.0001f;

            if (run3)
            {
                const float pm = fmDepth (curFm43) * digOut[1];
                digOut[0] = digitalSample (wrap01 (phase[2] + pm), curShape[2], band[2]);

                phase[2] += dt[2];
                if (phase[2] >= 1.0f)
                    phase[2] -= 1.0f;

                mixL += digOut[0] * curLevel[2] * oscGainL[2];
                mixR += digOut[0] * curLevel[2] * oscGainR[2];
            }
            else
                digOut[0] = 0.0f;

            if (run4)
            {
                const float pm = fmDepth (curFm34) * digOut[0];
                digOut[1] = digitalSample (wrap01 (phase[3] + pm), curShape[3], band[3]);

                phase[3] += dt[3];
                if (phase[3] >= 1.0f)
                    phase[3] -= 1.0f;

                mixL += digOut[1] * curLevel[3] * oscGainL[3];
                mixR += digOut[1] * curLevel[3] * oscGainR[3];
            }
            else
                digOut[1] = 0.0f;

            if (curRing > 0.0001f)   // ring modulation: osc 3 x osc 4, straight to the mix
            {
                const float rm = curRing * 1.2f * digOut[0] * digOut[1];
                mixL += rm;
                mixR += rm;
            }

            if (effNoise > 0.0001f)   // white noise, same level in both channels
            {
                const float nz = (rng.nextFloat() * 2.0f - 1.0f) * effNoise;
                mixL += nz;
                mixR += nz;
            }

            mixL *= 0.3f;   // headroom for up to four oscillators at full level
            mixR *= 0.3f;

            // --- filter + amp. One ladder per channel so each oscillator can sit anywhere in the
            // stereo field; each ladder runs twice per sample (2x oversampled) for a cleaner, more stable
            // resonance and drive.
            muteG += muteCoef * ((perf.seqMute ? 0.0f : 1.0f) - muteG);
            const float envGain = aenv * ampGain * (0.25f + 0.75f * vel) * muteG;

            float outL = ladder2x (filter,  dcL, prevInL, mixL);
            float outR = ladder2x (filterR, dcR, prevInR, mixR);
            outL *= envGain;
            outR *= envGain;


            left[i] += outL * panL;
            if (right != nullptr)
                right[i] += outR * panR;
        }
    }

private:
    static constexpr int controlRate = 16;   // modulation updates every 16 samples (power of two)

    // Parameter values copied once per audio block.
    struct Snapshot
    {
        float noise = 0.0f, ring = 0.0f;
        bool  sync = false;
        int   uni[2] { 1, 1 };
        float uniDet[2] {};
        float pan[numOscs] {}, level[numOscs] {}, semi[numOscs] {}, fine[numOscs] {}, shape[numOscs] {};
        float fm43 = 0.0f, fm34 = 0.0f;
        float cutoff = 1000.0f, res = 0.0f, envAmt = 0.0f, keyTrack = 0.0f, driveGain = 1.0f;
        bool  fourPole = true;
        float lfoRate[numLfos] {}, lfoAmt[numLfos] {};
        int   lfoShape[numLfos] {}, lfoDest[numLfos] {}, lfoSync[numLfos] {};
        int   mmSrc[numSlots] {}, mmDst[numSlots] {};
        float mmAmt[numSlots] {};
        float glideMs = 0.0f, bendRange = 2.0f;
    };

    void readBlockParams()
    {
        for (int o = 0; o < numOscs; ++o)
        {
            snap.level[o] = P.oscLevel[o]->load();
            snap.pan[o]   = P.oscPan[o]->load();
            snap.semi [o] = P.oscSemi [o]->load();
            snap.fine [o] = P.oscFine [o]->load();
            snap.shape[o] = P.oscShape[o]->load();
        }

        snap.fm43      = P.fm43->load();
        snap.fm34      = P.fm34->load();
        snap.noise     = P.noise->load();
        snap.ring      = P.ring->load();
        snap.sync      = P.sync->load() > 0.5f;
        for (int o = 0; o < 2; ++o)
        {
            snap.uni   [o] = juce::jlimit (1, maxUnison, juce::roundToInt (P.oscUni[o]->load()));
            snap.uniDet[o] = P.oscUniDet[o]->load();
        }
        snap.cutoff    = P.cutoff->load();
        snap.res       = P.resonance->load();
        snap.envAmt    = P.filterEnv->load();
        snap.keyTrack  = P.keyTrack->load();
        snap.driveGain = 1.5f;   // fixed input drive into the ladder
        snap.fourPole  = P.poles->load() > 0.5f;
        snap.glideMs   = P.glide->load();
        snap.bendRange = P.bendRange->load();

        for (int l = 0; l < numLfos; ++l)
        {
            snap.lfoRate [l] = P.lfoRate[l]->load();
            snap.lfoAmt  [l] = P.lfoAmount[l]->load();
            snap.lfoShape[l] = (int) (P.lfoShape[l]->load() + 0.5f);
            snap.lfoDest [l] = (int) (P.lfoDest[l]->load() + 0.5f);
            snap.lfoSync [l] = juce::jlimit (0, numSyncDivisions - 1, (int) (P.lfoSync[l]->load() + 0.5f));
        }

        for (int m = 0; m < numSlots; ++m)
        {
            snap.mmSrc[m] = juce::jlimit (0, (int) numSrc - 1, (int) (P.mmSrc[m]->load() + 0.5f));
            snap.mmDst[m] = juce::jlimit (0, (int) numDst - 1, (int) (P.mmDst[m]->load() + 0.5f));
            snap.mmAmt[m] = P.mmAmt[m]->load();
        }

        ampEnv.setParameters    ({ P.ampA->load(), P.ampD->load(), P.ampS->load(), P.ampR->load() });
        filterEnv.setParameters ({ P.fltA->load(), P.fltD->load(), P.fltS->load(), P.fltR->load() });
    }

    float ladder2x (LadderFilter& f, DcBlocker& dc, float& prevIn, float in) noexcept
    {
        const float mid = 0.5f * (prevIn + in);
        prevIn = in;
        const float a = f.process (mid + biasNow, curDrive, snap.fourPole);
        const float b = f.process (in  + biasNow, curDrive, snap.fourPole);
        float y = 0.5f * (a + b);
        y += asymNow * y * y;   // even-order term: top and bottom of the wave are no longer mirror images
        return dc.process (y, dcCoef) * polComp;
    }

    static float lerpTo (float cur, float target, float c) noexcept { return cur + c * (target - cur); }

    // Runs every 'controlRate' samples: smoothing, LFOs, mod matrix, pitch, shapes, filter coefficients.
    void updateControl()
    {
        const float sm = smoothCoef;

        // ---- parameter smoothing (one pole, ~12 ms) so knobs never zipper ------------------
        if (needsInit)
        {
            for (int o = 0; o < numOscs; ++o) { curLevel[o] = snap.level[o]; curPan[o] = snap.pan[o]; }
            curNoise = snap.noise;  curRes = snap.res;  curDrive = snap.driveGain;
            curFm43Base = snap.fm43; curFm34Base = snap.fm34; curRingBase = snap.ring;
            curDet[0] = snap.uniDet[0]; curDet[1] = snap.uniDet[1];
            curCutLog = std::log2 (snap.cutoff);
            needsInit = false;
        }
        else
        {
            for (int o = 0; o < numOscs; ++o)
            {
                curLevel[o] = lerpTo (curLevel[o], snap.level[o], sm);
                curPan  [o] = lerpTo (curPan  [o], snap.pan  [o], sm);
            }
            curNoise = lerpTo (curNoise, snap.noise, sm);
            curRes   = lerpTo (curRes,   snap.res,   sm);
            curDrive = lerpTo (curDrive, snap.driveGain, sm);
            curFm43Base = lerpTo (curFm43Base, snap.fm43, sm);
            curFm34Base = lerpTo (curFm34Base, snap.fm34, sm);
            curRingBase = lerpTo (curRingBase, snap.ring, sm);
            curDet[0] = lerpTo (curDet[0], snap.uniDet[0], sm);
            curDet[1] = lerpTo (curDet[1], snap.uniDet[1], sm);
            curCutLog = lerpTo (curCutLog, std::log2 (snap.cutoff), sm);
        }

        // ---- glide -----------------------------------------------------------------
        if (snap.glideMs > 0.5f)
        {
            const float tau = snap.glideMs * 0.001f / 3.0f;
            const float c = 1.0f - std::exp (-(float) controlRate / (sr * tau));
            curNoteF = lerpTo (curNoteF, (float) note, c);
            if (std::abs (curNoteF - (float) note) < 0.001f) curNoteF = (float) note;
        }
        else
            curNoteF = (float) note;

        modW   = lerpTo (modW,   perf.modWheel,   0.25f);
        aftert = lerpTo (aftert, perf.aftertouch, 0.25f);

        // ---- LFOs (classic fixed destinations) -----------------------------------------
        float pitchMod = 0.0f, shapeMod = 0.0f, cutoffMod = 0.0f, ampAcc = 0.0f;
        float resMod = 0.0f, panMod = 0.0f, fmMod = 0.0f, ringMod = 0.0f;
        float lfoVal[numLfos] {};

        for (int l = 0; l < numLfos; ++l)
        {
            // Always advance, so an LFO keeps its phase even when its destination is "Off".
            float rate = snap.lfoRate[l];
            if (snap.lfoSync[l] > 0)   // tempo sync: cycles per second = beats per second / beats per cycle
                rate = (perf.bpm / 60.0f) / (float) syncBeats[snap.lfoSync[l]];

            const float v = lfos[(size_t) l].next (snap.lfoShape[l], rate, controlRate, sr);
            lfoVal[l] = v;
            const float a = snap.lfoAmt[l] * v;

            switch (snap.lfoDest[l])
            {
                case destPitch:      pitchMod  += a * 12.0f;            break;   // up to +/- 1 octave
                case destOscShape:   shapeMod  += a * 0.5f;             break;
                case destCutoff:     cutoffMod += a * 3.0f;             break;   // octaves
                case destReso:       resMod    += a * 0.5f;             break;
                case destPan:        panMod    += a;                    break;
                case destFM:         fmMod     += a * 0.5f;             break;
                case destRing:       ringMod   += a * 0.5f;             break;
                case destAmp:        ampAcc    += snap.lfoAmt[l] * 0.5f * (v - 1.0f); break;   // tremolo
                default: break;
            }
        }

        // ---- modulation matrix -----------------------------------------------------------
        float srcVal[numSrc] {};
        srcVal[srcLfo1]       = lfoVal[0];
        srcVal[srcLfo2]       = lfoVal[1];
        srcVal[srcFiltEnv]    = lastFilterEnv;
        srcVal[srcAmpEnv]     = lastAmpEnv;
        srcVal[srcVelocity]   = vel;
        srcVal[srcModWheel]   = modW;
        srcVal[srcAftertouch] = aftert;
        srcVal[srcKey]        = juce::jlimit (-1.0f, 1.0f, ((float) note - 60.0f) / 48.0f);
        srcVal[srcRandom]     = noteRandom;

        float dst[numDst] {};
        for (int m = 0; m < numSlots; ++m)
            if (snap.mmSrc[m] != srcOff && snap.mmDst[m] != dstOff)
                dst[snap.mmDst[m]] += srcVal[snap.mmSrc[m]] * snap.mmAmt[m];

        pitchMod  += dst[dstPitch] * 12.0f;
        cutoffMod += dst[dstCutoff] * 4.0f;
        resMod    += dst[dstReso] * 0.5f;
        panMod    += dst[dstPan];
        fmMod     += dst[dstFM] * 0.5f;
        ringMod   += dst[dstRing] * 0.5f;
        ampAcc    += dst[dstAmp] * 0.5f;

        effNoise = juce::jlimit (0.0f, 1.0f, curNoise + dst[dstNoise] * 0.5f);

        // ---- analog character: slow drift + wandering polarity ---------------------------
        analogAmt = lerpTo (analogAmt, P.analog->load(), sm);
        const float an  = analogAmt;
        const float dts = (float) controlRate / sr;
        const float wp0 = wPitch[0].next (rng, dts), wp1 = wPitch[1].next (rng, dts);
        const float wc  = wCut.next (rng, dts), wpol = wPol.next (rng, dts), wsh = wShape.next (rng, dts);

        cutoffMod += an * (0.12f * wc + 0.06f * tolCut);

        // The polarity: a small DC offset ahead of the filter that slowly wanders between positive and negative.
        // The saturating filter then clips the top and bottom of the wave differently (even harmonics = thicker,
        // warmer), and the lean slowly swings up and down. The DC itself is blocked again after the filter.
        biasRamp = lerpTo (biasRamp, 1.0f, 0.004f);   // fades in over ~0.1 s so note starts do not thump
        const float biasTarget = an * (0.90f * wpol + 0.15f * tolBias + 0.10f);
        biasNow = biasTarget * biasRamp;
        asymNow = juce::jlimit (-0.5f, 0.5f, biasTarget * 0.9f) * biasRamp;
        polComp = 1.0f / (1.0f + 0.9f * std::abs (asymNow) + 0.35f * std::abs (biasNow));   // keep the loudness about the same

        // ---- pitch and shapes ----------------------------------------------------------
        const float baseNote = curNoteF + bendNorm * snap.bendRange + pitchMod + seq.pitch;

        for (int o = 0; o < numOscs; ++o)
        {
            const float drift = an * (o < 2 ? 0.07f : 0.03f) * ((o & 1) ? wp1 : wp0) + an * 0.03f * tolTune * (float) (o + 1) * 0.25f;
            const float semis = baseNote + snap.semi[o] + snap.fine[o] / 100.0f + drift;
            const float freq  = juce::jlimit (8.0f, 0.45f * sr, 440.0f * std::exp2 ((semis - 69.0f) / 12.0f));

            dt[o]       = freq / sr;
            const float own = (o < 2 ? dst[dstShape] : dst[dstWave]) * 0.5f;
            curShape[o] = juce::jlimit (0.0f, 1.0f, snap.shape[o] + shapeMod + own + (o < 2 ? an * 0.03f * wsh : 0.0f));

            if (o >= 2)
                band[o] = WaveTables::bandForFrequency (freq, sr);
        }

        // Unison: detune the stack symmetrically around the note and fan it out across the stereo field.
        for (int o = 0; o < 2; ++o)
        {
            const int   n    = snap.uni[o];
            const float norm = 1.0f / std::sqrt ((float) n);
            const float det  = juce::jlimit (0.0f, 1.0f, curDet[o] + dst[dstDetune] * 0.5f);

            for (int u = 0; u < n; ++u)
            {
                const float pos = n > 1 ? 2.0f * (float) u / (float) (n - 1) - 1.0f : 0.0f;
                uDt[o][u] = juce::jmin (0.45f, dt[o] * std::exp2 (pos * det * 60.0f / 1200.0f));

                const float p = juce::jlimit (-1.0f, 1.0f, curPan[o] + pos * det);
                const float a = (p + 1.0f) * juce::MathConstants<float>::pi * 0.25f;
                uGL[o][u] = std::cos (a) * 1.41421356f * norm;
                uGR[o][u] = std::sin (a) * 1.41421356f * norm;
            }
        }

        curFm43 = juce::jlimit (0.0f, 1.0f, curFm43Base + fmMod);
        curFm34 = juce::jlimit (0.0f, 1.0f, curFm34Base + fmMod);
        curRing = juce::jlimit (0.0f, 1.0f, curRingBase + ringMod);

        // ---- filter ------------------------------------------------------------------------
        const float octaves = snap.envAmt * 5.0f * lastFilterEnv
                            + snap.keyTrack * ((float) note - 60.0f) / 12.0f
                            + cutoffMod + seq.cutoffOct;

        const float fc  = juce::jlimit (20.0f, 0.45f * sr, std::exp2 (curCutLog + octaves));
        const float res = juce::jlimit (0.0f, 1.0f, curRes + resMod);
        filter.setCoefficients  (fc, res, sr * 2.0f);   // the ladder runs at 2x the sample rate
        filterR.setCoefficients (fc, res, sr * 2.0f);

        for (int o = 0; o < numOscs; ++o)   // equal-power per-oscillator pan (centre = unity gain)
        {
            const float a = (juce::jlimit (-1.0f, 1.0f, curPan[o]) + 1.0f) * juce::MathConstants<float>::pi * 0.25f;
            oscGainL[o] = std::cos (a) * 1.41421356f;
            oscGainR[o] = std::sin (a) * 1.41421356f;
        }

        ampGain = juce::jlimit (0.0f, 1.5f, 1.0f + ampAcc);

        // equal-power pan (centre = unity gain on both sides)
        const float angle = (juce::jlimit (-1.0f, 1.0f, seq.pan + panMod) + 1.0f) * juce::MathConstants<float>::pi * 0.25f;
        panL = std::cos (angle) * 1.41421356f;
        panR = std::sin (angle) * 1.41421356f;
    }

    // FM depth in cycles of phase offset: squared so the low end of the knob is subtle.
    static float fmDepth (float amount) noexcept   { return amount * amount * 2.0f; }

    static float wrap01 (float t) noexcept
    {
        t -= std::floor (t);
        return t >= 1.0f ? 0.0f : t;
    }

    // Analog-style osc: shape 0 = sine, 1/3 = triangle, 2/3 = saw, 1 = square (crossfaded in between).
    static float analogSample (float t, float dtv, float shape) noexcept
    {
        const float saw = 2.0f * t - 1.0f - polyBlep (t, dtv);
        const float tri = 1.0f - 4.0f * std::abs (t - 0.5f);

        // 50% square wave (no DC offset)
        float pulse = (t < 0.5f) ? 1.0f : -1.0f;
        pulse += polyBlep (t, dtv);
        pulse -= polyBlep (std::fmod (t + 0.5f, 1.0f), dtv);

        const float sine = std::sin (juce::MathConstants<float>::twoPi * t);
        const float pos = juce::jlimit (0.0f, 1.0f, shape) * 3.0f;

        if (pos < 1.0f) return sine * (1.0f - pos) + tri * pos;
        if (pos < 2.0f) return tri * (2.0f - pos) + saw * (pos - 1.0f);
        return saw * (3.0f - pos) + pulse * (pos - 2.0f);
    }

    // Digital osc: shape sweeps (and crossfades) through the wavetable bank.
    float digitalSample (float t, float shape, int b) const noexcept
    {
        const float pos = juce::jlimit (0.0f, 1.0f, shape) * (float) (numWaves - 1);
        const int w0 = (int) pos;
        const int w1 = std::min (w0 + 1, numWaves - 1);
        const float wf = pos - (float) w0;

        const float idx = t * (float) WaveTables::tableSize;
        const int i0 = (int) idx;
        const float f = idx - (float) i0;

        const float* t0 = tables.table (b, w0);
        const float* t1 = tables.table (b, w1);

        const float a = t0[i0] + f * (t0[i0 + 1] - t0[i0]);
        const float c = t1[i0] + f * (t1[i0 + 1] - t1[i0]);
        return a + wf * (c - a);
    }

    const ParamPointers& P;
    const SeqState& seq;
    const PerfState& perf;
    const WaveTables& tables;
    float panL = 1.0f, panR = 1.0f;

    juce::ADSR ampEnv, filterEnv;
    LadderFilter filter, filterR;
    float prevInL = 0.0f, prevInR = 0.0f;
    float oscGainL[numOscs] { 1.0f, 1.0f, 1.0f, 1.0f }, oscGainR[numOscs] { 1.0f, 1.0f, 1.0f, 1.0f };
    Lfo lfos[numLfos];
    juce::Random rng;
    Snapshot snap;

    float sr = 44100.0f, smoothCoef = 0.02f, muteCoef = 0.01f, muteG = 1.0f;
    int note = 60;
    float vel = 1.0f, bendNorm = 0.0f, noteRandom = 0.0f;
    float lastFilterEnv = 0.0f, lastAmpEnv = 0.0f, ampGain = 1.0f;
    float curNoteF = 60.0f, pendingGlideFrom = -1.0f;
    float modW = 0.0f, aftert = 0.0f;
    unsigned int controlCounter = 0;

    // smoothed copies of the knob values
    bool  needsInit = true;
    float curLevel[numOscs] {}, curPan[numOscs] {};
    float curNoise = 0.0f, effNoise = 0.0f, curRes = 0.0f, curDrive = 1.0f;
    float curFm43Base = 0.0f, curFm34Base = 0.0f, curRingBase = 0.0f;
    float curDet[2] {};
    float curCutLog = 10.0f;

    // analog character: slow drift, per-voice tolerances, and a wandering polarity (DC bias) before the filter
    Wander wPitch[2], wCut, wPol, wShape;
    DcBlocker dcL, dcR;
    float analogAmt = 0.0f;            // smoothed knob value
    float tolTune = 0.0f, tolCut = 0.0f, tolBias = 0.0f;   // fixed per note
    float polComp = 1.0f, biasNow = 0.0f, biasRamp = 0.0f, asymNow = 0.0f, dcCoef = 0.999f;

    float uPhase[2][maxUnison] {}, uDt[2][maxUnison] {}, uGL[2][maxUnison] {}, uGR[2][maxUnison] {};
    float curFm43 = 0.0f, curFm34 = 0.0f, curRing = 0.0f;
    float digOut[2] {};   // last output of osc 3 and osc 4 (used as FM modulators)
    float phase[numOscs] {}, dt[numOscs] {}, curShape[numOscs] {};
    int band[numOscs] {};
};
} // namespace evo
