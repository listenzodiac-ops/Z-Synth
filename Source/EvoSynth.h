#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include "SynthVoice.h"

namespace evo
{
// Synthesiser with a voice limit (4/6/8), mono and legato modes with a last-note-priority
// note stack, and portamento (glide) from the previously played note.
class EvoSynth : public juce::Synthesiser
{
public:
    explicit EvoSynth (const ParamPointers& params) : P (params) {}

    void noteOn (int midiChannel, int midiNoteNumber, float velocity) override
    {
        const juce::ScopedLock sl (lock);

        if (sounds.isEmpty() || voices.isEmpty())
            return;

        auto sound = sounds.getFirst();
        const int mode = (int) (P.voiceMode->load() + 0.5f);

        if (mode == modePoly)
        {
            noteStack.clear();
            const int limit = voiceLimit();

            // Same note struck again: release the old copy first.
            for (int i = 0; i < voices.size(); ++i)
                if (voices[i]->isVoiceActive() && voices[i]->getCurrentlyPlayingNote() == midiNoteNumber
                     && voices[i]->isPlayingChannel (midiChannel))
                    stopVoice (voices[i], 1.0f, true);

            auto* v = pickPolyVoice (limit);
            startWithGlide (v, sound.get(), midiChannel, midiNoteNumber, velocity);
            lastNote = midiNoteNumber;
            return;
        }

        // Mono / legato
        noteStack.removeFirstMatchingValue (midiNoteNumber);
        noteStack.add (midiNoteNumber);

        auto* v = dynamic_cast<EvolverVoice*> (voices[0]);
        if (v == nullptr)
            return;

        for (int i = 1; i < voices.size(); ++i)          // mono: only voice 0 sounds
            if (voices[i]->isVoiceActive())
                stopVoice (voices[i], 1.0f, false);

        const bool held = v->isVoiceActive() && v->isKeyDown();

        if (mode == modeLegato && held)
        {
            if (P.glide->load() > 0.5f)
                v->setGlideSource (-1.0f);   // glide continues from where the pitch currently is
            v->retarget (midiNoteNumber);
        }
        else
        {
            startWithGlide (v, sound.get(), midiChannel, midiNoteNumber, velocity);
        }

        lastNote = midiNoteNumber;
    }

    void noteOff (int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override
    {
        const juce::ScopedLock sl (lock);

        const int mode = (int) (P.voiceMode->load() + 0.5f);

        if (mode == modePoly || noteStack.isEmpty())
        {
            noteStack.clear();
            juce::Synthesiser::noteOff (midiChannel, midiNoteNumber, velocity, allowTailOff);
            return;
        }

        noteStack.removeFirstMatchingValue (midiNoteNumber);

        auto* v = dynamic_cast<EvolverVoice*> (voices[0]);
        if (v == nullptr)
            return;

        if (noteStack.isEmpty())
        {
            stopVoice (v, velocity, allowTailOff);
            return;
        }

        const int back = noteStack.getLast();    // fall back to the previous held note
        if (back == lastNote)
            return;

        if (mode == modeLegato)
            v->retarget (back);
        else if (auto sound = sounds.getFirst())
            startWithGlide (v, sound.get(), midiChannel, back, 0.8f);

        lastNote = back;
    }

    void allNotesOff (int midiChannel, bool allowTailOff) override
    {
        const juce::ScopedLock sl (lock);
        noteStack.clear();
        juce::Synthesiser::allNotesOff (midiChannel, allowTailOff);
    }

    int voiceLimit() const
    {
        static const int counts[3] = { 4, 6, 8 };
        return juce::jmin (voices.size(), counts[juce::jlimit (0, 2, (int) (P.voices->load() + 0.5f))]);
    }

private:
    void startWithGlide (juce::SynthesiserVoice* voice, juce::SynthesiserSound* sound, int ch, int note, float vel)
    {
        if (auto* ev = dynamic_cast<EvolverVoice*> (voice))
            ev->setGlideSource (lastNote >= 0 && P.glide->load() > 0.5f ? (float) lastNote : -1.0f);

        startVoice (voice, sound, ch, note, vel);
    }

    juce::SynthesiserVoice* pickPolyVoice (int limit)
    {
        for (int i = 0; i < limit; ++i)
            if (! voices[i]->isVoiceActive())
                return voices[i];

        // Steal: prefer a voice that is already releasing, otherwise the oldest one.
        juce::SynthesiserVoice* best = nullptr;
        bool bestReleasing = false;

        for (int i = 0; i < limit; ++i)
        {
            auto* v = voices[i];
            const bool releasing = ! v->isKeyDown();

            if (best == nullptr
                 || (releasing && ! bestReleasing)
                 || (releasing == bestReleasing && v->wasStartedBefore (*best)))
            {
                best = v;
                bestReleasing = releasing;
            }
        }
        return best;
    }

    const ParamPointers& P;
    juce::Array<int> noteStack;
    int lastNote = -1;
};
} // namespace evo
