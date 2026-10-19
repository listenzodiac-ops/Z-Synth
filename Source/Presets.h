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
    const char* name;
    std::vector<std::pair<const char*, float>> values;
};

inline const std::vector<FactoryPreset>& factoryPresets()
{
    static const std::vector<FactoryPreset> list = {
        { "Init", {} },

        { "Fat Saw Lead", {
            { "osc1_level", 0.8f }, { "osc1_uni", 5 }, { "osc1_unidet", 0.35f },
            { "osc2_level", 0.8f }, { "osc2_uni", 5 }, { "osc2_unidet", 0.35f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 2800 }, { "resonance", 0.3f }, { "filter_env", 0.4f },
            { "flt_decay", 0.5f }, { "flt_sustain", 0.3f },
            { "amp_sustain", 0.9f }, { "amp_release", 0.35f },
            { "voice_mode", 2 }, { "glide", 60 },
            { "lfo1_rate", 5.5f }, { "lfo1_amount", 0.03f }, { "lfo1_dest", 1 },
            { "delay_sync", 11 }, { "delay_feedback", 0.4f }, { "delay_mix", 0.25f },
            { "reverb_mix", 0.2f } } },

        { "Warm Pad", {
            { "osc1_level", 0.7f }, { "osc1_uni", 3 }, { "osc1_unidet", 0.25f },
            { "osc2_level", 0.7f }, { "osc2_uni", 3 }, { "osc2_unidet", 0.3f }, { "osc2_shape", 0.333f }, { "osc2_fine", -7 },
            { "osc3_level", 0.4f }, { "osc3_shape", 0.05f }, { "osc3_semi", 12 }, { "osc4_level", 0 },
            { "cutoff", 900 }, { "resonance", 0.2f }, { "filter_env", 0.3f },
            { "flt_attack", 0.8f }, { "flt_decay", 1.5f }, { "flt_sustain", 0.6f },
            { "amp_attack", 0.9f }, { "amp_decay", 1.0f }, { "amp_sustain", 0.85f }, { "amp_release", 2.2f },
            { "lfo1_rate", 0.3f }, { "lfo1_amount", 0.25f }, { "lfo1_dest", 3 },
            { "chorus_mix", 0.5f }, { "chorus_depth", 0.6f },
            { "reverb_size", 0.8f }, { "reverb_mix", 0.4f } } },

        { "Sub Bass (Mono)", {
            { "osc1_shape", 0.0f }, { "osc1_semi", -12 },
            { "osc2_semi", -12 }, { "osc2_level", 0.6f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 500 }, { "resonance", 0.3f }, { "filter_env", 0.5f },
            { "flt_decay", 0.25f }, { "flt_sustain", 0.1f },
            { "amp_sustain", 0.9f }, { "amp_release", 0.1f },
            { "voice_mode", 1 }, { "glide", 40 },
            { "dist_drive", 0.4f }, { "dist_mix", 0.25f } } },

        { "Pluck Sequence", {
            { "osc1_level", 0.8f }, { "osc2_level", 0.7f }, { "osc2_shape", 1.0f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 700 }, { "resonance", 0.45f }, { "filter_env", 0.8f },
            { "flt_decay", 0.2f }, { "flt_sustain", 0 },
            { "amp_decay", 0.25f }, { "amp_sustain", 0 }, { "amp_release", 0.15f },
            { "seq_on", 1 }, { "seq_rate", 2 }, { "seq_swing", 0.2f },
            { "delay_sync", 11 }, { "delay_feedback", 0.4f }, { "delay_mix", 0.3f },
            { "reverb_mix", 0.15f } } },

        { "Glass Bells", {
            { "osc1_level", 0 }, { "osc2_level", 0 },
            { "osc3_level", 0.8f }, { "osc3_shape", 0.44f },
            { "osc4_level", 0.5f }, { "osc4_shape", 0.5f }, { "osc4_semi", 12 }, { "osc4_pan", 0.4f },
            { "fm_4to3", 0.15f },
            { "cutoff", 8000 }, { "resonance", 0.1f }, { "filter_env", 0 },
            { "amp_attack", 0.003f }, { "amp_decay", 2.5f }, { "amp_sustain", 0 }, { "amp_release", 2.5f },
            { "delay_sync", 3 }, { "delay_mix", 0.2f },
            { "reverb_size", 0.8f }, { "reverb_mix", 0.4f } } },

        { "Wobble Bass", {
            { "osc1_semi", -12 }, { "osc1_uni", 3 }, { "osc1_unidet", 0.2f },
            { "osc2_semi", -12 }, { "osc2_shape", 1.0f }, { "osc2_level", 0.7f },
            { "osc3_level", 0 }, { "osc4_level", 0 },
            { "cutoff", 400 }, { "resonance", 0.55f }, { "filter_env", 0 },
            { "amp_sustain", 1.0f }, { "amp_release", 0.1f },
            { "voice_mode", 1 },
            { "lfo1_sync", 4 }, { "lfo1_shape", 1 }, { "lfo1_amount", 0.7f }, { "lfo1_dest", 3 },
            { "dist_drive", 0.5f }, { "dist_mix", 0.3f } } },

        { "FM Keys", {
            { "osc1_level", 0 }, { "osc2_level", 0 },
            { "osc3_level", 0 }, { "osc3_shape", 0.0f }, { "osc3_semi", 12 },
            { "osc4_level", 1.0f }, { "osc4_shape", 0.0f },
            { "fm_3to4", 0.35f },
            { "cutoff", 12000 }, { "filter_env", 0 },
            { "amp_decay", 1.2f }, { "amp_sustain", 0.3f }, { "amp_release", 0.4f },
            { "mm2_src", 5 }, { "mm2_dst", 8 }, { "mm2_amt", 0.5f },
            { "chorus_mix", 0.4f } } },

        { "Ambient Wash", {
            { "osc1_level", 0.4f }, { "osc1_uni", 4 }, { "osc1_unidet", 0.3f },
            { "osc2_level", 0 },
            { "osc3_level", 0.8f }, { "osc3_shape", 0.86f },
            { "osc4_level", 0.5f }, { "osc4_shape", 0.3f }, { "osc4_semi", 7 }, { "osc4_fine", 5 },
            { "cutoff", 1800 }, { "resonance", 0.2f }, { "filter_env", 0.2f },
            { "flt_attack", 1.5f }, { "flt_sustain", 0.7f },
            { "amp_attack", 1.5f }, { "amp_sustain", 0.9f }, { "amp_release", 4.0f },
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

        resetToDefaults();
        for (const auto& kv : list[(size_t) index].values)
            setReal (kv.first, kv.second);

        apvts.state.setProperty ("presetName", list[(size_t) index].name, nullptr);
    }

    bool saveUser (const juce::String& name)
    {
        auto clean = juce::File::createLegalFileName (name.trim());
        if (clean.isEmpty())
            return false;

        auto state = apvts.copyState();
        state.setProperty ("presetName", clean, nullptr);

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
                const auto skin = apvts.getParameter ("skin")->getValue();
                apvts.replaceState (juce::ValueTree::fromXml (*xml));
                apvts.getParameter ("skin")->setValueNotifyingHost (skin);   // keep the current skin
                apvts.state.setProperty ("presetName", name, nullptr);
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
