#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include <vector>
#include <utility>

namespace evo
{
// Factory presets are written as "change these parameters from their defaults" lists, so a
// preset never leaves stale values behind from the previous sound. Values are in real units
// (Hz, ms, semitones, choice index...). The skin and master volume are never touched.
struct FactoryPreset
{
    const char* category;   // folder in the preset menu ("" = top level)
    const char* name;
    std::vector<std::pair<const char*, float>> values;
};

inline const std::vector<FactoryPreset>& factoryPresets()
{
    static const std::vector<FactoryPreset> list = {
        { "", "Init", {} },

        // ------------------------------------------------------------ Bass
        { "Bass", "Velvet Reese", {
            { "osc1_level", 0.704f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -10.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.704f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 10.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1706.0f }, { "resonance", 0.12f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.31f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.22f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.1f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Deep Reese", {
            { "osc1_level", 0.614f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -14.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.675f }, { "osc2_shape", 0.6667f }, { "osc2_semi", -12.0f }, { "osc2_fine", 14.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 835.7f }, { "resonance", 0.1f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.553f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.15f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.12f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Silk Saw Bass", {
            { "osc1_level", 1.0f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -4.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 1.0f }, { "osc2_shape", 0.6667f }, { "osc2_semi", -12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1341.0f }, { "resonance", 0.18f }, { "poles", 1.0f },
            { "filter_env", 0.45f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.35f }, { "flt_sustain", 0.25f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.35f }, { "amp_sustain", 0.8f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.4f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Wide Reese", {
            { "osc1_level", 0.635f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -9.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.22f }, { "osc2_level", 0.635f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 9.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.22f }, { "cutoff", 1950.0f }, { "resonance", 0.1f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.18f },
            { "voice_mode", 0.0f }, { "glide", 0.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.28f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.18f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.08f }, { "lfo1_dest", 3.0f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.45f }, { "chorus_mix", 0.25f },
            { "osc4_level", 0.0f } } },

        { "Bass", "Moon Reese", {
            { "osc1_level", 0.94f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -12.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.94f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 12.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1132.0f }, { "resonance", 0.3f }, { "poles", 0.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f },
            { "voice_mode", 1.0f }, { "glide", 45.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.414f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.09f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.16f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Rolling Saw", {
            { "osc1_level", 0.828f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -8.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.828f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 8.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1828.0f }, { "resonance", 0.16f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.365f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.05f }, { "lfo1_sync", 4.0f }, { "lfo1_shape", 1.0f },
            { "lfo1_amount", 0.2f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Pulse Saw Bass", {
            { "osc1_level", 0.675f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -7.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.607f }, { "osc2_shape", 0.93f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 2194.0f }, { "resonance", 0.14f }, { "poles", 1.0f },
            { "filter_env", 0.25f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.297f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.3f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.07f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Fifth Reese", {
            { "osc1_level", 0.692f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -9.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.692f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 9.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1828.0f }, { "resonance", 0.12f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.305f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.2f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.09f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.305f }, { "osc4_shape", 0.1f }, { "osc4_semi", 7.0f },
            { "osc4_fine", -4.0f } } },

        { "Bass", "Sidewinder", {
            { "osc1_level", 0.787f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -11.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.787f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 11.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1592.0f }, { "resonance", 0.18f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.35f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.346f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.05f }, { "lfo1_sync", 3.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.22f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Tape Reese", {
            { "osc1_level", 0.412f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -13.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.412f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 13.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 2194.0f }, { "resonance", 0.1f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.181f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.12f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.08f }, { "lfo1_dest", 3.0f }, { "dist_type", 0.0f }, { "dist_drive", 0.18f }, { "dist_mix", 0.22f },
            { "chorus_rate", 0.35f }, { "chorus_depth", 0.45f }, { "chorus_mix", 0.3f }, { "osc4_level", 0.0f } } },

        { "Bass", "Glass Reese", {
            { "osc1_level", 0.66f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -9.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.66f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 9.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 2438.0f }, { "resonance", 0.15f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.264f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.2f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.09f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.29f }, { "osc4_shape", 0.9f }, { "osc4_semi", 0.0f },
            { "osc4_fine", 3.0f } } },

        { "Bass", "Mono Glide Saw", {
            { "osc1_level", 0.945f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -5.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.945f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1950.0f }, { "resonance", 0.22f }, { "poles", 1.0f },
            { "filter_env", 0.4f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 95.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.416f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Dub Saw", {
            { "osc1_level", 0.995f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -6.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.995f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1463.0f }, { "resonance", 0.28f }, { "poles", 1.0f },
            { "filter_env", 0.55f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.55f }, { "flt_sustain", 0.2f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.45f },
            { "voice_mode", 0.0f }, { "glide", 0.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.696f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.38f }, { "delay_tone", 1800.0f },
            { "delay_mix", 0.16f }, { "osc4_level", 0.0f } } },

        { "Bass", "Pluck Saw Bass", {
            { "osc1_level", 1.0f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -3.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 1.0f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1584.0f }, { "resonance", 0.22f }, { "poles", 1.0f },
            { "filter_env", 0.5f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.15f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.45f }, { "amp_sustain", 0.15f }, { "amp_release", 0.12f },
            { "voice_mode", 0.0f }, { "glide", 0.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.6f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Sub Saw", {
            { "osc1_level", 0.497f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -5.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.497f }, { "osc2_shape", 0.6667f }, { "osc2_semi", -12.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 682.1f }, { "resonance", 0.08f }, { "poles", 0.0f },
            { "filter_env", 0.0f }, { "key_track", 0.3f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.607f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Mellow Reese", {
            { "osc1_level", 0.5f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -8.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.5f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 8.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 661.6f }, { "resonance", 0.05f }, { "poles", 0.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.01f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.4f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.12f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.06f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Reese Drone", {
            { "osc1_level", 0.605f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -15.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.18f }, { "osc2_level", 0.605f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 15.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.18f }, { "cutoff", 1584.0f }, { "resonance", 0.14f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.35f }, { "amp_decay", 0.3f }, { "amp_sustain", 1.0f }, { "amp_release", 0.9f },
            { "voice_mode", 0.0f }, { "glide", 0.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.424f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.07f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.18f }, { "lfo1_dest", 3.0f }, { "voices", 0.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Neuro Light", {
            { "osc1_level", 0.69f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -12.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 0.69f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 12.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 2072.0f }, { "resonance", 0.32f }, { "poles", 1.0f },
            { "filter_env", 0.0f }, { "key_track", 0.4f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.304f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.05f }, { "lfo1_sync", 5.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.24f }, { "lfo1_dest", 3.0f }, { "dist_type", 0.0f }, { "dist_drive", 0.2f }, { "dist_mix", 0.22f },
            { "lfo2_rate", 0.3f }, { "lfo2_amount", 0.06f }, { "lfo2_dest", 4.0f }, { "lfo2_shape", 0.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Hollow Reese", {
            { "osc1_level", 1.0f }, { "osc1_shape", 0.3333f }, { "osc1_semi", 0.0f }, { "osc1_fine", -10.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 1.0f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 10.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 2240.0f }, { "resonance", 0.42f }, { "poles", 0.0f },
            { "filter_env", 0.0f }, { "key_track", 0.5f }, { "flt_attack", 0.003f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.3f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 30.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.4f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "lfo1_rate", 0.16f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.1f }, { "lfo1_dest", 3.0f }, { "osc4_level", 0.0f } } },

        { "Bass", "Rubber Saw", {
            { "osc1_level", 1.0f }, { "osc1_shape", 0.6667f }, { "osc1_semi", 0.0f }, { "osc1_fine", -4.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_level", 1.0f }, { "osc2_shape", 0.6667f }, { "osc2_semi", 0.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "cutoff", 1485.0f }, { "resonance", 0.34f }, { "poles", 1.0f },
            { "filter_env", 0.55f }, { "key_track", 0.3f }, { "flt_attack", 0.003f }, { "flt_decay", 0.28f }, { "flt_sustain", 0.35f },
            { "flt_release", 0.2f }, { "amp_attack", 0.004f }, { "amp_decay", 0.25f }, { "amp_sustain", 0.9f }, { "amp_release", 0.12f },
            { "voice_mode", 1.0f }, { "glide", 60.0f }, { "bend_range", 2.0f }, { "osc3_level", 0.44f }, { "osc3_shape", 0.0f },
            { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "mm2_src", 5.0f }, { "mm2_dst", 4.0f }, { "mm2_amt", 0.25f },
            { "osc4_level", 0.0f } } },


        // ------------------------------------------------------------ Pad
        { "Pad", "Juno Haze", {
            { "cutoff", 2400.0f }, { "resonance", 0.12f }, { "poles", 1.0f }, { "filter_env", 0.15f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.6f },
            { "amp_decay", 0.8f }, { "amp_sustain", 0.85f }, { "amp_release", 1.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.411f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.24f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.5f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f },
            { "reverb_size", 0.55f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.25f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Soft Ensemble", {
            { "cutoff", 1800.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 2.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.399f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.254f }, { "osc2_semi", 0.0f }, { "osc2_fine", -5.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.15f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.45f },
            { "reverb_size", 0.65f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Honey Pad", {
            { "cutoff", 1500.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.25f }, { "key_track", 0.5f },
            { "flt_attack", 0.8f }, { "flt_decay", 1.2f }, { "flt_sustain", 0.55f }, { "flt_release", 2.0f }, { "amp_attack", 1.0f },
            { "amp_decay", 1.2f }, { "amp_sustain", 0.85f }, { "amp_release", 2.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.5f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.22f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.3f }, { "osc2_semi", 12.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.0f }, { "osc3_level", 0.25f }, { "osc3_semi", -12.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.35f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.6f }, { "reverb_mix", 0.3f }, { "osc4_level", 0.0f } } },

        { "Pad", "Sunday Morning", {
            { "cutoff", 2600.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 2.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.406f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.185f }, { "osc2_semi", 12.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.8504f }, { "osc3_level", 0.222f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "reverb_size", 0.7f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.35f }, { "osc4_level", 0.0f } } },

        { "Pad", "Warm Blanket", {
            { "cutoff", 1100.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.4f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.358f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 4.0f },
            { "osc1_unidet", 0.28f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.358f }, { "osc2_semi", -12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 4.0f }, { "osc2_unidet", 0.28f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.6f },
            { "reverb_size", 0.8f }, { "reverb_damp", 0.55f }, { "reverb_mix", 0.35f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Analog Breath", {
            { "cutoff", 1800.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 2.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.446f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.22f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.365f }, { "osc2_semi", 0.0f }, { "osc2_fine", 8.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.22f }, { "lfo1_rate", 0.2f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.12f }, { "lfo1_dest", 3.0f }, { "lfo2_rate", 0.13f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.25f }, { "lfo2_dest", 6.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.35f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "noise_level", 0.032f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Pad", "Velvet Cloud", {
            { "cutoff", 1300.0f }, { "resonance", 0.12f }, { "poles", 0.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.6f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.282f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.35f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.198f }, { "osc2_semi", 0.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.25f }, { "osc4_shape", 0.8268f }, { "osc4_level", 0.141f }, { "osc4_semi", -12.0f },
            { "osc4_fine", 0.0f }, { "osc4_pan", 0.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.5f },
            { "reverb_size", 0.85f }, { "reverb_damp", 0.55f }, { "reverb_mix", 0.4f }, { "osc3_level", 0.0f } } },

        { "Pad", "Amber", {
            { "cutoff", 1700.0f }, { "resonance", 0.18f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 2.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.55f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.3f }, { "osc2_semi", 7.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.55f }, { "chorus_mix", 0.4f },
            { "delay_sync", 11.0f }, { "delay_feedback", 0.35f }, { "delay_tone", 2500.0f }, { "delay_mix", 0.12f }, { "reverb_size", 0.65f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Ensemble Strings", {
            { "cutoff", 3200.0f }, { "resonance", 0.08f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.6f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.45f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.95f }, { "amp_release", 0.9f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.32f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 7.0f },
            { "osc1_unidet", 0.22f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.256f }, { "osc2_semi", 0.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 5.0f }, { "osc2_unidet", 0.3f }, { "lfo2_rate", 5.3f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.012f }, { "lfo2_dest", 1.0f }, { "chorus_rate", 0.5f }, { "chorus_depth", 0.8f }, { "chorus_mix", 0.55f },
            { "reverb_size", 0.55f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.25f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Chamber Pad", {
            { "cutoff", 2600.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.6f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.55f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.402f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.15f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.322f }, { "osc2_semi", 0.0f }, { "osc2_fine", -6.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.15f }, { "osc3_shape", 0.2598f }, { "osc3_level", 0.161f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "lfo2_rate", 5.0f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.01f }, { "lfo2_dest", 1.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.25f }, { "osc4_level", 0.0f } } },

        { "Pad", "Solina Dream", {
            { "cutoff", 3800.0f }, { "resonance", 0.05f }, { "poles", 1.0f }, { "filter_env", 0.05f }, { "key_track", 0.6f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.7f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 1.4f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.349f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 7.0f },
            { "osc1_unidet", 0.35f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.174f }, { "osc2_semi", 12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 7.0f }, { "osc2_unidet", 0.35f }, { "chorus_rate", 0.6f }, { "chorus_depth", 0.9f }, { "chorus_mix", 0.65f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Slow Strings", {
            { "cutoff", 2200.0f }, { "resonance", 0.08f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.6f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.6f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 2.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.269f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.242f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 5.0f }, { "osc2_unidet", 0.25f }, { "lfo2_rate", 5.1f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.01f }, { "lfo2_dest", 1.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f },
            { "reverb_size", 0.7f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "String Machine", {
            { "cutoff", 3000.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.6f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.3f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 0.7f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.333f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.199f }, { "osc2_semi", 12.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.5f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f },
            { "reverb_size", 0.45f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Silk Section", {
            { "cutoff", 2000.0f }, { "resonance", 0.12f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.55f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.8f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.95f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.365f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.256f }, { "osc2_semi", 12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.25f }, { "osc3_shape", 0.0315f }, { "osc3_level", 0.146f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.45f },
            { "reverb_size", 0.7f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc4_level", 0.0f } } },

        { "Pad", "Glass Air", {
            { "cutoff", 9000.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.165f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc3_shape", 0.9449f }, { "osc3_level", 0.414f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.4016f }, { "osc4_level", 0.289f }, { "osc4_semi", 12.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.2f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.4f }, { "reverb_size", 0.9f },
            { "reverb_damp", 0.3f }, { "reverb_mix", 0.45f }, { "osc2_level", 0.0f } } },

        { "Pad", "Crystal Bed", {
            { "cutoff", 12000.000000f }, { "resonance", 0.08f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.0f },
            { "amp_decay", 1.5f }, { "amp_sustain", 0.8f }, { "amp_release", 3.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.213f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 2.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3858f }, { "osc3_level", 0.384f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.25f }, { "osc4_shape", 0.9843f }, { "osc4_level", 0.256f }, { "osc4_semi", 12.0f }, { "osc4_fine", 3.0f },
            { "osc4_pan", 0.25f }, { "lfo1_rate", 0.15f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.0f },
            { "lfo1_dest", 0.0f }, { "mm2_src", 1.0f }, { "mm2_dst", 7.0f }, { "mm2_amt", 0.5f }, { "delay_sync", 11.0f },
            { "delay_feedback", 0.4f }, { "delay_tone", 5000.0f }, { "delay_mix", 0.15f }, { "reverb_size", 0.85f }, { "reverb_damp", 0.25f },
            { "reverb_mix", 0.45f }, { "osc2_level", 0.0f } } },

        { "Pad", "Ice Halo", {
            { "cutoff", 10000.000000f }, { "resonance", 0.08f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.8f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 3.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.265f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.3f }, { "osc3_shape", 0.9606f }, { "osc3_level", 0.353f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.4094f }, { "osc4_level", 0.265f }, { "osc4_semi", 7.0f }, { "osc4_fine", 4.0f },
            { "osc4_pan", 0.2f }, { "chorus_rate", 0.25f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f }, { "reverb_size", 0.95f },
            { "reverb_damp", 0.3f }, { "reverb_mix", 0.5f }, { "osc2_level", 0.0f } } },

        { "Pad", "Shimmer Pad", {
            { "cutoff", 7000.0f }, { "resonance", 0.12f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.3f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.25f }, { "osc2_semi", 0.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.9764f }, { "osc3_level", 0.35f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "lfo1_rate", 0.4f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.06f }, { "lfo1_dest", 2.0f }, { "chorus_rate", 0.5f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f },
            { "delay_sync", 10.0f }, { "delay_feedback", 0.5f }, { "delay_tone", 6000.0f }, { "delay_mix", 0.2f }, { "reverb_size", 0.9f },
            { "reverb_damp", 0.35f }, { "reverb_mix", 0.4f }, { "osc4_level", 0.0f } } },

        { "Pad", "Cirrus", {
            { "cutoff", 5000.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.4f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 2.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.215f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 4.0f },
            { "osc1_unidet", 0.3f }, { "osc3_shape", 0.8661f }, { "osc3_level", 0.287f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.15f }, { "osc4_shape", 0.0236f }, { "osc4_level", 0.144f }, { "osc4_semi", 12.0f }, { "osc4_fine", 3.0f },
            { "osc4_pan", 0.15f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f }, { "reverb_size", 0.9f },
            { "reverb_damp", 0.4f }, { "reverb_mix", 0.45f }, { "osc2_level", 0.0f } } },

        { "Pad", "Snow Light", {
            { "cutoff", 8000.0f }, { "resonance", 0.08f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.5f },
            { "amp_decay", 1.2f }, { "amp_sustain", 0.9f }, { "amp_release", 3.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.287f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 4.0f },
            { "osc1_unidet", 0.3f }, { "osc3_shape", 0.9921f }, { "osc3_level", 0.246f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.8504f }, { "osc4_level", 0.246f }, { "osc4_semi", 0.0f }, { "osc4_fine", 4.0f },
            { "osc4_pan", 0.2f }, { "lfo1_rate", 0.12f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.08f },
            { "lfo1_dest", 3.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.35f }, { "reverb_size", 0.9f },
            { "reverb_damp", 0.35f }, { "reverb_mix", 0.45f }, { "osc2_level", 0.0f } } },

        { "Pad", "Dark Matter", {
            { "cutoff", 600.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.4f },
            { "flt_attack", 0.6f }, { "flt_decay", 1.5f }, { "flt_sustain", 0.7f }, { "flt_release", 2.0f }, { "amp_attack", 2.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.408f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.408f }, { "osc2_semi", -12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 5.0f }, { "osc2_unidet", 0.3f }, { "lfo1_rate", 0.07f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.14f }, { "lfo1_dest", 3.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.35f },
            { "reverb_size", 0.9f }, { "reverb_damp", 0.6f }, { "reverb_mix", 0.4f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Cinema Low", {
            { "cutoff", 500.0f }, { "resonance", 0.25f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.4f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.5f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.45f }, { "osc1_semi", -12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.4f }, { "osc2_semi", -24.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.25f }, { "osc3_shape", 0.6299f }, { "osc3_level", 0.3f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "reverb_size", 0.9f }, { "reverb_damp", 0.7f }, { "reverb_mix", 0.4f },
            { "osc4_level", 0.0f } } },

        { "Pad", "Abyss", {
            { "cutoff", 420.0f }, { "resonance", 0.3f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.4f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 3.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 5.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.498f }, { "osc1_semi", -12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 7.0f },
            { "osc1_unidet", 0.4f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.332f }, { "osc2_semi", -24.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 0.05f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.2f }, { "lfo1_dest", 3.0f }, { "reverb_size", 0.95f }, { "reverb_damp", 0.7f }, { "reverb_mix", 0.5f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Black Velvet", {
            { "cutoff", 900.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.15f }, { "key_track", 0.45f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.95f }, { "amp_release", 2.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.396f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 4.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.317f }, { "osc2_semi", -12.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "reverb_size", 0.75f }, { "reverb_damp", 0.6f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Nightfall", {
            { "cutoff", 750.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.35f }, { "key_track", 0.4f },
            { "flt_attack", 0.05f }, { "flt_decay", 4.0f }, { "flt_sustain", 0.3f }, { "flt_release", 2.5f }, { "amp_attack", 1.4f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.342f }, { "osc1_semi", -12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.308f }, { "osc2_semi", 0.0f }, { "osc2_fine", -9.0f },
            { "osc2_uni", 5.0f }, { "osc2_unidet", 0.3f }, { "osc4_shape", 0.8425f }, { "osc4_level", 0.171f }, { "osc4_semi", 0.0f },
            { "osc4_fine", 0.0f }, { "osc4_pan", 0.0f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.35f },
            { "reverb_size", 0.85f }, { "reverb_damp", 0.6f }, { "reverb_mix", 0.4f }, { "osc3_level", 0.0f } } },

        { "Pad", "Monolith", {
            { "cutoff", 700.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.4f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.8f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.233f }, { "osc1_semi", -12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.233f }, { "osc2_semi", -12.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.25f }, { "osc3_shape", 0.0394f }, { "osc3_level", 0.129f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "reverb_size", 0.8f }, { "reverb_damp", 0.6f }, { "reverb_mix", 0.35f }, { "osc4_level", 0.0f } } },

        { "Pad", "Slow Bloom", {
            { "cutoff", 500.0f }, { "resonance", 0.18f }, { "poles", 1.0f }, { "filter_env", 0.55f }, { "key_track", 0.5f },
            { "flt_attack", 3.0f }, { "flt_decay", 3.0f }, { "flt_sustain", 0.6f }, { "flt_release", 3.0f }, { "amp_attack", 1.8f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.373f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.28f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.336f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f },
            { "reverb_size", 0.75f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.35f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Tidal Wash", {
            { "cutoff", 2200.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.5f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.321f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.22f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.285f }, { "osc2_semi", 0.0f }, { "osc2_fine", -7.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.22f }, { "osc3_shape", 0.5827f }, { "osc3_level", 0.214f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "lfo1_rate", 0.12f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.0f }, { "lfo1_dest", 0.0f }, { "lfo2_rate", 0.09f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.14f }, { "lfo2_dest", 3.0f }, { "mm2_src", 1.0f }, { "mm2_dst", 3.0f }, { "mm2_amt", 0.22f },
            { "chorus_rate", 0.3f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f }, { "reverb_size", 0.85f }, { "reverb_damp", 0.45f },
            { "reverb_mix", 0.4f }, { "osc4_level", 0.0f } } },

        { "Pad", "Drift", {
            { "cutoff", 1800.0f }, { "resonance", 0.18f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 2.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.435f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.261f }, { "osc2_semi", 12.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "osc4_shape", 0.8346f }, { "osc4_level", 0.217f }, { "osc4_semi", 0.0f },
            { "osc4_fine", 0.0f }, { "osc4_pan", 0.0f }, { "lfo1_rate", 0.45f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 4.0f },
            { "lfo1_amount", 0.09f }, { "lfo1_dest", 3.0f }, { "lfo2_rate", 0.11f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 1.0f },
            { "lfo2_amount", 0.2f }, { "lfo2_dest", 6.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f },
            { "reverb_size", 0.8f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc3_level", 0.0f } } },

        { "Pad", "Aurora", {
            { "cutoff", 4000.0f }, { "resonance", 0.12f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.6f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.305f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 4.0f },
            { "osc1_unidet", 0.3f }, { "osc3_shape", 0.8819f }, { "osc3_level", 0.229f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.9528f }, { "osc4_level", 0.191f }, { "osc4_semi", 12.0f }, { "osc4_fine", 3.0f },
            { "osc4_pan", 0.2f }, { "lfo1_rate", 0.08f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f }, { "lfo1_amount", 0.0f },
            { "lfo1_dest", 0.0f }, { "lfo2_rate", 0.17f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 1.0f }, { "lfo2_amount", 0.1f },
            { "lfo2_dest", 2.0f }, { "mm2_src", 1.0f }, { "mm2_dst", 7.0f }, { "mm2_amt", 0.6f }, { "chorus_rate", 0.5f },
            { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f }, { "reverb_size", 0.9f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.45f },
            { "osc2_level", 0.0f } } },

        { "Pad", "Breathing Pad", {
            { "cutoff", 1900.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 2.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.394f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.22f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.355f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.22f }, { "lfo1_rate", 0.05f }, { "lfo1_sync", 1.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.16f }, { "lfo1_dest", 3.0f }, { "lfo2_rate", 0.05f }, { "lfo2_sync", 1.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.25f }, { "lfo2_dest", 5.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.35f },
            { "reverb_size", 0.7f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.35f }, { "noise_level", 0.023f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Pad", "Time Lapse", {
            { "cutoff", 400.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.6f }, { "key_track", 0.5f },
            { "flt_attack", 6.0f }, { "flt_decay", 4.0f }, { "flt_sustain", 0.5f }, { "flt_release", 4.0f }, { "amp_attack", 4.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 4.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.549f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.28f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.22f }, { "osc2_semi", 7.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 3.0f }, { "delay_feedback", 0.5f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.2f }, { "reverb_size", 0.85f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Pad", "Neon Pad", {
            { "cutoff", 2800.0f }, { "resonance", 0.22f }, { "poles", 1.0f }, { "filter_env", 0.3f }, { "key_track", 0.5f },
            { "flt_attack", 0.01f }, { "flt_decay", 1.2f }, { "flt_sustain", 0.35f }, { "flt_release", 1.5f }, { "amp_attack", 0.35f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.85f }, { "amp_release", 1.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.388f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.282f }, { "osc2_semi", 0.0f }, { "osc2_fine", 8.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.6f }, { "chorus_depth", 0.8f }, { "chorus_mix", 0.55f },
            { "delay_sync", 11.0f }, { "delay_feedback", 0.35f }, { "delay_tone", 4000.0f }, { "delay_mix", 0.18f }, { "reverb_size", 0.6f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Midnight Drive", {
            { "cutoff", 1600.0f }, { "resonance", 0.3f }, { "poles", 1.0f }, { "filter_env", 0.4f }, { "key_track", 0.5f },
            { "flt_attack", 0.01f }, { "flt_decay", 0.9f }, { "flt_sustain", 0.3f }, { "flt_release", 1.5f }, { "amp_attack", 0.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.8f }, { "amp_release", 1.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.621f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.496f }, { "osc2_semi", -12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.7f }, { "chorus_depth", 0.75f }, { "chorus_mix", 0.55f },
            { "delay_sync", 10.0f }, { "delay_feedback", 0.4f }, { "delay_tone", 3500.0f }, { "delay_mix", 0.15f }, { "reverb_size", 0.6f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Retro Wave", {
            { "cutoff", 3400.0f }, { "resonance", 0.18f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.5f },
            { "amp_decay", 0.8f }, { "amp_sustain", 0.85f }, { "amp_release", 1.4f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.55f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 4.0f },
            { "osc1_unidet", 0.28f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.25f }, { "osc2_semi", 12.0f }, { "osc2_fine", 3.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "lfo2_rate", 5.2f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.01f }, { "lfo2_dest", 1.0f }, { "chorus_rate", 0.55f }, { "chorus_depth", 0.8f }, { "chorus_mix", 0.5f },
            { "reverb_size", 0.55f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Sunset Strip", {
            { "cutoff", 2000.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.45f }, { "key_track", 0.5f },
            { "flt_attack", 0.25f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.5f }, { "flt_release", 1.2f }, { "amp_attack", 0.3f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.372f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.297f }, { "osc2_semi", 0.0f }, { "osc2_fine", 9.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.2598f }, { "osc3_level", 0.149f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "chorus_rate", 0.5f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f },
            { "delay_sync", 4.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3000.0f }, { "delay_mix", 0.1f }, { "reverb_size", 0.6f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc4_level", 0.0f } } },

        { "Pad", "PWM Dream", {
            { "cutoff", 3500.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.7f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.85f }, { "osc1_level", 0.29f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.85f }, { "osc2_level", 0.231f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 0.35f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f },
            { "lfo1_amount", 0.22f }, { "lfo1_dest", 2.0f }, { "chorus_rate", 0.45f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.45f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Pad", "Hollow Pulse", {
            { "cutoff", 2000.0f }, { "resonance", 0.25f }, { "poles", 0.0f }, { "filter_env", 0.15f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 2.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.316f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 2.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.158f }, { "osc2_semi", 12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.0472f }, { "osc3_level", 0.158f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "lfo1_rate", 0.2f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.1f }, { "lfo1_dest", 3.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f },
            { "reverb_size", 0.7f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc4_level", 0.0f } } },

        { "Pad", "Clarinet Pad", {
            { "cutoff", 3500.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.5f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.085f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 2.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.7795f }, { "osc3_level", 0.31f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.7953f }, { "osc4_level", 0.197f }, { "osc4_semi", 0.0f }, { "osc4_fine", 6.0f },
            { "osc4_pan", 0.2f }, { "lfo2_rate", 5.0f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f }, { "lfo2_amount", 0.008f },
            { "lfo2_dest", 1.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f }, { "reverb_size", 0.6f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc2_level", 0.0f } } },

        { "Pad", "Organ Cloud", {
            { "cutoff", 6000.0f }, { "resonance", 0.05f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.6f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.15f },
            { "amp_decay", 0.3f }, { "amp_sustain", 1.0f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.118f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.2205f }, { "osc3_level", 0.295f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.2047f }, { "osc4_level", 0.206f }, { "osc4_semi", 12.0f }, { "osc4_fine", 0.0f },
            { "osc4_pan", 0.2f }, { "lfo1_rate", 0.8f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.3f },
            { "lfo1_dest", 6.0f }, { "chorus_rate", 0.5f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.35f }, { "reverb_size", 0.6f },
            { "reverb_damp", 0.4f }, { "reverb_mix", 0.35f }, { "osc2_level", 0.0f } } },


        // ------------------------------------------------------------ Lead
        { "Lead", "Classic Saw Lead", {
            { "cutoff", 3200.0f }, { "resonance", 0.25f }, { "poles", 1.0f }, { "filter_env", 0.3f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.5f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 40.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.846f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.634f }, { "osc2_semi", 0.0f }, { "osc2_fine", 8.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Square Lead", {
            { "cutoff", 2400.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.25f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.35f }, { "flt_sustain", 0.5f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 30.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.424f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.282f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 4.0f }, { "delay_feedback", 0.25f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.1f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Sync Lead", {
            { "cutoff", 5000.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.6f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 30.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.668f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.557f }, { "osc2_semi", 7.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc_sync", 1.0f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Super Lead", {
            { "cutoff", 4200.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.25f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.5f }, { "flt_sustain", 0.6f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 25.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.561f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.3f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.505f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 5.0f }, { "osc2_unidet", 0.35f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f }, { "delay_mix", 0.12f }, { "reverb_size", 0.5f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Soft Sine Lead", {
            { "cutoff", 6000.0f }, { "resonance", 0.0f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.02f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.25f }, { "voice_mode", 1.0f }, { "glide", 60.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.416f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.091f }, { "osc2_semi", 12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.0079f }, { "osc3_level", 0.151f }, { "osc3_semi", 12.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "lfo1_rate", 5.3f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.02f }, { "lfo1_dest", 1.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc4_level", 0.0f } } },

        { "Lead", "Trance Pluck", {
            { "cutoff", 1800.0f }, { "resonance", 0.3f }, { "poles", 1.0f }, { "filter_env", 0.65f }, { "key_track", 0.5f },
            { "flt_attack", 0.002f }, { "flt_decay", 0.25f }, { "flt_sustain", 0.15f }, { "flt_release", 0.2f }, { "amp_attack", 0.002f },
            { "amp_decay", 0.35f }, { "amp_sustain", 0.4f }, { "amp_release", 0.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 1.0f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.8f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.25f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.45f }, { "delay_tone", 4000.0f },
            { "delay_mix", 0.25f }, { "reverb_size", 0.5f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.25f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Brass Lead", {
            { "cutoff", 1200.0f }, { "resonance", 0.12f }, { "poles", 1.0f }, { "filter_env", 0.55f }, { "key_track", 0.5f },
            { "flt_attack", 0.09f }, { "flt_decay", 0.5f }, { "flt_sustain", 0.6f }, { "flt_release", 0.2f }, { "amp_attack", 0.04f },
            { "amp_decay", 0.3f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 25.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.5f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.5f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.2598f }, { "osc3_level", 0.2f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.4f }, { "chorus_mix", 0.2f },
            { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc4_level", 0.0f } } },

        { "Lead", "Flute Lead", {
            { "cutoff", 5000.0f }, { "resonance", 0.05f }, { "poles", 0.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.06f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.8f }, { "flt_release", 0.2f }, { "amp_attack", 0.06f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.25f }, { "voice_mode", 1.0f }, { "glide", 35.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.251f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.7874f }, { "osc3_level", 0.46f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "lfo1_rate", 5.2f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.018f },
            { "lfo1_dest", 1.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f }, { "delay_mix", 0.12f },
            { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "noise_level", 0.025f }, { "osc2_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Whistle Lead", {
            { "cutoff", 9000.0f }, { "resonance", 0.0f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.03f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.25f }, { "voice_mode", 1.0f }, { "glide", 120.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.43f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.0f }, { "osc3_level", 0.072f }, { "osc3_semi", 12.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "lfo1_rate", 5.8f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.025f },
            { "lfo1_dest", 1.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 4500.0f }, { "delay_mix", 0.15f },
            { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "noise_level", 0.015f }, { "osc2_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Eighties Lead", {
            { "cutoff", 3800.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.3f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.5f }, { "flt_sustain", 0.55f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 20.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.566f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.396f }, { "osc2_semi", 0.0f }, { "osc2_fine", 6.0f },
            { "osc2_uni", 2.0f }, { "osc2_unidet", 0.2f }, { "chorus_rate", 0.6f }, { "chorus_depth", 0.8f }, { "chorus_mix", 0.5f },
            { "delay_sync", 11.0f }, { "delay_feedback", 0.4f }, { "delay_tone", 4000.0f }, { "delay_mix", 0.22f }, { "reverb_size", 0.5f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Violin Lead", {
            { "cutoff", 3000.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.2f }, { "key_track", 0.7f },
            { "flt_attack", 0.1f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.7f }, { "flt_release", 0.3f }, { "amp_attack", 0.08f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.25f }, { "voice_mode", 1.0f }, { "glide", 40.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.5f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.4f }, { "osc2_semi", 0.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 5.6f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.028f }, { "lfo1_dest", 1.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.4f }, { "chorus_mix", 0.2f },
            { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Moog Mono", {
            { "cutoff", 1400.0f }, { "resonance", 0.38f }, { "poles", 1.0f }, { "filter_env", 0.6f }, { "key_track", 0.6f },
            { "flt_attack", 0.003f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.3f }, { "flt_release", 0.2f }, { "amp_attack", 0.003f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.15f }, { "voice_mode", 1.0f }, { "glide", 60.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.889f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.799f }, { "osc2_semi", -12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.0236f }, { "osc3_level", 0.355f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 5.0f }, { "osc3_pan", 0.0f }, { "reverb_size", 0.3f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.1f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Hollow Lead", {
            { "cutoff", 3000.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.3f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.5f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 30.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.363f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.0394f }, { "osc3_level", 0.727f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f }, { "delay_mix", 0.12f },
            { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc2_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Sizzle Lead", {
            { "cutoff", 7000.0f }, { "resonance", 0.3f }, { "poles", 0.0f }, { "filter_env", 0.2f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.6f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 30.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 1.0f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.5f }, { "osc2_semi", 12.0f }, { "osc2_fine", -5.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "noise_level", 0.03f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Portamento Lead", {
            { "cutoff", 2600.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.25f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.6f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 160.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.835f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 2.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.607f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.45f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Octave Lead", {
            { "cutoff", 3400.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.25f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.6f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 30.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.65f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.585f }, { "osc2_semi", 12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "Lead", "Chip Lead", {
            { "cutoff", 6000.0f }, { "resonance", 0.05f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.12f }, { "amp_sustain", 0.6f }, { "amp_release", 0.08f }, { "voice_mode", 1.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.6f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.2f }, { "osc2_semi", 12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "dist_type", 3.0f }, { "dist_drive", 0.15f }, { "dist_mix", 0.15f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Glass Lead", {
            { "cutoff", 10000.000000f }, { "resonance", 0.05f }, { "poles", 0.0f }, { "filter_env", 0.1f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.5f }, { "flt_sustain", 0.5f }, { "flt_release", 0.5f }, { "amp_attack", 0.003f },
            { "amp_decay", 0.6f }, { "amp_sustain", 0.6f }, { "amp_release", 0.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.56f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.56f }, { "osc2_semi", 12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.3937f }, { "osc3_level", 0.747f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "osc4_shape", 0.9685f }, { "osc4_level", 0.373f }, { "osc4_semi", 12.0f },
            { "osc4_fine", 3.0f }, { "osc4_pan", 0.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.6f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.25f }, { "fm_3to4", 0.18f } } },

        { "Lead", "Anthem Lead", {
            { "cutoff", 3800.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.25f }, { "key_track", 0.5f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.5f }, { "flt_sustain", 0.6f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 35.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.554f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 7.0f },
            { "osc1_unidet", 0.4f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.493f }, { "osc2_semi", -12.0f }, { "osc2_fine", 4.0f },
            { "osc2_uni", 7.0f }, { "osc2_unidet", 0.4f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "delay_sync", 10.0f }, { "delay_feedback", 0.35f }, { "delay_tone", 4000.0f }, { "delay_mix", 0.2f }, { "reverb_size", 0.65f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Lead", "Mellow Lead", {
            { "cutoff", 2000.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.15f }, { "key_track", 0.5f },
            { "flt_attack", 0.01f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.7f }, { "flt_release", 0.3f }, { "amp_attack", 0.004f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.2f }, { "voice_mode", 1.0f }, { "glide", 50.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.592f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.355f }, { "osc2_semi", 0.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 5.4f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.012f }, { "lfo1_dest", 1.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.12f }, { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },


        // ------------------------------------------------------------ SFX
        { "SFX", "Laser Zap", {
            { "cutoff", 6000.0f }, { "resonance", 0.3f }, { "poles", 1.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 0.22f }, { "flt_sustain", 0.0f }, { "flt_release", 0.1f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.3f }, { "amp_sustain", 0.0f }, { "amp_release", 0.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.897f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.719f }, { "osc2_semi", 0.0f }, { "osc2_fine", 10.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", 1.0f },
            { "mm3_src", 3.0f }, { "mm3_dst", 1.0f }, { "mm3_amt", 1.0f }, { "delay_sync", 5.0f }, { "delay_feedback", 0.3f },
            { "delay_tone", 5000.0f }, { "delay_mix", 0.15f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Reverse Zap", {
            { "cutoff", 5000.0f }, { "resonance", 0.25f }, { "poles", 1.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 0.35f }, { "flt_sustain", 0.0f }, { "flt_release", 0.1f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.45f }, { "amp_sustain", 0.0f }, { "amp_release", 0.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.828f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.662f }, { "osc2_semi", 0.0f }, { "osc2_fine", 10.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", -1.0f },
            { "mm3_src", 3.0f }, { "mm3_dst", 1.0f }, { "mm3_amt", -1.0f }, { "delay_sync", 5.0f }, { "delay_feedback", 0.3f },
            { "delay_tone", 5000.0f }, { "delay_mix", 0.15f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Noise Riser", {
            { "cutoff", 450.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.9f }, { "key_track", 0.0f },
            { "flt_attack", 6.0f }, { "flt_decay", 1.0f }, { "flt_sustain", 1.0f }, { "flt_release", 1.0f }, { "amp_attack", 5.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 1.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.25f }, { "noise_level", 1.0f }, { "osc1_level", 0.0f },
            { "osc2_level", 0.0f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Down Sweep", {
            { "cutoff", 900.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.9f }, { "key_track", 0.0f },
            { "flt_attack", 0.001f }, { "flt_decay", 3.0f }, { "flt_sustain", 0.0f }, { "flt_release", 1.0f }, { "amp_attack", 0.001f },
            { "amp_decay", 3.5f }, { "amp_sustain", 0.0f }, { "amp_release", 1.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.25f }, { "noise_level", 1.0f }, { "osc1_level", 0.0f },
            { "osc2_level", 0.0f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Wind Gust", {
            { "cutoff", 2600.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.0f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 2.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "lfo1_rate", 0.18f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f }, { "lfo1_amount", 0.22f }, { "lfo1_dest", 3.0f },
            { "lfo2_rate", 0.31f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f }, { "lfo2_amount", 0.5f }, { "lfo2_dest", 6.0f },
            { "reverb_size", 0.8f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.35f }, { "noise_level", 1.0f }, { "osc1_level", 0.0f },
            { "osc2_level", 0.0f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Two-Tone Alarm", {
            { "cutoff", 3500.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.005f },
            { "amp_decay", 0.1f }, { "amp_sustain", 1.0f }, { "amp_release", 0.05f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.315f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.158f }, { "osc2_semi", 0.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 2.0f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 3.0f },
            { "lfo1_amount", 0.17f }, { "lfo1_dest", 1.0f }, { "reverb_size", 0.25f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Sci-Fi Computer", {
            { "cutoff", 2500.0f }, { "resonance", 0.3f }, { "poles", 1.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.01f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.1f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.53f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.3333f }, { "osc2_level", 0.353f }, { "osc2_semi", 12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 11.0f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 4.0f },
            { "lfo1_amount", 0.45f }, { "lfo1_dest", 1.0f }, { "lfo2_rate", 7.0f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 4.0f },
            { "lfo2_amount", 0.2f }, { "lfo2_dest", 3.0f }, { "delay_sync", 5.0f }, { "delay_feedback", 0.45f }, { "delay_tone", 5000.0f },
            { "delay_mix", 0.25f }, { "reverb_size", 0.3f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "SFX", "Data Bleeps", {
            { "cutoff", 4500.0f }, { "resonance", 0.2f }, { "poles", 1.0f }, { "filter_env", 0.3f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 0.12f }, { "flt_sustain", 0.0f }, { "flt_release", 0.05f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.14f }, { "amp_sustain", 0.0f }, { "amp_release", 0.05f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.956f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.478f }, { "osc2_semi", 7.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.126f }, { "osc3_level", 0.764f }, { "osc3_semi", 12.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "osc4_shape", 0.1575f }, { "osc4_level", 0.574f }, { "osc4_semi", 0.0f },
            { "osc4_fine", 0.0f }, { "osc4_pan", 0.0f }, { "lfo1_rate", 0.05f }, { "lfo1_sync", 5.0f }, { "lfo1_shape", 4.0f },
            { "lfo1_amount", 0.5f }, { "lfo1_dest", 1.0f }, { "delay_sync", 5.0f }, { "delay_feedback", 0.5f }, { "delay_tone", 5000.0f },
            { "delay_mix", 0.3f }, { "reverb_size", 0.3f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.15f } } },

        { "SFX", "Impact Boom", {
            { "cutoff", 800.0f }, { "resonance", 0.1f }, { "poles", 1.0f }, { "filter_env", 0.6f }, { "key_track", 0.2f },
            { "flt_attack", 0.001f }, { "flt_decay", 0.4f }, { "flt_sustain", 0.0f }, { "flt_release", 0.3f }, { "amp_attack", 0.001f },
            { "amp_decay", 1.4f }, { "amp_sustain", 0.0f }, { "amp_release", 1.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.6f }, { "osc1_semi", -24.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", 1.0f }, { "mm3_src", 3.0f },
            { "mm3_dst", 1.0f }, { "mm3_amt", 1.0f }, { "reverb_size", 0.9f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f },
            { "noise_level", 0.35f }, { "dist_type", 0.0f }, { "dist_drive", 0.2f }, { "dist_mix", 0.15f }, { "osc2_level", 0.0f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Sub Drop", {
            { "cutoff", 3000.0f }, { "resonance", 0.0f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 1.8f }, { "flt_sustain", 0.0f }, { "flt_release", 0.3f }, { "amp_attack", 0.003f },
            { "amp_decay", 2.2f }, { "amp_sustain", 0.0f }, { "amp_release", 1.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.481f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.0f }, { "osc3_level", 0.321f }, { "osc3_semi", -12.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", 1.0f }, { "mm3_src", 3.0f },
            { "mm3_dst", 1.0f }, { "mm3_amt", 1.0f }, { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f },
            { "osc2_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Bubbles", {
            { "cutoff", 6000.0f }, { "resonance", 0.0f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 0.08f }, { "flt_sustain", 0.0f }, { "flt_release", 0.05f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.12f }, { "amp_sustain", 0.0f }, { "amp_release", 0.08f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 1.0f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.0f }, { "osc2_level", 0.417f }, { "osc2_semi", 12.0f }, { "osc2_fine", 0.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", -1.0f },
            { "mm3_src", 9.0f }, { "mm3_dst", 1.0f }, { "mm3_amt", 0.35f }, { "delay_sync", 5.0f }, { "delay_feedback", 0.4f },
            { "delay_tone", 5000.0f }, { "delay_mix", 0.25f }, { "reverb_size", 0.4f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Metal Hit", {
            { "cutoff", 9000.0f }, { "resonance", 0.15f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.001f },
            { "amp_decay", 1.6f }, { "amp_sustain", 0.0f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.442f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.442f }, { "osc2_semi", 6.0f }, { "osc2_fine", 15.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.7087f }, { "osc3_level", 0.442f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "reverb_size", 0.6f }, { "reverb_damp", 0.3f }, { "reverb_mix", 0.3f },
            { "ring_mod", 0.45f }, { "osc4_level", 0.0f } } },

        { "SFX", "Shatter", {
            { "cutoff", 12000.000000f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.0f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.5f }, { "amp_sustain", 0.0f }, { "amp_release", 0.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc3_shape", 0.9764f }, { "osc3_level", 0.785f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f },
            { "osc4_shape", 0.4331f }, { "osc4_level", 0.471f }, { "osc4_semi", 12.0f }, { "osc4_fine", 0.0f }, { "osc4_pan", 0.0f },
            { "delay_sync", 5.0f }, { "delay_feedback", 0.45f }, { "delay_tone", 7000.0f }, { "delay_mix", 0.3f }, { "reverb_size", 0.7f },
            { "reverb_damp", 0.2f }, { "reverb_mix", 0.4f }, { "noise_level", 0.785f }, { "osc1_level", 0.0f }, { "osc2_level", 0.0f } } },

        { "SFX", "Radio Static", {
            { "cutoff", 6000.0f }, { "resonance", 0.25f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.0f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.05f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 0.3f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "lfo1_rate", 9.0f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 4.0f }, { "lfo1_amount", 0.3f }, { "lfo1_dest", 3.0f },
            { "lfo2_rate", 6.0f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 4.0f }, { "lfo2_amount", 0.4f }, { "lfo2_dest", 5.0f },
            { "reverb_size", 0.25f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.1f }, { "noise_level", 1.0f }, { "osc1_level", 0.0f },
            { "osc2_level", 0.0f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Tape Stop", {
            { "cutoff", 3000.0f }, { "resonance", 0.15f }, { "poles", 1.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 1.3f }, { "flt_sustain", 0.0f }, { "flt_release", 0.3f }, { "amp_attack", 0.001f },
            { "amp_decay", 1.6f }, { "amp_sustain", 0.0f }, { "amp_release", 0.3f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.632f }, { "osc1_semi", -24.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.505f }, { "osc2_semi", -24.0f }, { "osc2_fine", 8.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", 1.0f },
            { "mm3_src", 3.0f }, { "mm3_dst", 1.0f }, { "mm3_amt", 1.0f }, { "reverb_size", 0.3f }, { "reverb_damp", 0.5f },
            { "reverb_mix", 0.1f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Turbine Hover", {
            { "cutoff", 700.0f }, { "resonance", 0.4f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.8f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 1.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.498f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.449f }, { "osc2_semi", -12.0f }, { "osc2_fine", 15.0f },
            { "osc2_uni", 3.0f }, { "osc2_unidet", 0.25f }, { "lfo1_rate", 6.5f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.12f }, { "lfo1_dest", 3.0f }, { "lfo2_rate", 0.25f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f },
            { "lfo2_amount", 0.18f }, { "lfo2_dest", 6.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.35f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Sub Thump", {
            { "cutoff", 2500.0f }, { "resonance", 0.0f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.001f }, { "flt_decay", 0.09f }, { "flt_sustain", 0.0f }, { "flt_release", 0.05f }, { "amp_attack", 0.001f },
            { "amp_decay", 0.35f }, { "amp_sustain", 0.0f }, { "amp_release", 0.1f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.7f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "mm2_src", 3.0f }, { "mm2_dst", 1.0f }, { "mm2_amt", 1.0f }, { "mm3_src", 3.0f },
            { "mm3_dst", 1.0f }, { "mm3_amt", 1.0f }, { "osc2_level", 0.0f }, { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Siren", {
            { "cutoff", 2800.0f }, { "resonance", 0.15f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.5f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.1f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 0.3f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.403f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 1.0f }, { "osc2_level", 0.242f }, { "osc2_semi", 0.0f }, { "osc2_fine", 5.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 0.55f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f },
            { "lfo1_amount", 0.6f }, { "lfo1_dest", 1.0f }, { "delay_sync", 4.0f }, { "delay_feedback", 0.35f }, { "delay_tone", 4000.0f },
            { "delay_mix", 0.15f }, { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc3_level", 0.0f },
            { "osc4_level", 0.0f } } },

        { "SFX", "Spaceship Pass", {
            { "cutoff", 400.0f }, { "resonance", 0.45f }, { "poles", 1.0f }, { "filter_env", 0.8f }, { "key_track", 0.2f },
            { "flt_attack", 4.0f }, { "flt_decay", 3.0f }, { "flt_sustain", 0.3f }, { "flt_release", 2.0f }, { "amp_attack", 2.5f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 2.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.748f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.4f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.561f }, { "osc2_semi", -12.0f }, { "osc2_fine", 9.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "lfo1_rate", 0.2f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.8f }, { "lfo1_dest", 6.0f }, { "delay_sync", 3.0f }, { "delay_feedback", 0.5f }, { "delay_tone", 4000.0f },
            { "delay_mix", 0.2f }, { "reverb_size", 0.8f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "noise_level", 0.748f },
            { "osc3_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "SFX", "Fairy Dust", {
            { "cutoff", 14000.000000f }, { "resonance", 0.05f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.15f },
            { "amp_decay", 1.5f }, { "amp_sustain", 0.3f }, { "amp_release", 2.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.268f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.9685f }, { "osc3_level", 0.536f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.4252f }, { "osc4_level", 0.402f }, { "osc4_semi", 19.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "lfo1_rate", 0.7f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f }, { "lfo1_amount", 0.7f },
            { "lfo1_dest", 6.0f }, { "lfo2_rate", 0.4f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 1.0f }, { "lfo2_amount", 0.06f },
            { "lfo2_dest", 2.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.55f }, { "delay_tone", 7000.0f }, { "delay_mix", 0.3f },
            { "reverb_size", 0.9f }, { "reverb_damp", 0.25f }, { "reverb_mix", 0.5f }, { "osc2_level", 0.0f } } },


        // ------------------------------------------------------------ Vocal
        { "Vocal", "Ooh Choir", {
            { "cutoff", 1100.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.127f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.315f }, { "osc3_level", 0.423f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3228f }, { "osc4_level", 0.338f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.8f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Aah Choir", {
            { "cutoff", 2200.0f }, { "resonance", 0.15f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.2f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3386f }, { "osc3_level", 0.5f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3465f }, { "osc4_level", 0.4f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.8f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Eeh Choir", {
            { "cutoff", 4000.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.172f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3622f }, { "osc3_level", 0.575f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3701f }, { "osc4_level", 0.46f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.8f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Oh Choir", {
            { "cutoff", 1500.0f }, { "resonance", 0.18f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.135f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3228f }, { "osc3_level", 0.451f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3307f }, { "osc4_level", 0.361f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.8f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Vowel Morph", {
            { "cutoff", 2000.0f }, { "resonance", 0.15f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.8f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.182f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3307f }, { "osc3_level", 0.606f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3543f }, { "osc4_level", 0.424f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "lfo1_rate", 0.18f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f }, { "lfo1_amount", 0.0f },
            { "lfo1_dest", 0.0f }, { "mm2_src", 1.0f }, { "mm2_dst", 3.0f }, { "mm2_amt", 0.12f }, { "mm3_src", 1.0f },
            { "mm3_dst", 4.0f }, { "mm3_amt", 0.08f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f },
            { "reverb_size", 0.75f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.35f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Talking Pad", {
            { "cutoff", 2200.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.3f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc3_shape", 0.3386f }, { "osc3_level", 0.653f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f }, { "osc3_pan", -0.3f },
            { "osc4_shape", 0.3465f }, { "osc4_level", 0.457f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f }, { "osc4_pan", 0.3f },
            { "lfo1_rate", 0.05f }, { "lfo1_sync", 4.0f }, { "lfo1_shape", 4.0f }, { "lfo1_amount", 0.0f }, { "lfo1_dest", 0.0f },
            { "mm2_src", 1.0f }, { "mm2_dst", 3.0f }, { "mm2_amt", 0.12f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f },
            { "chorus_mix", 0.45f }, { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc1_level", 0.0f },
            { "osc2_level", 0.0f } } },

        { "Vocal", "Breathy Vox", {
            { "cutoff", 3000.0f }, { "resonance", 0.3f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.25f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc3_shape", 0.3465f }, { "osc3_level", 1.0f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f },
            { "lfo2_rate", 5.2f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f }, { "lfo2_amount", 0.012f }, { "lfo2_dest", 1.0f },
            { "reverb_size", 0.7f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "noise_level", 0.155f }, { "osc1_level", 0.0f },
            { "osc2_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Vocal", "Male Choir", {
            { "cutoff", 900.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.8f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.2f }, { "osc1_semi", -12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3228f }, { "osc3_level", 0.5f }, { "osc3_semi", -12.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3307f }, { "osc4_level", 0.4f }, { "osc4_semi", -12.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.8f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Angel Choir", {
            { "cutoff", 6000.0f }, { "resonance", 0.1f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.4f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.2f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.0f }, { "osc1_level", 0.2f }, { "osc1_semi", 12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.25f }, { "osc3_shape", 0.3543f }, { "osc3_level", 0.4f }, { "osc3_semi", 12.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3622f }, { "osc4_level", 0.35f }, { "osc4_semi", 12.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.7f }, { "chorus_mix", 0.5f }, { "reverb_size", 0.95f },
            { "reverb_damp", 0.3f }, { "reverb_mix", 0.5f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Robot Vox", {
            { "cutoff", 1800.0f }, { "resonance", 0.45f }, { "poles", 0.0f }, { "filter_env", 0.2f }, { "key_track", 0.3f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.5f }, { "flt_release", 0.2f }, { "amp_attack", 0.005f },
            { "amp_decay", 0.2f }, { "amp_sustain", 0.9f }, { "amp_release", 0.1f }, { "voice_mode", 1.0f }, { "glide", 40.0f },
            { "osc1_shape", 1.0f }, { "osc1_level", 0.752f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3386f }, { "osc3_level", 0.752f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "delay_sync", 5.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 3500.0f }, { "delay_mix", 0.12f },
            { "reverb_size", 0.3f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.1f }, { "fm_4to3", 0.2f }, { "osc4_level", 0.376f },
            { "osc4_shape", 0.3543f }, { "osc4_semi", 12.0f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Whisper Pad", {
            { "cutoff", 2500.0f }, { "resonance", 0.5f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 1.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 2.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc3_shape", 0.3465f }, { "osc3_level", 0.502f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f },
            { "lfo1_rate", 0.25f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.2f }, { "lfo1_dest", 3.0f },
            { "chorus_rate", 0.3f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.35f }, { "reverb_size", 0.85f }, { "reverb_damp", 0.5f },
            { "reverb_mix", 0.4f }, { "noise_level", 0.704f }, { "osc1_level", 0.0f }, { "osc2_level", 0.0f }, { "osc4_level", 0.0f } } },

        { "Vocal", "Gospel Voices", {
            { "cutoff", 2300.0f }, { "resonance", 0.12f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.4f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.3333f }, { "osc1_level", 0.177f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3307f }, { "osc3_level", 0.591f }, { "osc3_semi", 0.0f }, { "osc3_fine", -4.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3386f }, { "osc4_level", 0.473f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "lfo2_rate", 5.4f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f }, { "lfo2_amount", 0.014f },
            { "lfo2_dest", 1.0f }, { "chorus_rate", 0.4f }, { "chorus_depth", 0.6f }, { "chorus_mix", 0.4f }, { "reverb_size", 0.6f },
            { "reverb_damp", 0.4f }, { "reverb_mix", 0.3f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Monk Drone", {
            { "cutoff", 700.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.2f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 2.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 3.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.15f }, { "osc1_semi", -12.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.315f }, { "osc3_level", 0.55f }, { "osc3_semi", -12.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.2f }, { "osc4_shape", 0.3228f }, { "osc4_level", 0.4f }, { "osc4_semi", -12.0f }, { "osc4_fine", 6.0f },
            { "osc4_pan", 0.2f }, { "lfo1_rate", 0.1f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.1f },
            { "lfo1_dest", 3.0f }, { "reverb_size", 0.9f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.4f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Vowel Pluck", {
            { "cutoff", 2500.0f }, { "resonance", 0.3f }, { "poles", 0.0f }, { "filter_env", 0.5f }, { "key_track", 0.3f },
            { "flt_attack", 0.002f }, { "flt_decay", 0.25f }, { "flt_sustain", 0.1f }, { "flt_release", 0.3f }, { "amp_attack", 0.003f },
            { "amp_decay", 0.4f }, { "amp_sustain", 0.2f }, { "amp_release", 0.3f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc3_shape", 0.3386f }, { "osc3_level", 1.0f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f },
            { "osc4_shape", 0.3465f }, { "osc4_level", 0.5f }, { "osc4_semi", 12.0f }, { "osc4_fine", 4.0f }, { "osc4_pan", 0.0f },
            { "mm2_src", 3.0f }, { "mm2_dst", 3.0f }, { "mm2_amt", 0.12f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f },
            { "delay_tone", 4000.0f }, { "delay_mix", 0.15f }, { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.25f },
            { "osc1_level", 0.0f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Opera Lead", {
            { "cutoff", 3500.0f }, { "resonance", 0.15f }, { "poles", 0.0f }, { "filter_env", 0.1f }, { "key_track", 0.4f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.1f },
            { "amp_decay", 0.3f }, { "amp_sustain", 0.9f }, { "amp_release", 0.3f }, { "voice_mode", 1.0f }, { "glide", 50.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.37f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 1.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3465f }, { "osc3_level", 0.926f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "osc4_shape", 0.3543f }, { "osc4_level", 0.556f }, { "osc4_semi", 0.0f }, { "osc4_fine", 4.0f },
            { "osc4_pan", 0.0f }, { "lfo1_rate", 5.6f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f }, { "lfo1_amount", 0.03f },
            { "lfo1_dest", 1.0f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.3f }, { "delay_tone", 4000.0f }, { "delay_mix", 0.12f },
            { "reverb_size", 0.6f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.3f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Vox Stab", {
            { "cutoff", 3000.0f }, { "resonance", 0.2f }, { "poles", 0.0f }, { "filter_env", 0.4f }, { "key_track", 0.3f },
            { "flt_attack", 0.005f }, { "flt_decay", 0.3f }, { "flt_sustain", 0.3f }, { "flt_release", 0.2f }, { "amp_attack", 0.005f },
            { "amp_decay", 0.25f }, { "amp_sustain", 0.35f }, { "amp_release", 0.2f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.333f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3386f }, { "osc3_level", 1.0f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", 0.0f }, { "osc4_shape", 0.3701f }, { "osc4_level", 0.499f }, { "osc4_semi", 12.0f }, { "osc4_fine", 4.0f },
            { "osc4_pan", 0.0f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.4f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Ghost Choir", {
            { "cutoff", 1500.0f }, { "resonance", 0.3f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 2.0f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 4.0f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.167f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 5.0f },
            { "osc1_unidet", 0.25f }, { "osc3_shape", 0.315f }, { "osc3_level", 0.444f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3701f }, { "osc4_level", 0.333f }, { "osc4_semi", 12.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "lfo1_rate", 0.13f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 1.0f }, { "lfo1_amount", 0.0f },
            { "lfo1_dest", 0.0f }, { "lfo2_rate", 0.21f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 1.0f }, { "lfo2_amount", 0.6f },
            { "lfo2_dest", 6.0f }, { "mm2_src", 1.0f }, { "mm2_dst", 3.0f }, { "mm2_amt", 0.2f }, { "chorus_rate", 0.35f },
            { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "delay_sync", 11.0f }, { "delay_feedback", 0.5f }, { "delay_tone", 3500.0f },
            { "delay_mix", 0.2f }, { "reverb_size", 0.95f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.5f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Formant Sweep", {
            { "cutoff", 900.0f }, { "resonance", 0.55f }, { "poles", 0.0f }, { "filter_env", 0.0f }, { "key_track", 0.0f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.05f },
            { "amp_decay", 1.0f }, { "amp_sustain", 1.0f }, { "amp_release", 0.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.5f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc2_shape", 0.6667f }, { "osc2_level", 0.3f }, { "osc2_semi", 0.0f }, { "osc2_fine", 7.0f },
            { "osc2_uni", 1.0f }, { "osc2_unidet", 0.2f }, { "osc3_shape", 0.3386f }, { "osc3_level", 0.3f }, { "osc3_semi", 0.0f },
            { "osc3_fine", 0.0f }, { "osc3_pan", 0.0f }, { "lfo1_rate", 0.6f }, { "lfo1_sync", 0.0f }, { "lfo1_shape", 0.0f },
            { "lfo1_amount", 0.35f }, { "lfo1_dest", 3.0f }, { "chorus_rate", 0.3f }, { "chorus_depth", 0.5f }, { "chorus_mix", 0.3f },
            { "reverb_size", 0.5f }, { "reverb_damp", 0.5f }, { "reverb_mix", 0.2f }, { "osc4_level", 0.0f } } },

        { "Vocal", "Duet Ah Oh", {
            { "cutoff", 1800.0f }, { "resonance", 0.15f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.7f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 1.6f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.15f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3386f }, { "osc3_level", 0.5f }, { "osc3_semi", 0.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.35f }, { "osc4_shape", 0.315f }, { "osc4_level", 0.5f }, { "osc4_semi", 0.0f }, { "osc4_fine", 0.0f },
            { "osc4_pan", 0.35f }, { "lfo2_rate", 5.3f }, { "lfo2_sync", 0.0f }, { "lfo2_shape", 0.0f }, { "lfo2_amount", 0.012f },
            { "lfo2_dest", 1.0f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.7f },
            { "reverb_damp", 0.5f }, { "reverb_mix", 0.35f }, { "osc2_level", 0.0f } } },

        { "Vocal", "Cathedral Voices", {
            { "cutoff", 3200.0f }, { "resonance", 0.12f }, { "poles", 0.0f }, { "filter_env", 0.05f }, { "key_track", 0.3f },
            { "flt_attack", 0.5f }, { "flt_decay", 1.0f }, { "flt_sustain", 0.6f }, { "flt_release", 1.5f }, { "amp_attack", 0.9f },
            { "amp_decay", 1.0f }, { "amp_sustain", 0.9f }, { "amp_release", 2.5f }, { "voice_mode", 0.0f }, { "glide", 0.0f },
            { "osc1_shape", 0.6667f }, { "osc1_level", 0.167f }, { "osc1_semi", 0.0f }, { "osc1_fine", 0.0f }, { "osc1_uni", 3.0f },
            { "osc1_unidet", 0.2f }, { "osc3_shape", 0.3465f }, { "osc3_level", 0.5f }, { "osc3_semi", 12.0f }, { "osc3_fine", 0.0f },
            { "osc3_pan", -0.3f }, { "osc4_shape", 0.3307f }, { "osc4_level", 0.389f }, { "osc4_semi", 0.0f }, { "osc4_fine", 5.0f },
            { "osc4_pan", 0.3f }, { "chorus_rate", 0.35f }, { "chorus_depth", 0.65f }, { "chorus_mix", 0.45f }, { "reverb_size", 0.98f },
            { "reverb_damp", 0.35f }, { "reverb_mix", 0.5f }, { "osc2_level", 0.0f } } },

        // ------------------------------------------------------------ Starter (the original eight)

        { "Starter", "Fat Saw Lead", {
            { "osc1_level", 0.8f }, { "osc1_uni", 5 }, { "osc1_unidet", 0.35f },
            { "osc2_level", 0.8f }, { "osc2_uni", 5 }, { "osc2_unidet", 0.35f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 2800 }, { "resonance", 0.3f }, { "filter_env", 0.4f },
            { "flt_decay", 0.5f }, { "flt_sustain", 0.3f },
            { "amp_attack", 0.005f }, { "amp_decay", 0.3f }, { "amp_sustain", 0.9f }, { "amp_release", 0.35f },
            { "voice_mode", 2 }, { "glide", 60 },
            { "lfo1_rate", 5.5f }, { "lfo1_amount", 0.03f }, { "lfo1_dest", 1 },
            { "delay_sync", 11 }, { "delay_feedback", 0.4f }, { "delay_mix", 0.25f },
            { "reverb_mix", 0.2f } } },

        { "Starter", "Warm Pad", {
            { "osc1_level", 0.7f }, { "osc1_uni", 3 }, { "osc1_unidet", 0.25f },
            { "osc2_level", 0.7f }, { "osc2_uni", 3 }, { "osc2_unidet", 0.3f }, { "osc2_shape", 0.333f }, { "osc2_fine", -7 },
            { "osc3_level", 0.4f }, { "osc3_shape", 0.05f }, { "osc3_semi", 12 }, { "osc4_level", 0 },
            { "cutoff", 900 }, { "resonance", 0.2f }, { "filter_env", 0.3f },
            { "flt_attack", 0.8f }, { "flt_decay", 1.5f }, { "flt_sustain", 0.6f },
            { "amp_attack", 0.9f }, { "amp_decay", 1.0f }, { "amp_sustain", 0.85f }, { "amp_release", 2.2f },
            { "lfo1_rate", 0.3f }, { "lfo1_amount", 0.25f }, { "lfo1_dest", 3 },
            { "chorus_mix", 0.5f }, { "chorus_depth", 0.6f },
            { "reverb_size", 0.8f }, { "reverb_mix", 0.4f } } },

        { "Starter", "Sub Bass (Mono)", {
            { "osc1_shape", 0.0f }, { "osc1_semi", -12 },
            { "osc2_semi", -12 }, { "osc2_level", 0.6f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 500 }, { "resonance", 0.3f }, { "filter_env", 0.5f },
            { "flt_decay", 0.25f }, { "flt_sustain", 0.1f },
            { "amp_attack", 0.005f }, { "amp_decay", 0.3f }, { "amp_sustain", 0.9f }, { "amp_release", 0.1f },
            { "voice_mode", 1 }, { "glide", 40 },
            { "dist_drive", 0.4f }, { "dist_mix", 0.25f } } },

        { "Starter", "Pluck Sequence", {
            { "osc1_level", 0.8f }, { "osc2_level", 0.7f }, { "osc2_shape", 1.0f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 700 }, { "resonance", 0.45f }, { "filter_env", 0.8f },
            { "flt_decay", 0.2f }, { "flt_sustain", 0 },
            { "amp_attack", 0.005f }, { "amp_decay", 0.25f }, { "amp_sustain", 0 }, { "amp_release", 0.15f },
            { "seq_on", 1 }, { "seq_rate", 2 }, { "seq_swing", 0.2f },
            // its own little pattern (the sequencer itself now starts flat)
            { "seq_step_2", 7.0f / 12.0f }, { "seq_step_3", 4.0f / 12.0f }, { "seq_step_4", 7.0f / 12.0f }, { "seq_step_6", 7.0f / 12.0f }, { "seq_step_7", 12.0f / 12.0f }, { "seq_step_8", 7.0f / 12.0f }, { "seq_step_10", 7.0f / 12.0f }, { "seq_step_11", 4.0f / 12.0f }, { "seq_step_12", 7.0f / 12.0f }, { "seq_step_14", 4.0f / 12.0f }, { "seq_step_15", 7.0f / 12.0f }, { "seq_step_16", 12.0f / 12.0f },
            { "delay_sync", 11 }, { "delay_feedback", 0.4f }, { "delay_mix", 0.3f },
            { "reverb_mix", 0.15f } } },

        { "Starter", "Glass Bells", {
            { "osc1_level", 0 }, { "osc2_level", 0 },
            { "osc3_level", 0.8f }, { "osc3_shape", 0.44f },
            { "osc4_level", 0.5f }, { "osc4_shape", 0.5f }, { "osc4_semi", 12 }, { "osc4_pan", 0.4f },
            { "fm_4to3", 0.15f },
            { "cutoff", 8000 }, { "resonance", 0.1f }, { "filter_env", 0 },
            { "amp_attack", 0.003f }, { "amp_decay", 2.5f }, { "amp_sustain", 0 }, { "amp_release", 2.5f },
            { "delay_sync", 3 }, { "delay_mix", 0.2f },
            { "reverb_size", 0.8f }, { "reverb_mix", 0.4f } } },

        { "Starter", "Wobble Bass", {
            { "osc1_semi", -12 }, { "osc1_uni", 3 }, { "osc1_unidet", 0.2f },
            { "osc2_semi", -12 }, { "osc2_shape", 1.0f }, { "osc2_level", 0.7f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 400 }, { "resonance", 0.55f }, { "filter_env", 0 },
            { "amp_attack", 0.005f }, { "amp_decay", 0.3f }, { "amp_sustain", 1.0f }, { "amp_release", 0.1f },
            { "voice_mode", 1 },
            { "lfo1_sync", 4 }, { "lfo1_shape", 1 }, { "lfo1_amount", 0.7f }, { "lfo1_dest", 3 },
            { "dist_drive", 0.5f }, { "dist_mix", 0.3f } } },

        { "Starter", "FM Keys", {
            { "osc1_level", 0 }, { "osc2_level", 0 },
            { "osc3_level", 0 }, { "osc3_shape", 0.0f }, { "osc3_semi", 12 },
            { "osc4_level", 1.0f }, { "osc4_shape", 0.0f },
            { "fm_3to4", 0.35f },
            { "cutoff", 12000 }, { "filter_env", 0 },
            { "amp_attack", 0.005f }, { "amp_decay", 1.2f }, { "amp_sustain", 0.3f }, { "amp_release", 0.4f },
            { "mm2_src", 5 }, { "mm2_dst", 8 }, { "mm2_amt", 0.5f },
            { "chorus_mix", 0.4f } } },

        { "Starter", "Ambient Wash", {
            { "osc1_level", 0.4f }, { "osc1_uni", 4 }, { "osc1_unidet", 0.3f },
            { "osc2_level", 0 },
            { "osc3_level", 0.8f }, { "osc3_shape", 0.86f },
            { "osc4_level", 0.5f }, { "osc4_shape", 0.3f }, { "osc4_semi", 7 }, { "osc4_fine", 5 },
            { "cutoff", 1800 }, { "resonance", 0.2f }, { "filter_env", 0.2f },
            { "flt_attack", 1.5f }, { "flt_sustain", 0.7f },
            { "amp_decay", 0.3f }, { "amp_attack", 1.5f }, { "amp_sustain", 0.9f }, { "amp_release", 4.0f },
            { "lfo2_rate", 0.15f }, { "lfo2_amount", 0.5f }, { "lfo2_dest", 6 },
            { "chorus_mix", 0.5f },
            { "delay_sync", 10 }, { "delay_mix", 0.35f },
            { "reverb_size", 0.95f }, { "reverb_damp", 0.4f }, { "reverb_mix", 0.6f } } },
    };
    return list;
}

class PresetManager
{
public:
    explicit PresetManager (juce::AudioProcessorValueTreeState& s) : apvts (s) {}

    // Bumped (before and after) every time a preset is loaded. The audio thread watches it and fades the
    // output back in, so a preset change can never arrive as a sudden burst of volume.
    std::atomic<int> changes { 0 };

    static juce::File userDir()
    {
        auto d = juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory)
                     .getChildFile ("Z-Synth").getChildFile ("Presets");
        d.createDirectory();
        return d;
    }

    static juce::StringArray userNames()
    {
        juce::StringArray names;
        for (const auto& f : userDir().findChildFiles (juce::File::findFiles, false, "*.xml"))
            names.add (f.getFileNameWithoutExtension());
        names.sort (true);
        return names;
    }

    void resetToDefaults()
    {
        for (auto* p : apvts.processor.getParameters())
            if (auto* r = dynamic_cast<juce::RangedAudioParameter*> (p))
            {
                const auto id = r->paramID;
                if (id == "skin" || id == "master" || id == "analog")
                    continue;
                r->setValueNotifyingHost (r->getDefaultValue());
            }
    }

    void setReal (const juce::String& id, float value)
    {
        if (auto* p = apvts.getParameter (id))
            p->setValueNotifyingHost (p->convertTo0to1 (value));
        else
            jassertfalse;
    }

    void loadFactory (int index)
    {
        const auto& list = factoryPresets();
        if (! juce::isPositiveAndBelow (index, (int) list.size()))
            return;

        ++changes;
        resetToDefaults();
        for (const auto& kv : list[(size_t) index].values)
            setReal (kv.first, kv.second);

        apvts.state.setProperty ("presetName", list[(size_t) index].name, nullptr);
        ++changes;
    }

    bool saveUser (const juce::String& name)
    {
        auto clean = juce::File::createLegalFileName (name.trim());
        if (clean.isEmpty())
            return false;

        auto state = apvts.copyState();
        state.setProperty ("presetName", clean, nullptr);
        state.removeProperty ("uiWidth", nullptr);   state.removeProperty ("editorWidth", nullptr);   // the window size belongs to the project, not the sound

        if (auto xml = state.createXml())
        {
            apvts.state.setProperty ("presetName", clean, nullptr);
            return xml->writeTo (userDir().getChildFile (clean + ".xml"));
        }
        return false;
    }

    bool loadUser (const juce::String& name)
    {
        auto f = userDir().getChildFile (name + ".xml");
        if (auto xml = juce::XmlDocument::parse (f))
            if (xml->hasTagName (apvts.state.getType()))
            {
                ++changes;
                const auto skin = apvts.getParameter ("skin")->getValue();
                const auto width = apvts.state.getProperty ("uiWidth");
                apvts.replaceState (juce::ValueTree::fromXml (*xml));
                apvts.getParameter ("skin")->setValueNotifyingHost (skin);   // keep the current skin
                if (! width.isVoid())
                    apvts.state.setProperty ("uiWidth", width, nullptr);   // and the current window size
                apvts.state.setProperty ("presetName", name, nullptr);
                ++changes;
                return true;
            }
        return false;
    }

    bool deleteUser (const juce::String& name)
    {
        return userDir().getChildFile (name + ".xml").deleteFile();
    }

private:
    juce::AudioProcessorValueTreeState& apvts;
};
} // namespace evo
