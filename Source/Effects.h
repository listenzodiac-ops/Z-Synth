#pragma once

#include <JuceHeader.h>
#include <vector>

namespace evo
{
// Distortion with four flavours and a dry/wet mix:
//   Soft  - tanh saturation (smooth overdrive / fuzz)
//   Hard  - hard clipping (harsher, buzzier)
//   Fold  - wavefolder (metallic, synthy harmonics that move as the level changes)
//   Crush - sample-rate reduction + bit reduction (lo-fi / downsampling); Drive sets how crushed it is
class Distortion
{
public:
    enum Type { soft = 0, hard, fold, crush };

    void process (float* left, float* right, int n, int type, float drive01, float mix)
    {
        if (mix <= 0.0001f)
        {
            prevL = left[n - 1]; prevR = right[n - 1];
            return;
        }

        if (type == crush)
        {
            // hold ratio 1..48 samples, bit depth 16..3 bits
            const float ratio  = std::exp (drive01 * std::log (48.0f));
            const float step   = 1.0f / ratio;
            const float levels = std::pow (2.0f, 16.0f - 13.0f * drive01) * 0.5f;

            for (int i = 0; i < n; ++i)
            {
                holdPhase += step;
                if (holdPhase >= 1.0f)
                {
                    holdPhase -= 1.0f;
                    heldL = std::round (left[i]  * levels) / levels;
                    heldR = std::round (right[i] * levels) / levels;
                }
                left[i]  += mix * (heldL - left[i]);
                right[i] += mix * (heldR - right[i]);
            }
            prevL = left[n - 1]; prevR = right[n - 1];
            return;
        }

        const float g    = 1.0f + drive01 * 24.0f;
        const float comp = type == fold ? 0.8f : 1.0f / (1.0f + drive01 * 1.6f);

        for (int i = 0; i < n; ++i)
        {
            const float l = left[i], r = right[i];

            const float wl = 0.5f * (shape (type, (prevL + l) * 0.5f, g) + shape (type, l, g)) * comp;
            const float wr = 0.5f * (shape (type, (prevR + r) * 0.5f, g) + shape (type, r, g)) * comp;

            prevL = l; prevR = r;
            left[i]  = l + mix * (wl - l);
            right[i] = r + mix * (wr - r);
        }
    }

private:
    static float shape (int type, float x, float g) noexcept
    {
        const float v = x * g;
        if (type == hard) return juce::jlimit (-1.0f, 1.0f, v);
        if (type == fold) return std::sin (v);
        return std::tanh (v);
    }

    float prevL = 0.0f, prevR = 0.0f, heldL = 0.0f, heldR = 0.0f, holdPhase = 0.0f;
};

// Stereo chorus: two modulated taps per channel, 90 degrees apart between channels.
class Chorus
{
public:
    void prepare (double sr)
    {
        sampleRate = (float) sr;
        len = (int) (sr * 0.06) + 8;
        for (auto& b : buffer) b.assign ((size_t) len, 0.0f);
        pos = 0;
        phase = 0.0f;
    }

    void process (float* left, float* right, int n, float rateHz, float depth01, float mix)
    {
        if (buffer[0].empty())
            return;

        const float inc = rateHz / sampleRate;

        for (int i = 0; i < n; ++i)
        {
            buffer[0][(size_t) pos] = left[i];
            buffer[1][(size_t) pos] = right[i];

            const float baseMs  = 12.0f;
            const float depthMs = 1.0f + depth01 * 7.0f;

            auto tap = [&] (int ch, float ph)
            {
                const float m = std::sin (juce::MathConstants<float>::twoPi * ph);
                return read (buffer[ch], (baseMs + depthMs * m) * 0.001f * sampleRate);
            };

            const float wl = 0.5f * (tap (0, phase)        + tap (0, phase + 0.5f));
            const float wr = 0.5f * (tap (1, phase + 0.25f) + tap (1, phase + 0.75f));

            left[i]  += mix * wl;
            right[i] += mix * wr;

            phase += inc;
            if (phase >= 1.0f) phase -= 1.0f;
            if (++pos >= len) pos = 0;
        }
    }

private:
    float read (const std::vector<float>& b, float delaySamples) const
    {
        delaySamples = juce::jlimit (1.0f, (float) (len - 2), delaySamples);
        float rp = (float) pos - delaySamples;
        if (rp < 0.0f) rp += (float) len;
        const int i0 = (int) rp;
        const float f = rp - (float) i0;
        const int i1 = (i0 + 1 >= len) ? 0 : i0 + 1;
        return b[(size_t) i0] + f * (b[(size_t) i1] - b[(size_t) i0]);
    }

    std::vector<float> buffer[2];
    float sampleRate = 44100.0f, phase = 0.0f;
    int len = 0, pos = 0;
};

// Large, wide, diffuse "space" reverb: stereo pre-delay -> 4 input allpass diffusers per side ->
// 8-line feedback delay network (Householder mix) with slowly modulated delay times, per-line
// damping and RT60-based decay. Left and right are fed into alternate lines and tapped from
// alternate lines, so the tail is very decorrelated (wide).
//   size : room scale and decay time (about 1.5 s up to 13 s)
//   damp : how fast the highs die away in the tail
class SpaceReverb
{
public:
    void prepare (double sr)
    {
        sampleRate = (float) sr;
        const float k = sampleRate / 44100.0f;

        for (int i = 0; i < N; ++i)
        {
            baseLen[i] = (float) lineBase[i] * k;
            lines[i].assign ((size_t) (baseLen[i] * 2.4f) + 64, 0.0f);
            pos[i] = 0;
            lp[i] = 0.0f;
            lfoPhase[i] = (float) i / (float) N;
        }

        for (int c = 0; c < 2; ++c)
        {
            pre[c].assign ((size_t) (sampleRate * 0.12f) + 8, 0.0f);
            prePos[c] = 0;

            for (int a = 0; a < 4; ++a)
            {
                const int len = (int) ((float) apLen[c][a] * k);
                ap[c][a].assign ((size_t) len, 0.0f);
                apPos[c][a] = 0;
            }
            hpState[c] = 0.0f;
        }
        active = false;
    }

    void process (float* left, float* right, int n, float size01, float damp01, float mix)
    {
        if (lines[0].empty())
            return;

        if (mix <= 0.0001f)
        {
            if (active) { clear(); active = false; }
            return;
        }
        active = true;

        const float scale   = 0.7f + 1.3f * size01;                 // delay-length scale
        const float rt60    = 1.5f + 11.5f * size01 * size01 + 2.0f * size01;
        const float dampC   = 1.0f - 0.88f * damp01;               // one-pole coefficient (1 = bright)
        const float preSmp  = sampleRate * (0.012f + 0.03f * size01);
        const float modDepth = 7.0f * sampleRate / 44100.0f;
        const float lfoInc  = 1.0f / sampleRate;
        const float hpC     = 1.0f - std::exp (-juce::MathConstants<float>::twoPi * 140.0f / sampleRate);

        float g[N], len[N];
        for (int i = 0; i < N; ++i)
        {
            len[i] = baseLen[i] * scale;
            g[i]   = std::pow (10.0f, -3.0f * len[i] / (rt60 * sampleRate));
        }

        for (int s = 0; s < n; ++s)
        {
            float in[2] = { left[s], right[s] };

            // gentle low cut into the tank so the tail stays clear
            for (int c = 0; c < 2; ++c)
            {
                hpState[c] += hpC * (in[c] - hpState[c]);
                in[c] -= hpState[c];

                // pre-delay
                pre[c][(size_t) prePos[c]] = in[c];
                in[c] = readLine (pre[c], prePos[c], preSmp);
                if (++prePos[c] >= (int) pre[c].size()) prePos[c] = 0;

                // input diffusion
                for (int a = 0; a < 4; ++a)
                {
                    auto& b = ap[c][a];
                    const float d = b[(size_t) apPos[c][a]];
                    const float v = in[c] - 0.6f * d;
                    b[(size_t) apPos[c][a]] = v;
                    in[c] = d + 0.6f * v;
                    if (++apPos[c][a] >= (int) b.size()) apPos[c][a] = 0;
                }
            }

            // read the tank
            float out[N], sum = 0.0f;
            for (int i = 0; i < N; ++i)
            {
                const float m = std::sin (juce::MathConstants<float>::twoPi * lfoPhase[i]);
                lfoPhase[i] += lfoInc * (0.17f + 0.043f * (float) i);
                if (lfoPhase[i] >= 1.0f) lfoPhase[i] -= 1.0f;

                float d = readLine (lines[i], pos[i], len[i] + m * modDepth);
                lp[i] += dampC * (d - lp[i]);
                out[i] = lp[i] * g[i];
                sum += out[i];
            }

            // Householder feedback matrix, injecting left into even lines and right into odd lines
            const float h = sum * (2.0f / (float) N);
            float wl = 0.0f, wr = 0.0f;
            for (int i = 0; i < N; ++i)
            {
                const float fb = out[i] - h;
                lines[i][(size_t) pos[i]] = fb + 0.35f * in[i & 1];
                if (++pos[i] >= (int) lines[i].size()) pos[i] = 0;

                // alternate taps with alternating signs for L and R
                if (i & 1) wr += (i & 2 ? -out[i] : out[i]);
                else       wl += (i & 2 ? -out[i] : out[i]);
            }

            left[s]  += mix * wl * 1.6f;
            right[s] += mix * wr * 1.6f;
        }
    }

private:
    static constexpr int N = 8;
    static constexpr int lineBase[N] = { 1423, 1637, 1891, 2113, 2347, 2593, 2819, 3067 };
    static constexpr int apLen[2][4] = { { 142, 107, 379, 277 }, { 151, 113, 359, 311 } };

    static float readLine (const std::vector<float>& b, int writePos, float delay) noexcept
    {
        const int size = (int) b.size();
        delay = juce::jlimit (1.0f, (float) (size - 2), delay);
        float rp = (float) writePos - delay;
        if (rp < 0.0f) rp += (float) size;
        const int i0 = (int) rp;
        const float f = rp - (float) i0;
        const int i1 = (i0 + 1 >= size) ? 0 : i0 + 1;
        return b[(size_t) i0] + f * (b[(size_t) i1] - b[(size_t) i0]);
    }

    void clear()
    {
        for (auto& b : lines) std::fill (b.begin(), b.end(), 0.0f);
        for (auto& b : pre)   std::fill (b.begin(), b.end(), 0.0f);
        for (auto& c : ap) for (auto& b : c) std::fill (b.begin(), b.end(), 0.0f);
        for (auto& v : lp) v = 0.0f;
        hpState[0] = hpState[1] = 0.0f;
    }

    std::vector<float> lines[N], pre[2], ap[2][4];
    int pos[N] {}, prePos[2] {}, apPos[2][4] {};
    float baseLen[N] {}, lp[N] {}, lfoPhase[N] {}, hpState[2] {};
    float sampleRate = 44100.0f;
    bool active = false;
};
} // namespace evo
