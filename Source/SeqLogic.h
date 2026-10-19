#pragma once

#include <cmath>
#include <cstdint>
#include <algorithm>

// Pure sequencer timing / ordering helpers (no JUCE), so they can be unit-tested offline.
namespace evo::seq
{
struct Tick
{
    long long k;            // global tick counter (floor-based, may be negative before the song start)
    double nextBoundary;    // ppq position where the next tick starts
};

// Maps a ppq position to a tick number. 'swing' (0..1) delays every odd tick:
// the pair of steps keeps its total length, the first gets longer and the second shorter.
inline Tick tickAt (double ppq, double stepQ, float swing)
{
    const double sw   = (double) swing * 0.5;
    const double pairLen = 2.0 * stepQ;
    const double pair = std::floor (ppq / pairLen);
    const double within = ppq - pair * pairLen;
    const double firstLen = stepQ * (1.0 + sw);
    const long long base = (long long) pair * 2;

    if (within < firstLen)
        return { base, pair * pairLen + firstLen };

    return { base + 1, (pair + 1.0) * pairLen };
}

inline uint32_t hash32 (uint32_t x)
{
    x ^= x >> 16; x *= 0x7feb352dU; x ^= x >> 15; x *= 0x846ca68bU; x ^= x >> 16;
    return x;
}

inline long long posMod (long long a, long long m) { return ((a % m) + m) % m; }

// dir: 0 forward, 1 backward, 2 pendulum, 3 random. Returns a step index in [0, length).
inline int stepForTick (long long k, int length, int dir)
{
    length = std::max (1, std::min (16, length));
    if (length == 1) return 0;

    switch (dir)
    {
        case 1:  return length - 1 - (int) posMod (k, length);
        case 2:
        {
            const int period = 2 * length - 2;
            const int m = (int) posMod (k, period);
            return m < length ? m : period - m;
        }
        case 3:  return (int) (hash32 ((uint32_t) (k & 0xffffffffLL)) % (uint32_t) length);
        default: return (int) posMod (k, length);
    }
}
} // namespace evo::seq
