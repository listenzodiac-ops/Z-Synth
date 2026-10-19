# Z-Synth

A JUCE (C++) VST3 / AU / Standalone synth inspired by the Dave Smith Instruments (Sequential) **Poly Evolver**.

This is an original, from-scratch synth inspired by the architecture and sound character of the Poly Evolver, not a sample-accurate clone. Z-Synth is the product name; change `PRODUCT_NAME` and `COMPANY_NAME` in `CMakeLists.txt` if you want something else.

## What's in it (v2)

| Section | What it does |
|---|---|
| **Voices** | 4, 6 or 8 voices with voice stealing. Poly / Mono / Legato modes (last-note priority), glide (portamento), adjustable pitch-bend range. |
| **Osc 1 + 2 (analog-style)** | PolyBLEP anti-aliased. *Shape* morphs sine -> triangle -> saw -> square, plus semitone, fine, pan and 1-7 voice unison. Osc 2 can be hard-synced to osc 1. |
| **Osc 3 + 4 (digital)** | Band-limited wavetable oscillators with a **128-wave** bank, morphed by the *Wave* knob. FM between them, plus ring mod. |
| **Noise** | White noise ahead of the filter. |
| **Filter** | Moog-style saturating ladder (2-pole / 4-pole), run **2x oversampled**. |
| **2 ADSR envelopes** | Filter and amp. |
| **2 LFOs** | Sine / tri / saw / square / S&H, with **tempo sync** (1/1 ... 1/32, triplets, dotted). |
| **Mod matrix** | 4 slots. Sources: LFO 1/2, filter env, amp env, velocity, mod wheel, pressure (aftertouch), key, random. Destinations: pitch, shape, wave, cutoff, reso, amp, pan, FM, ring, noise, detune. |
| **Effects** | Distortion (Soft / Hard / Fold / Crush, where Crush is downsampling + bit reduction) -> chorus -> delay (tempo-syncable) -> a large, wide "space" reverb (8-line modulated feedback network, my own design, not a copy of any commercial reverb). |
| **Analog** | One knob in the Master section (default 35%, 0 = clean). Slow per-voice drift (pitch, cutoff, shape), small random tolerances per note, and a wandering polarity: a slowly swinging DC offset ahead of the filter plus an even-order term, so the waveform bends and its peaks tilt up and down over a few seconds (extra even harmonics = thicker and warmer). The DC is blocked again after the filter. Loudness is compensated. Not touched by presets. |
| **Step sequencer** | Up to 16 steps, three lanes (pitch / cutoff / pan, all active at once; *Lane* picks which one the knobs edit), per-step on/off, length, order (forward / backward / pendulum / random), swing, rates 1/4 ... 1/16T. Locked to the host. |
| **Presets** | 9 factory presets (also shown to the host as programs) and your own saved presets (SAVE button), stored in `~/Library/Application Support/Z-Synth/Presets`. |
| **Parameter smoothing** | Knobs are smoothed so they never zipper or click. |
| **UI** | Resizable (keeps its shape), blue and white skins. |

## Build on macOS

1. Install the tools (once):
   ```
   xcode-select --install
   brew install cmake
   ```
2. Configure and build (the first run downloads JUCE, so you need internet and git):
   ```
   cd ZSynth
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
   cmake --build build --config Release -j 8
   ```
3. The build copies the plugins into place automatically:
   - VST3: `~/Library/Audio/Plug-Ins/VST3/`
   - AU: `~/Library/Audio/Plug-Ins/Components/`
   - Standalone app: look under `build/ZSynth_artefacts/`

**First test:** launch the Standalone app and click the on-screen keyboard (connect a MIDI keyboard in the app's audio/MIDI settings). If you hear a detuned saw pair with a filter sweep, the whole chain works. Then rescan plugins in your DAW.

**If your DAW won't load it:** ad-hoc sign the plugin so macOS stops blocking it:
```
codesign --force --deep -s - ~/Library/Audio/Plug-Ins/VST3/"Z-Synth.vst3"
```
For Logic (AU), validate with `auval -v aumu Pevo Ynam`.

## Code map (read in this order)

1. `Source/Params.h` / `Params.cpp`: every parameter (ID, range, default). **To add a knob, start here**, then add it to the editor.
2. `Source/SynthVoice.h`: the heart of the synth. `EvolverVoice::renderNextBlock` is the per-sample signal path: oscillators -> ladder filter -> amp envelope. `updateControl()` runs every 16 samples and applies LFOs, pitch and filter modulation.
3. `Source/WaveTables.h`: builds the digital wave bank additively at startup.
4. `Source/StereoDelay.h`, `Effects.h`: the delay, distortion and chorus .
   `Source/EvoSynth.h`: voice limit, mono / legato, glide. `Source/SeqLogic.h`: sequencer timing. `Source/Presets.h`: factory + user presets.
5. `Source/PluginProcessor.*`: the glue between host, MIDI and DSP; saves and restores presets.
6. `Source/PluginEditor.*`: the UI. Panels are built from `Section`, `Knob` and `Choice` helpers.

## Known limitations / honest notes

- **Oscillators 1-2 triangle** is not anti-aliased (fine at normal pitches). The ladder filter is 2x oversampled; the FM and the distortion are not (distortion uses a light interpolation only).
- **Digital waves** are 128 additive recipes of my own, not the Evolver's actual wave ROM.
- **Mono / legato** ignore the sustain pedal.
- **Sequencer lanes**: pitch, cutoff and pan lanes all play at the same time; set unused lanes to 0.
- **Not validated here:** the plug-in has been compile-checked and its DSP tested offline, but the GUI, AU validation (`auval`) and Apple code-signing / notarisation have to be done on a Mac. The build is ad-hoc signed only.
