#pragma once

#include <JuceHeader.h>
#include <vector>

namespace evo
{
#ifdef EVO_LIMIT_PROBE
inline int evoLimitHits = 0;   // test builds only: counts how often the safety limiter actually acts
#endif

// Transparent up to 2.0 (far above anything the synth makes on purpose, factory presets peak at about 1.5
// in the loudest case), then rolls off smoothly towards 3.0. It sits ahead of the effects and inside their
// feedback loops, so no glitch can ever park a huge level in a delay line or the reverb and keep it ringing
// for seconds. NaN / infinity / absurd values become 0.
inline float softLimit (float x) noexcept
{
    const float a = std::fabs (x);
    if (a <= 2.0f)
        return x;
#ifdef EVO_LIMIT_PROBE
    ++evoLimitHits;
#endif
    if (! (a < 1.0e6f))
        return 0.0f;
    const float y = 2.0f + std::tanh (a - 2.0f);
    return x < 0.0f ? -y : y;
}

// Simple stereo feedback delay. The right channel runs slightly longer than the
// left so a mono signal gets a wide, bouncing echo. A one-pole lowpass in the
// feedback path darkens each repeat (like the Evolver's analog-flavoured delay).
class StereoDelay
{
public:
    void prepare (double newSampleRate)
    {
        sampleRate = (float) newSampleRate;
        const int len = (int) (newSampleRate * 2.6) + 8;   // up to 2 s * 1.25 + margin

        for (auto& b : buffer)
            b.assign ((size_t) len, 0.0f);

        writePos = 0;
        lowpass[0] = lowpass[1] = 0.0f;
        time.reset (newSampleRate, 0.05);
        time.setCurrentAndTargetValue (300.0f);
    }

    void clear()
    {
        for (auto& b : buffer)
            std::fill (b.begin(), b.end(), 0.0f);
        lowpass[0] = lowpass[1] = 0.0f;
    }

    void process (float* left, float* right, int numSamples,
                  float timeMs, float feedback, float toneHz, float mix)
    {
        if (buffer[0].empty())
            return;

        time.setTargetValue (timeMs);

        const float a = std::exp (-juce::MathConstants<float>::twoPi * toneHz / sampleRate);
        const int len = (int) buffer[0].size();

        for (int i = 0; i < numSamples; ++i)
        {
            const float delaySamples = time.getNextValue() * 0.001f * sampleRate;

            const float wetL = read (buffer[0], delaySamples);
            const float wetR = read (buffer[1], delaySamples * 1.25f);

            lowpass[0] = (1.0f - a) * wetL + a * lowpass[0];
            lowpass[1] = (1.0f - a) * wetR + a * lowpass[1];

            buffer[0][(size_t) writePos] = softLimit (left[i]  + lowpass[0] * feedback);
            buffer[1][(size_t) writePos] = softLimit (right[i] + lowpass[1] * feedback);

            left[i]  += lowpass[0] * mix;
            right[i] += lowpass[1] * mix;

            if (++writePos >= len)
                writePos = 0;
        }
    }

private:
    float read (const std::vector<float>& b, float delaySamples) const
    {
        const int len = (int) b.size();
        delaySamples = juce::jlimit (1.0f, (float) (len - 2), delaySamples);

        float rp = (float) writePos - delaySamples;
        if (rp < 0.0f)
            rp += (float) len;

        const int i0 = (int) rp;
        const float frac = rp - (float) i0;
        const int i1 = (i0 + 1 >= len) ? 0 : i0 + 1;

        return b[(size_t) i0] + frac * (b[(size_t) i1] - b[(size_t) i0]);
    }

    std::vector<float> buffer[2];
    juce::SmoothedValue<float> time { 300.0f };
    float lowpass[2] { 0.0f, 0.0f };
    float sampleRate = 44100.0f;
    int writePos = 0;
};
} // namespace evo
