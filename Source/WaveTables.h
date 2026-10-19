#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include <array>
#include <vector>

namespace evo
{
// Band-limited single-cycle wavetables for the "digital" oscillators, standing in
// for the Evolver's 128 digital waveforms. There are 128 waves, each built
// additively, and 7 octave-spaced bands so high notes use fewer harmonics
// (which avoids aliasing).
//
//   waves  0-3  : sine -> triangle-ish -> saw-ish (increasingly bright)
//   waves  4-7  : odd harmonics only (hollow, square-ish)
//   waves  8-11 : formant-like peaks moving up the spectrum
//   waves 12-15 : seeded pseudo-random harmonic spectra (metallic / bell-ish)
//   waves 16-23 : pulse waves, narrowing duty cycle
//   waves 24-31 : organ-style stacks of octaves and fifths
//   waves 32-39 : reedy, even-harmonic-heavy spectra
//   waves 40-47 : vowel-like double formants
//   waves 48-55 : bell / glass (stretched, sparse harmonics)
//   waves 56-63 : bright seeded random spectra
//   waves 64-71 : comb saws (every n-th harmonic missing)
//   waves 72-79 : narrow resonant peak sweeping up the spectrum
//   waves 80-87 : sub / octave-stack heavy
//   waves 88-95 : inharmonic metal bars
//   waves 96-103: clarinet-like (odd, with a boosted third)
//   waves 104-111: soft pads (dark random, random phase)
//   waves 112-119: pulse + saw blends
//   waves 120-127: glassy high clusters
class WaveTables
{
public:
    static constexpr int tableSize = 2048;
    static constexpr int numBands  = 7;      // max harmonics: 128, 64, 32, 16, 8, 4, 2
    static constexpr int maxHarmonics = 128;

    static const WaveTables& instance()
    {
        static const WaveTables tables;      // built once, shared by all plugin instances
        return tables;
    }

    // Each table has tableSize + 1 entries (extra guard sample for interpolation).
    const float* table (int band, int wave) const noexcept
    {
        return data.data() + (((size_t) band * numWaves) + (size_t) wave) * (tableSize + 1);
    }

    static int bandForFrequency (float freqHz, float sampleRate) noexcept
    {
        for (int b = 0; b < numBands; ++b)
            if ((float) (maxHarmonics >> b) * freqHz <= 0.45f * sampleRate)
                return b;

        return numBands - 1;
    }

private:
    WaveTables()
    {
        data.assign ((size_t) numBands * numWaves * (tableSize + 1), 0.0f);

        std::array<std::array<float, maxHarmonics + 1>, numWaves> amp {}, phase {};

        for (int w = 0; w < numWaves; ++w)
        {
            juce::Random rng (1000 + w);

            for (int h = 1; h <= maxHarmonics; ++h)
            {
                amp[(size_t) w][(size_t) h]   = recipeAmp (w, h, rng);
                phase[(size_t) w][(size_t) h] = (w >= 12 && (w < 16 || (w >= 48 && w < 64) || (w >= 104 && w < 112))) ? rng.nextFloat() * juce::MathConstants<float>::twoPi : 0.0f;
            }
        }

        // Build each wave from the smallest band upwards, adding harmonics as the
        // band widens (so every harmonic is synthesised only once per wave).
        std::vector<float> acc ((size_t) tableSize);

        for (int w = 0; w < numWaves; ++w)
        {
            std::fill (acc.begin(), acc.end(), 0.0f);
            int done = 0;

            for (int b = numBands - 1; b >= 0; --b)
            {
                const int maxH = maxHarmonics >> b;

                for (int h = done + 1; h <= maxH; ++h)
                {
                    const float a = amp[(size_t) w][(size_t) h];
                    if (a == 0.0f)
                        continue;

                    const float ph = phase[(size_t) w][(size_t) h];
                    const float step = juce::MathConstants<float>::twoPi * (float) h / (float) tableSize;

                    for (int n = 0; n < tableSize; ++n)
                        acc[(size_t) n] += a * std::sin (step * (float) n + ph);
                }
                done = maxH;

                float* t = data.data() + (((size_t) b * numWaves) + (size_t) w) * (tableSize + 1);

                float peak = 0.0f;
                for (int n = 0; n < tableSize; ++n)
                    peak = std::max (peak, std::abs (acc[(size_t) n]));

                const float norm = peak > 0.0f ? 1.0f / peak : 0.0f;
                for (int n = 0; n < tableSize; ++n)
                    t[n] = acc[(size_t) n] * norm;

                t[tableSize] = t[0];   // guard sample
            }
        }
    }

    static float recipeAmp (int w, int h, juce::Random& rng)
    {
        const float hf = (float) h;

        if (w < 4)   // sine -> saw-like
            return 1.0f / std::pow (hf, 3.0f - 0.55f * (float) w);

        if (w < 8)   // odd harmonics only
        {
            if ((h & 1) == 0)
                return 0.0f;

            return 1.0f / std::pow (hf, 2.0f - 0.4f * (float) (w - 4));
        }

        if (w < 12)  // moving formant peak
        {
            const float centre = 3.0f + 3.0f * (float) (w - 8);
            const float d = (hf - centre) / 1.5f;
            return 1.0f / std::pow (hf, 1.5f) + 0.9f * std::exp (-d * d) / std::sqrt (hf);
        }

        if (w < 16)  // random spectra
            return (0.3f + 0.7f * rng.nextFloat()) / hf;

        const float k = (float) ((w - 16) & 7);   // position within the group of eight

        if (w < 24)  // pulse waves: harmonic h has amplitude sin(pi h d) / h
        {
            const float duty = 0.5f - 0.055f * k;
            return std::abs (std::sin (juce::MathConstants<float>::pi * hf * duty)) / hf;
        }

        if (w < 32)  // organ: octave and fifth partials, drawbar-like
        {
            static const int partials[] { 1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128 };
            const int count = 3 + (int) k;
            for (int n = 0; n < count && n < 14; ++n)
                if (h == partials[n])
                    return 1.0f / (1.0f + 0.35f * (float) n);
            return 0.0f;
        }

        if (w < 40)  // reedy: even harmonics boosted, softer slope as k rises
        {
            const float slope = 1.6f - 0.12f * k;
            return ((h & 1) == 0 ? 1.0f : 0.45f) / std::pow (hf, slope);
        }

        if (w < 48)  // two formant peaks that move together
        {
            const float f1 = 2.0f + 0.9f * k, f2 = 7.0f + 2.2f * k;
            const float d1 = (hf - f1) / 1.2f, d2 = (hf - f2) / 1.8f;
            return 0.02f / hf + std::exp (-d1 * d1) + 0.6f * std::exp (-d2 * d2);
        }

        if (w < 56)  // bell / glass: sparse, stretched partials
        {
            const float stretch = 1.0f + 0.12f * k;
            const float x = hf / stretch;
            const bool hit = std::abs (x - std::round (x * 0.5f) * 2.0f) < 0.25f || h < 3;
            return hit ? 1.0f / std::pow (hf, 0.9f) : 0.0f;
        }

        if (w < 64)  // bright random spectra
            return (0.2f + 0.8f * rng.nextFloat()) / std::pow (hf, 0.45f + 0.06f * k);

        const float k2 = (float) ((w - 64) & 7);

        if (w < 72)  // comb saw
            return (h % ((int) k2 + 2) == 0) ? 0.0f : 1.0f / hf;

        if (w < 80)  // narrow resonant peak sweeping up
        {
            const float d = (hf - (2.0f + 4.0f * k2)) / 1.0f;
            return 1.0f / hf + 1.6f * std::exp (-d * d) / std::sqrt (hf);
        }

        if (w < 88)  // sub / octave stack
        {
            const bool pow2 = (h & (h - 1)) == 0;
            if (h == 1) return 1.0f;
            return pow2 ? (0.8f - 0.06f * k2) / std::sqrt (hf) : 0.12f / std::pow (hf, 1.2f + 0.1f * k2);
        }

        if (w < 96)  // inharmonic metal: partials at n^(1.5 + 0.1k)
        {
            const float e = 1.5f + 0.1f * k2;
            for (int n = 1; n < 40; ++n)
            {
                const float p = std::pow ((float) n, e);
                if (p > hf + 0.6f) break;
                if (std::abs (p - hf) < 0.55f) return 1.0f / std::pow (hf, 0.7f);
            }
            return 0.0f;
        }

        if (w < 104) // clarinet-ish: odd only, third boosted
        {
            if ((h & 1) == 0) return 0.0f;
            return (h % 3 == 0 ? 1.5f + 0.3f * k2 : 1.0f) / std::pow (hf, 1.2f);
        }

        if (w < 112) // soft pads: dark random, random phase
            return (0.4f + 0.6f * rng.nextFloat()) / std::pow (hf, 1.5f - 0.08f * k2);

        if (w < 120) // pulse + saw blend
        {
            const float duty = 0.45f - 0.05f * k2;
            return std::abs (std::sin (juce::MathConstants<float>::pi * hf * duty)) / hf + 0.5f / hf;
        }

        // glassy high clusters
        const float c = 4.0f + 6.0f * k2;
        const float d = (hf - c) / 2.0f;
        return (h == 1 ? 0.5f : 0.0f) + std::exp (-d * d) + 0.05f / hf;
    }

    std::vector<float> data;
};
} // namespace evo
