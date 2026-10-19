#include "Params.h"

namespace evo
{
using APF  = juce::AudioParameterFloat;
using APC  = juce::AudioParameterChoice;
using Attr = juce::AudioParameterFloatAttributes;
using PID  = juce::ParameterID;
using Range = juce::NormalisableRange<float>;

static Range skewed (float lo, float hi, float centre)
{
    Range r (lo, hi);
    r.setSkewForCentre (centre);
    return r;
}

juce::StringArray syncNames()
{
    return { "Free", "1/1", "1/2", "1/4", "1/8", "1/16", "1/32", "1/4T", "1/8T", "1/16T", "1/4D", "1/8D", "1/16D" };
}

juce::AudioProcessorValueTreeState::ParameterLayout createLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // ---- Oscillators --------------------------------------------------------
    for (int i = 0; i < numOscs; ++i)
    {
        const bool analog = i < 2;
        const juce::String n = "Osc " + juce::String (i + 1) + " ";

        layout.add (std::make_unique<APF> (PID { oscID (i, "level"), 1 }, n + "Level",
                                           Range (0.0f, 1.0f, 0.001f),
                                           1.0f));

        layout.add (std::make_unique<APF> (PID { oscID (i, "semi"), 1 }, n + "Semitones",
                                           Range (-24.0f, 24.0f, 1.0f), 0.0f,
                                           Attr().withLabel ("st")));

        layout.add (std::make_unique<APF> (PID { oscID (i, "fine"), 1 }, n + "Fine",
                                           Range (-100.0f, 100.0f, 0.1f),
                                           i == 1 ? 7.0f : 0.0f,   // slight detune on osc 2
                                           Attr().withLabel ("ct")));

        layout.add (std::make_unique<APF> (PID { oscID (i, "pan"), 1 }, n + "Pan",
                                           Range (-1.0f, 1.0f, 0.001f), 0.0f));

        if (analog)
        {
            layout.add (std::make_unique<APF> (PID { oscID (i, "uni"), 1 }, n + "Unison Voices",
                                               Range (1.0f, (float) maxUnison, 1.0f), 1.0f));
            layout.add (std::make_unique<APF> (PID { oscID (i, "unidet"), 1 }, n + "Unison Detune",
                                               Range (0.0f, 1.0f, 0.001f), 0.3f));
        }

        // Analog osc: 0 = sine, 1/3 = triangle, 2/3 = saw, 1 = square. Digital osc: wave 1..128.
        layout.add (std::make_unique<APF> (PID { oscID (i, "shape"), 1 },
                                           n + (analog ? "Shape" : "Wave"),
                                           Range (0.0f, 1.0f, 0.001f),
                                           analog ? 2.0f / 3.0f : 0.0f));   // analog default = saw
    }

    // ---- Digital FM (oscillators 3 and 4 only) -----------------------------
    layout.add (std::make_unique<APF> (PID { "fm_4to3", 1 }, "FM 4 > 3",
                                       Range (0.0f, 1.0f, 0.001f), 0.0f));
    layout.add (std::make_unique<APF> (PID { "fm_3to4", 1 }, "FM 3 > 4",
                                       Range (0.0f, 1.0f, 0.001f), 0.0f));

    // ---- Oscillator sync and ring modulation --------------------------------
    layout.add (std::make_unique<APC> (PID { "osc_sync", 1 }, "Osc Sync",
                                       juce::StringArray { "Off", "On" }, 0));
    layout.add (std::make_unique<APF> (PID { "ring_mod", 1 }, "Ring Mod",
                                       Range (0.0f, 1.0f, 0.001f), 0.0f));

    // ---- Noise (white, mixed in ahead of the filter) -----------------------
    layout.add (std::make_unique<APF> (PID { "noise_level", 1 }, "Noise Level",
                                       Range (0.0f, 1.0f, 0.001f), 0.0f));

    // ---- Filter -------------------------------------------------------------
    layout.add (std::make_unique<APF> (PID { "cutoff", 1 }, "Cutoff", skewed (20.0f, 20000.0f, 1000.0f),
                                       1500.0f, Attr().withLabel ("Hz")));
    layout.add (std::make_unique<APF> (PID { "resonance", 1 }, "Resonance",
                                       Range (0.0f, 1.0f, 0.001f), 0.25f));
    layout.add (std::make_unique<APC> (PID { "poles", 1 }, "Poles",
                                       juce::StringArray { "2-pole", "4-pole" }, 1));
    layout.add (std::make_unique<APF> (PID { "filter_env", 1 }, "Env Amount",
                                       Range (-1.0f, 1.0f, 0.001f), 0.5f));
    layout.add (std::make_unique<APF> (PID { "key_track", 1 }, "Key Track",
                                       Range (0.0f, 1.0f, 0.001f), 0.5f));

    // ---- Envelopes ----------------------------------------------------------
    auto time = [] { return skewed (0.001f, 10.0f, 0.4f); };
    auto sec  = [] { return Attr().withLabel ("s"); };

    layout.add (std::make_unique<APF> (PID { "flt_attack",  1 }, "Filter Attack",  time(), 0.005f, sec()));
    layout.add (std::make_unique<APF> (PID { "flt_decay",   1 }, "Filter Decay",   time(), 0.4f,   sec()));
    layout.add (std::make_unique<APF> (PID { "flt_sustain", 1 }, "Filter Sustain", Range (0.0f, 1.0f, 0.001f), 0.2f));
    layout.add (std::make_unique<APF> (PID { "flt_release", 1 }, "Filter Release", time(), 0.3f,   sec()));

    layout.add (std::make_unique<APF> (PID { "amp_attack",  1 }, "Amp Attack",  time(), 0.005f, sec()));
    layout.add (std::make_unique<APF> (PID { "amp_decay",   1 }, "Amp Decay",   time(), 0.3f,   sec()));
    layout.add (std::make_unique<APF> (PID { "amp_sustain", 1 }, "Amp Sustain", Range (0.0f, 1.0f, 0.001f), 0.8f));
    layout.add (std::make_unique<APF> (PID { "amp_release", 1 }, "Amp Release", time(), 0.25f,  sec()));

    // ---- LFOs ---------------------------------------------------------------
    for (int i = 0; i < numLfos; ++i)
    {
        const juce::String n = "LFO " + juce::String (i + 1) + " ";

        layout.add (std::make_unique<APF> (PID { lfoID (i, "rate"), 1 }, n + "Rate",
                                           skewed (0.02f, 30.0f, 2.0f), 2.0f, Attr().withLabel ("Hz")));
        layout.add (std::make_unique<APC> (PID { lfoID (i, "sync"), 1 }, n + "Sync", syncNames(), 0));
        layout.add (std::make_unique<APC> (PID { lfoID (i, "shape"), 1 }, n + "Shape",
                                           juce::StringArray { "Sine", "Tri", "Saw", "Square", "S&H" }, 0));
        layout.add (std::make_unique<APF> (PID { lfoID (i, "amount"), 1 }, n + "Amount",
                                           Range (-1.0f, 1.0f, 0.001f), 0.0f));
        layout.add (std::make_unique<APC> (PID { lfoID (i, "dest"), 1 }, n + "Destination",
                                           juce::StringArray { "Off", "Pitch", "Shape", "Cutoff", "Reso", "Amp", "Pan", "FM", "Ring" },
                                           i == 0 ? destPitch : destOff));
    }

    // ---- Modulation matrix --------------------------------------------------
    const juce::StringArray srcNames { "Off", "LFO 1", "LFO 2", "Filt Env", "Amp Env", "Velocity", "Mod Wheel", "Pressure", "Key", "Random" };
    const juce::StringArray dstNames { "Off", "Pitch", "Shape", "Wave", "Cutoff", "Reso", "Amp", "Pan", "FM", "Ring", "Noise", "Detune" };
    for (int i = 0; i < numSlots; ++i)
    {
        const juce::String n = "Mod " + juce::String (i + 1) + " ";
        const int defSrc = i == 0 ? srcModWheel : (i == 1 ? srcVelocity : srcOff);
        const int defDst = i == 0 ? dstCutoff   : (i == 1 ? dstCutoff   : dstOff);
        layout.add (std::make_unique<APC> (PID { mmID (i, "src"), 1 }, n + "Source", srcNames, defSrc));
        layout.add (std::make_unique<APC> (PID { mmID (i, "dst"), 1 }, n + "Dest", dstNames, defDst));
        layout.add (std::make_unique<APF> (PID { mmID (i, "amt"), 1 }, n + "Amount",
                                           Range (-1.0f, 1.0f, 0.001f), i == 0 ? 0.5f : 0.0f));
    }

    // ---- Voices -------------------------------------------------------------
    layout.add (std::make_unique<APC> (PID { "voices", 1 }, "Voices", juce::StringArray { "4", "6", "8" }, 2));
    layout.add (std::make_unique<APC> (PID { "voice_mode", 1 }, "Voice Mode",
                                       juce::StringArray { "Poly", "Mono", "Legato" }, 0));
    layout.add (std::make_unique<APF> (PID { "glide", 1 }, "Glide", skewed (0.0f, 2000.0f, 150.0f), 0.0f,
                                       Attr().withLabel ("ms")));
    layout.add (std::make_unique<APF> (PID { "bend_range", 1 }, "Bend Range",
                                       Range (1.0f, 24.0f, 1.0f), 2.0f, Attr().withLabel ("st")));

    // ---- Effects: distortion -> chorus -> delay -> reverb --------------------
    layout.add (std::make_unique<APC> (PID { "dist_type", 1 }, "Dist Type",
                                       juce::StringArray { "Soft", "Hard", "Fold", "Crush" }, 0));
    layout.add (std::make_unique<APF> (PID { "dist_drive", 1 }, "Dist Drive", Range (0.0f, 1.0f, 0.001f), 0.3f));
    layout.add (std::make_unique<APF> (PID { "dist_mix", 1 },   "Dist Mix",   Range (0.0f, 1.0f, 0.001f), 0.0f));

    layout.add (std::make_unique<APF> (PID { "chorus_rate", 1 },  "Chorus Rate",
                                       skewed (0.05f, 5.0f, 0.6f), 0.5f, Attr().withLabel ("Hz")));
    layout.add (std::make_unique<APF> (PID { "chorus_depth", 1 }, "Chorus Depth", Range (0.0f, 1.0f, 0.001f), 0.5f));
    layout.add (std::make_unique<APF> (PID { "chorus_mix", 1 },   "Chorus Mix",   Range (0.0f, 1.0f, 0.001f), 0.0f));

    layout.add (std::make_unique<APF> (PID { "delay_time", 1 }, "Delay Time",
                                       skewed (10.0f, 1000.0f, 250.0f), 300.0f, Attr().withLabel ("ms")));
    layout.add (std::make_unique<APC> (PID { "delay_sync", 1 }, "Delay Sync", syncNames(), 0));
    layout.add (std::make_unique<APF> (PID { "delay_feedback", 1 }, "Delay Feedback",
                                       Range (0.0f, 0.95f, 0.001f), 0.35f));
    layout.add (std::make_unique<APF> (PID { "delay_tone", 1 }, "Delay Tone",
                                       skewed (200.0f, 16000.0f, 3000.0f), 6000.0f, Attr().withLabel ("Hz")));
    layout.add (std::make_unique<APF> (PID { "delay_mix", 1 }, "Delay Mix",
                                       Range (0.0f, 1.0f, 0.001f), 0.0f));

    layout.add (std::make_unique<APF> (PID { "reverb_size", 1 }, "Reverb Size", Range (0.0f, 1.0f, 0.001f), 0.5f));
    layout.add (std::make_unique<APF> (PID { "reverb_damp", 1 }, "Reverb Damp", Range (0.0f, 1.0f, 0.001f), 0.5f));
    layout.add (std::make_unique<APF> (PID { "reverb_mix", 1 },  "Reverb Mix",  Range (0.0f, 1.0f, 0.001f), 0.0f));

    // ---- Step sequencer -----------------------------------------------------
    layout.add (std::make_unique<APC> (PID { "seq_on", 1 },   "Seq On",
                                       juce::StringArray { "Off", "On" }, 0));
    layout.add (std::make_unique<APC> (PID { "seq_gate", 1 }, "Seq Gate",
                                       juce::StringArray { "Off", "On" }, 1));
    layout.add (std::make_unique<APC> (PID { "seq_rate", 1 }, "Seq Rate",
                                       juce::StringArray { "1/4", "1/8", "1/16", "1/32", "1/8T", "1/16T" }, 2));
    layout.add (std::make_unique<APC> (PID { "seq_dest", 1 }, "Seq Lane",
                                       juce::StringArray { "Pitch", "Cutoff", "Pan" }, 0));
    layout.add (std::make_unique<APF> (PID { "seq_length", 1 }, "Seq Length",
                                       Range (1.0f, 16.0f, 1.0f), 16.0f));
    layout.add (std::make_unique<APC> (PID { "seq_dir", 1 }, "Seq Direction",
                                       juce::StringArray { "Fwd", "Back", "Pend", "Rand" }, 0));
    layout.add (std::make_unique<APF> (PID { "seq_swing", 1 }, "Seq Swing",
                                       Range (0.0f, 1.0f, 0.001f), 0.0f));

    // A musical starter pattern (in 1/12ths, so pitch lands on semitones: 7 = fifth, 12 = octave).
    static const float pattern[16] = { 0, 7, 4, 7,  0, 7, 12, 7,  0, 7, 4, 7,  0, 4, 7, 12 };
    for (int i = 0; i < numSteps; ++i)
    {
        const auto idx = juce::String (i + 1);
        layout.add (std::make_unique<juce::AudioParameterBool> (PID { "seq_on_" + idx, 1 }, "Seq Step On " + idx, true));
        layout.add (std::make_unique<APF> (PID { "seq_step_" + idx, 1 }, "Seq Pitch " + idx,
                                           Range (-1.0f, 1.0f, 0.001f), pattern[i] / 12.0f));
        layout.add (std::make_unique<APF> (PID { "seq_cut_" + idx, 1 }, "Seq Cutoff " + idx,
                                           Range (-1.0f, 1.0f, 0.001f), 0.0f));
        layout.add (std::make_unique<APF> (PID { "seq_pan_" + idx, 1 }, "Seq Pan " + idx,
                                           Range (-1.0f, 1.0f, 0.001f), 0.0f));
    }

    layout.add (std::make_unique<APC> (PID { "skin", 1 }, "Skin",
                                       juce::StringArray { "Blue", "White" }, 0));

    layout.add (std::make_unique<APF> (PID { "analog", 1 }, "Analog",
                                       Range (0.0f, 1.0f, 0.001f), 0.35f));

    layout.add (std::make_unique<APF> (PID { "master", 1 }, "Master",
                                       Range (-48.0f, 6.0f, 0.1f), -6.0f, Attr().withLabel ("dB")));

    return layout;
}

void bindPointers (juce::AudioProcessorValueTreeState& s, ParamPointers& p)
{
    auto get = [&s] (const juce::String& id)
    {
        auto* ptr = s.getRawParameterValue (id);
        jassert (ptr != nullptr);
        return ptr;
    };

    for (int i = 0; i < numOscs; ++i)
    {
        p.oscLevel[i] = get (oscID (i, "level"));
        p.oscSemi [i] = get (oscID (i, "semi"));
        p.oscFine [i] = get (oscID (i, "fine"));
        p.oscPan  [i] = get (oscID (i, "pan"));
        if (i < 2)
        {
            p.oscUni   [i] = get (oscID (i, "uni"));
            p.oscUniDet[i] = get (oscID (i, "unidet"));
        }
        p.oscShape[i] = get (oscID (i, "shape"));
    }

    p.fm43      = get ("fm_4to3");
    p.fm34      = get ("fm_3to4");

    p.cutoff    = get ("cutoff");
    p.resonance = get ("resonance");
    p.poles     = get ("poles");
    p.filterEnv = get ("filter_env");
    p.keyTrack  = get ("key_track");

    p.fltA = get ("flt_attack");  p.fltD = get ("flt_decay");
    p.fltS = get ("flt_sustain"); p.fltR = get ("flt_release");
    p.ampA = get ("amp_attack");  p.ampD = get ("amp_decay");
    p.ampS = get ("amp_sustain"); p.ampR = get ("amp_release");

    for (int i = 0; i < numLfos; ++i)
    {
        p.lfoRate  [i] = get (lfoID (i, "rate"));
        p.lfoShape [i] = get (lfoID (i, "shape"));
        p.lfoAmount[i] = get (lfoID (i, "amount"));
        p.lfoDest  [i] = get (lfoID (i, "dest"));
    }

    for (int i = 0; i < numLfos; ++i)
        p.lfoSync[i] = get (lfoID (i, "sync"));

    for (int i = 0; i < numSlots; ++i)
    {
        p.mmSrc[i] = get (mmID (i, "src"));
        p.mmDst[i] = get (mmID (i, "dst"));
        p.mmAmt[i] = get (mmID (i, "amt"));
    }

    p.voices = get ("voices");  p.voiceMode = get ("voice_mode");
    p.glide  = get ("glide");   p.bendRange = get ("bend_range");

    p.distType = get ("dist_type");  p.distDrive = get ("dist_drive");  p.distMix = get ("dist_mix");
    p.chRate = get ("chorus_rate");    p.chDepth = get ("chorus_depth");  p.chMix = get ("chorus_mix");
    p.delayTime = get ("delay_time");  p.delaySync = get ("delay_sync");
    p.delayFeedback = get ("delay_feedback");
    p.delayTone = get ("delay_tone");
    p.delayMix  = get ("delay_mix");
    p.rvSize = get ("reverb_size");    p.rvDamp = get ("reverb_damp");    p.rvMix = get ("reverb_mix");

    p.noise   = get ("noise_level");
    p.sync    = get ("osc_sync");
    p.ring    = get ("ring_mod");
    p.seqOn   = get ("seq_on");
    p.seqGate = get ("seq_gate");
    p.seqRate = get ("seq_rate");
    p.seqDest = get ("seq_dest");
    p.seqLength = get ("seq_length");
    p.seqDir    = get ("seq_dir");
    p.seqSwing  = get ("seq_swing");
    for (int i = 0; i < numSteps; ++i)
    {
        const auto idx = juce::String (i + 1);
        p.seqStepOn[i]  = get ("seq_on_" + idx);
        p.seqPitch [i]  = get ("seq_step_" + idx);
        p.seqCutoff[i]  = get ("seq_cut_" + idx);
        p.seqPan   [i]  = get ("seq_pan_" + idx);
    }

    p.analog        = get ("analog");
    p.master        = get ("master");
}
} // namespace evo
