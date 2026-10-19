#include "PluginEditor.h"
#include "Fonts.h"

namespace ui
{
using juce::Colour;
using juce::ColourGradient;
namespace Colours = juce::Colours;

// ================================================================== skins
static int currentSkin = 0;

static const Theme blueSkin
{
    /* plateTop    */ Colour (0xff15438a), /* plateBottom */ Colour (0xff050f22), /* plateGlow */ Colour (0x334aa8ff),
    /* vignette    */ 0.67f,
    /* panelTop    */ Colour (0x66000000), /* panelBottom */ Colour (0x2e000000),
    /* panelBorder */ Colour (0x4090c4ff), /* panelBevel  */ Colour (0x0dffffff),
    /* text        */ Colour (0xffdbe7f8), /* textDim     */ Colour (0xff97b0d2), /* tick */ Colour (0xff97b0d2),
    /* logoTop     */ Colour (0xfff7fbff), /* logoBottom  */ Colour (0xff7f9cc4), /* subtitle */ Colour (0xff4db8ff),
    /* knobShadow  */ 0.80f,
    /* bloom       */ 1.0f
};

static const Theme whiteSkin
{
    /* plateTop    */ Colour (0xfff6f8fb), /* plateBottom */ Colour (0xffa9b2c0), /* plateGlow */ Colour (0x66ffffff),
    /* vignette    */ 0.26f,
    /* panelTop    */ Colour (0x30000000), /* panelBottom */ Colour (0x12000000),
    /* panelBorder */ Colour (0x5a202a3a), /* panelBevel  */ Colour (0xa0ffffff),
    /* text        */ Colour (0xff1a2230), /* textDim     */ Colour (0xff44526a), /* tick */ Colour (0xff2b3548),
    /* logoTop     */ Colour (0xff1b2331), /* logoBottom  */ Colour (0xff5a667b), /* subtitle */ Colour (0xff1f6fd1),
    /* knobShadow  */ 0.55f,
    /* bloom       */ 0.9f
};

const Theme& theme()          { return currentSkin == 1 ? whiteSkin : blueSkin; }
void setSkin (int index)      { currentSkin = index == 1 ? 1 : 0; }
int  getSkin()                { return currentSkin; }

// =========================================================== LookAndFeel
EvolverLookAndFeel::EvolverLookAndFeel()
{
    setDefaultSansSerifTypeface (typefaceFor (Face::bold));   // popups and dialogs use Inter too
    applyTheme();
}

void EvolverLookAndFeel::applyTheme()
{
    setColour (juce::Label::textColourId,                      theme().text);
    setColour (juce::ComboBox::textColourId,                   accent);
    setColour (juce::PopupMenu::backgroundColourId,            Colour (0xff07142b));
    setColour (juce::PopupMenu::textColourId,                  Colour (0xffdbe7f8));
    setColour (juce::PopupMenu::highlightedBackgroundColourId, Colour (0xff1b5fa8));
    setColour (juce::PopupMenu::highlightedTextColourId,       Colours::white);
    setColour (juce::BubbleComponent::backgroundColourId,      Colour (0xf008162e));
    setColour (juce::BubbleComponent::outlineColourId,         accent.withAlpha (0.6f));
    setColour (juce::TooltipWindow::textColourId,              accentHot);
}

void EvolverLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int w, int h,
                                           float pos, float startA, float endA, juce::Slider& s)
{
    const auto bounds = juce::Rectangle<int> (x, y, w, h).toFloat();
    const float scaleR = juce::jmin (bounds.getWidth(), bounds.getHeight()) * 0.5f - 1.0f;
    const auto  c      = bounds.getCentre();
    const float bodyR  = scaleR * 0.76f;
    const float angle  = startA + pos * (endA - startA);

    // --- printed scale: 11 ticks around the knob, larger at the ends and the middle
    for (int i = 0; i <= 10; ++i)
    {
        const float a = startA + (float) i / 10.0f * (endA - startA);
        const bool major = (i == 0 || i == 5 || i == 10);
        const float r1 = scaleR - (major ? 5.0f : 2.8f);
        g.setColour (theme().tick.withAlpha (major ? 0.95f : 0.6f));
        g.drawLine (c.x + r1 * std::sin (a), c.y - r1 * std::cos (a),
                    c.x + scaleR * std::sin (a), c.y - scaleR * std::cos (a), major ? 1.7f : 1.0f);
    }

    // --- soft drop shadow so the knob sits above the panel
    juce::Path body;
    body.addEllipse (c.x - bodyR, c.y - bodyR, bodyR * 2.0f, bodyR * 2.0f);
    juce::DropShadow (Colours::black.withAlpha (theme().knobShadow), juce::roundToInt (bodyR * 0.6f),
                      { juce::roundToInt (bodyR * 0.10f), juce::roundToInt (bodyR * 0.34f) }).drawForPath (g, body);

    // --- skirt (wide base of the knob)
    g.setGradientFill (ColourGradient (Colour (0xff59616f), c.x, c.y - bodyR,
                                       Colour (0xff040508), c.x, c.y + bodyR, false));
    g.fillPath (body);

    // bevelled rim: bright on the upper left, dark on the lower right
    g.setGradientFill (ColourGradient (Colours::white.withAlpha (0.65f), c.x - bodyR * 0.7f, c.y - bodyR * 0.7f,
                                       Colours::white.withAlpha (0.0f),  c.x + bodyR * 0.2f, c.y + bodyR * 0.2f, false));
    g.drawEllipse (c.x - bodyR + 0.6f, c.y - bodyR + 0.6f, bodyR * 2.0f - 1.2f, bodyR * 2.0f - 1.2f, 1.3f);

    // fine knurling on the skirt
    g.setColour (Colours::black.withAlpha (0.35f));
    for (int i = 0; i < 48; ++i)
    {
        const float a = juce::MathConstants<float>::twoPi * (float) i / 48.0f;
        g.drawLine (c.x + bodyR * 0.90f * std::sin (a), c.y - bodyR * 0.90f * std::cos (a),
                    c.x + bodyR * 0.99f * std::sin (a), c.y - bodyR * 0.99f * std::cos (a), 0.8f);
    }

    // --- cap (raised top of the knob)
    const float capR = bodyR * 0.80f;
    juce::Path cap;
    cap.addEllipse (c.x - capR, c.y - capR, capR * 2.0f, capR * 2.0f);

    g.setGradientFill (ColourGradient (Colour (0xff434a57), c.x - capR * 0.35f, c.y - capR * 0.5f,
                                       Colour (0xff07080b), c.x + capR * 0.7f,  c.y + capR * 0.9f, true));
    g.fillPath (cap);

    g.saveState();
    g.reduceClipRegion (cap);

    for (int k = 1; k <= 9; ++k)
    {
        const float rr = capR * (float) k / 9.0f;
        g.setColour (Colours::white.withAlpha ((k & 1) ? 0.045f : 0.02f));
        g.drawEllipse (c.x - rr, c.y - rr, rr * 2.0f, rr * 2.0f, 0.7f);
    }

    g.setGradientFill (ColourGradient (Colours::white.withAlpha (0.42f), c.x - capR * 0.4f, c.y - capR * 0.55f,
                                       Colours::white.withAlpha (0.0f),  c.x - capR * 0.4f + capR * 0.85f, c.y - capR * 0.55f, true));
    g.fillRect (bounds);
    g.restoreState();

    g.setColour (Colours::black.withAlpha (0.7f));
    g.drawEllipse (c.x - capR, c.y - capR, capR * 2.0f, capR * 2.0f, 1.0f);

    // --- pointer line
    juce::Path pointer;
    pointer.addRoundedRectangle (-1.7f, -capR * 0.93f, 3.4f, capR * 0.66f, 1.5f);
    const auto xf = juce::AffineTransform::rotation (angle).translated (c.x, c.y);

    g.setColour (Colours::black.withAlpha (0.55f));
    g.fillPath (pointer, xf.translated (0.9f, 1.3f));

    g.setColour (s.isMouseOverOrDragging() ? accentHot : Colour (0xfff4f8ff));
    g.fillPath (pointer, xf);
}

void EvolverLookAndFeel::drawComboBox (juce::Graphics& g, int w, int h, bool, int, int, int, int, juce::ComboBox& box)
{
    const auto r = juce::Rectangle<float> (0.0f, 0.0f, (float) w, (float) h).reduced (0.5f);

    g.setGradientFill (ColourGradient (Colour (0xff020913), 0, r.getY(), Colour (0xff0b2347), 0, r.getBottom(), false));
    g.fillRoundedRectangle (r, 4.0f);

    g.setColour (Colour (0xff2f5b97).withAlpha (box.isEnabled() ? 1.0f : 0.4f));
    g.drawRoundedRectangle (r, 4.0f, 1.0f);

    g.setColour (Colours::black.withAlpha (0.55f));
    g.drawLine (r.getX() + 3, r.getY() + 1.5f, r.getRight() - 3, r.getY() + 1.5f, 1.0f);

    juce::Path arrow;
    const float ax = r.getRight() - 9.0f, ay = r.getCentreY();
    arrow.addTriangle (ax - 3.5f, ay - 1.8f, ax + 3.5f, ay - 1.8f, ax, ay + 2.6f);
    g.setColour (accent);
    g.fillPath (arrow);
}

void EvolverLookAndFeel::drawToggleButton (juce::Graphics& g, juce::ToggleButton& b, bool highlighted, bool)
{
    const auto r = b.getLocalBounds().toFloat().reduced (0.5f);
    const bool on = b.getToggleState();

    if (on)
        g.setGradientFill (ColourGradient (Colour (0xff3b8fe6), 0, r.getY(), Colour (0xff0f4a94), 0, r.getBottom(), false));
    else
        g.setGradientFill (ColourGradient (Colour (0xff1a2b49), 0, r.getY(), Colour (0xff060d1b), 0, r.getBottom(), false));

    g.fillRoundedRectangle (r, 4.5f);

    g.setColour (on ? accent.withAlpha (0.9f) : Colour (0xff2f5b97));
    g.drawRoundedRectangle (r, 4.5f, 1.0f);

    // top bevel highlight on the key
    g.setColour (Colours::white.withAlpha (on ? 0.30f : 0.10f));
    g.drawLine (r.getX() + 4, r.getY() + 1.5f, r.getRight() - 4, r.getY() + 1.5f, 1.0f);

    if (highlighted)
    {
        g.setColour (Colours::white.withAlpha (0.08f));
        g.fillRoundedRectangle (r, 4.5f);
    }

    juce::Font f = font (Face::bold, 11.0f, 1.1f);
    g.setFont (f);
    g.setColour (on ? Colours::white : Colour (0xff6f86a8));
    g.drawText (on ? "ON" : "OFF", b.getLocalBounds(), juce::Justification::centred, false);
}

void EvolverLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& b, const juce::Colour&, bool highlighted, bool down)
{
    const auto r = b.getLocalBounds().toFloat().reduced (0.5f);
    const float lift = down ? 0.0f : (highlighted ? 0.12f : 0.0f);

    g.setGradientFill (ColourGradient (Colour (0xff1c3157).brighter (lift), 0, r.getY(),
                                       Colour (0xff07101f).brighter (lift), 0, r.getBottom(), false));
    g.fillRoundedRectangle (r, 4.0f);
    g.setColour (Colour (0xff2f5b97));
    g.drawRoundedRectangle (r, 4.0f, 1.0f);
    g.setColour (Colours::white.withAlpha (down ? 0.04f : 0.12f));
    g.drawLine (r.getX() + 3, r.getY() + 1.5f, r.getRight() - 3, r.getY() + 1.5f, 1.0f);
}

void EvolverLookAndFeel::drawButtonText (juce::Graphics& g, juce::TextButton& b, bool, bool)
{
    juce::Font f = font (Face::bold, 11.0f, 1.1f);
    g.setFont (f);
    g.setColour (accent);
    g.drawText (b.getButtonText(), b.getLocalBounds(), juce::Justification::centred, false);
}

juce::Font EvolverLookAndFeel::getComboBoxFont (juce::ComboBox&)
{
    return font (Face::bold, 11.0f);
}

void EvolverLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
{
    label.setBounds (5, 1, box.getWidth() - 18, box.getHeight() - 2);
    label.setFont (getComboBoxFont (box));
}

// Shared by Knob / Choice / Switch: the small silk-screened caption under each control.
static void drawCaption (juce::Graphics& g, juce::Rectangle<int> area, const juce::String& text, bool active)
{
    g.setFont (font (Face::bold, 10.0f));
    g.setColour (active ? accent : theme().text);
    g.drawText (text, area.removeFromBottom (15), juce::Justification::centred, false);
}

// ================================================================= Knob
Knob::Knob (juce::AudioProcessorValueTreeState& state, const juce::String& paramID, const juce::String& text)
    : state (state), labelText (text.toUpperCase())
{
    slider.setRotaryParameters (juce::MathConstants<float>::pi * 1.25f,
                                juce::MathConstants<float>::pi * 2.75f, true);
    slider.setMouseDragSensitivity (200);
    slider.setPopupDisplayEnabled (true, true, nullptr);
    addAndMakeVisible (slider);

    attachment = std::make_unique<SliderAttachment> (state, paramID, slider);

    if (auto* param = state.getParameter (paramID))
    {
        slider.setDoubleClickReturnValue (true, param->convertFrom0to1 (param->getDefaultValue()));

        const double step = param->getNormalisableRange().interval;
        const int decimals = step >= 1.0 ? 0 : (step >= 0.1 ? 1 : 2);
        const juce::String suffix = param->getLabel().isEmpty() ? juce::String() : " " + param->getLabel();

        slider.textFromValueFunction = [decimals, suffix] (double v)
        {
            if (std::abs (v) >= 1000.0)
                return juce::String (juce::roundToInt (v)) + suffix;

            return juce::String (v, decimals) + suffix;
        };
    }
}

void Knob::rebind (const juce::String& paramID)
{
    attachment.reset();
    attachment = std::make_unique<SliderAttachment> (state, paramID, slider);

    if (auto* param = state.getParameter (paramID))
        slider.setDoubleClickReturnValue (true, param->convertFrom0to1 (param->getDefaultValue()));
}

void Knob::setActive (bool shouldBeActive)
{
    if (active != shouldBeActive)
    {
        active = shouldBeActive;
        repaint();
    }
}

void Knob::paint (juce::Graphics& g)
{
    drawCaption (g, getLocalBounds(), labelText, active);
}

void Knob::resized()
{
    auto area = getLocalBounds();
    area.removeFromBottom (15);
    const int size = juce::jmin (area.getWidth() - 2, area.getHeight(), 78);
    slider.setBounds (area.withSizeKeepingCentre (size, size));
}

// ============================================================== Choice
Choice::Choice (juce::AudioProcessorValueTreeState& state, const juce::String& paramID, const juce::String& text)
    : labelText (text.toUpperCase())
{
    if (auto* choice = dynamic_cast<juce::AudioParameterChoice*> (state.getParameter (paramID)))
        box.addItemList (choice->choices, 1);

    addAndMakeVisible (box);
    attachment = std::make_unique<ComboBoxAttachment> (state, paramID, box);
}

void Choice::paint (juce::Graphics& g)
{
    drawCaption (g, getLocalBounds(), labelText, false);
}

void Choice::resized()
{
    auto area = getLocalBounds();
    area.removeFromBottom (15);
    box.setBounds (area.withSizeKeepingCentre (juce::jmax (10, area.getWidth() - 8), 22));
}

// ============================================================== Switch
Switch::Switch (juce::AudioProcessorValueTreeState& state, const juce::String& paramID, const juce::String& text)
    : labelText (text.toUpperCase())
{
    addAndMakeVisible (button);
    attachment = std::make_unique<ButtonAttachment> (state, paramID, button);
}

void Switch::paint (juce::Graphics& g)
{
    drawCaption (g, getLocalBounds(), labelText, false);
}

void Switch::resized()
{
    auto area = getLocalBounds();
    area.removeFromBottom (15);
    button.setBounds (area.withSizeKeepingCentre (juce::jmin (46, juce::jmax (10, area.getWidth() - 8)), 24));
}

// ============================================================ StepCell
void StepButton::paintButton (juce::Graphics& g, bool highlighted, bool)
{
    // A small round lamp. Dark glass when idle, glowing blue while its step is playing.
    // A step that is switched off is flatter and has no rim, so on / off is still readable.
    const bool on = getToggleState();
    const auto c  = getLocalBounds().toFloat().getCentre();
    const float r = juce::jmin (6.0f, (float) juce::jmin (getWidth(), getHeight()) * 0.5f - 1.0f);

    const bool lit = playing && on;
    const float L = lit ? 1.0f : 0.0f;

    if (lit)
    {
        juce::ColourGradient bloom (accent.withAlpha (0.65f * theme().bloom), c.x, c.y,
                                    accent.withAlpha (0.0f), c.x + r * 3.2f, c.y, true);
        bloom.addColour (0.35, accent.withAlpha (0.28f * theme().bloom));
        g.setGradientFill (bloom);
        g.fillEllipse (c.x - r * 3.2f, c.y - r * 3.2f, r * 6.4f, r * 6.4f);
    }

    // bezel seat
    g.setColour (Colour (0xff04070d));
    g.fillEllipse (c.x - r - 1.5f, c.y - r - 1.5f, (r + 1.5f) * 2.0f, (r + 1.5f) * 2.0f);

    // glass
    if (lit)
        g.setGradientFill (ColourGradient (Colour (0xfff2fbff), c.x, c.y, Colour (0xff1a78d8), c.x + r, c.y, true));
    else if (on)
        g.setGradientFill (ColourGradient (Colour (0xff10233f), c.x - r * 0.3f, c.y - r * 0.4f, Colour (0xff040a15), c.x + r, c.y + r, true));
    else
        g.setColour (Colour (0xff070b12));

    g.fillEllipse (c.x - r, c.y - r, r * 2.0f, r * 2.0f);

    // thin rim: blue on an enabled step, faint on a disabled one
    g.setColour (lit ? accentHot.withAlpha (0.9f) : (on ? Colour (0xff2f5b97) : Colour (0xff1b2535)));
    g.drawEllipse (c.x - r, c.y - r, r * 2.0f, r * 2.0f, 1.0f);

    // little glint so it reads as glass
    g.setColour (Colours::white.withAlpha (lit ? 0.75f : (on ? 0.20f : 0.07f)));
    g.fillEllipse (c.x - r * 0.55f, c.y - r * 0.75f, r * 0.7f, r * 0.4f);

    if (highlighted)
    {
        g.setColour (Colours::white.withAlpha (0.10f));
        g.fillEllipse (c.x - r, c.y - r, r * 2.0f, r * 2.0f);
    }
    juce::ignoreUnused (L);
}

StepCell::StepCell (juce::AudioProcessorValueTreeState& state, int stepIndex)
    : knob (state, "seq_step_" + juce::String (stepIndex + 1), juce::String (stepIndex + 1))
{
    addAndMakeVisible (knob);
    addAndMakeVisible (button);
    attachment = std::make_unique<ButtonAttachment> (state, "seq_on_" + juce::String (stepIndex + 1), button);
}

void StepCell::resized()
{
    auto area = getLocalBounds();
    auto row = area.removeFromBottom (14);
    button.setBounds (row.withSizeKeepingCentre (juce::jmin (26, row.getWidth() - 6), 14));
    knob.setBounds (area);
}

// ============================================================== LfoLed
LfoLed::LfoLed (juce::AudioProcessorValueTreeState& state, int i, const std::atomic<float>& hostBpm)
    : bpm (hostBpm)
{
    sync   = state.getRawParameterValue (evo::lfoID (i, "sync"));
    rate   = state.getRawParameterValue (evo::lfoID (i, "rate"));
    shape  = state.getRawParameterValue (evo::lfoID (i, "shape"));
    amount = state.getRawParameterValue (evo::lfoID (i, "amount"));
    dest   = state.getRawParameterValue (evo::lfoID (i, "dest"));

    held = rng.nextFloat() * 2.0f - 1.0f;
    setInterceptsMouseClicks (false, false);
}

void LfoLed::tick (float dt)
{
    float rateHz = rate->load();
    const int syncIdx = juce::jlimit (0, evo::numSyncDivisions - 1, (int) (sync->load() + 0.5f));
    if (syncIdx > 0)
        rateHz = (bpm.load() / 60.0f) / (float) evo::syncBeats[syncIdx];
    const int   sh     = (int) (shape->load() + 0.5f);
    const float amt    = juce::jmin (1.0f, std::abs (amount->load()));
    const bool  active = ((int) (dest->load() + 0.5f) != evo::destOff) && amt > 0.01f;

    // Several sub-steps per frame so fast LFOs average out like a real lamp does.
    constexpr int sub = 8;
    const float sdt = dt / (float) sub;

    for (int n = 0; n < sub; ++n)
    {
        phase += rateHz * sdt;

        if (phase >= 1.0f)
        {
            phase -= std::floor (phase);
            held = rng.nextFloat() * 2.0f - 1.0f;
        }

        float v;
        switch (sh)
        {
            case evo::lfoSine:     v = std::sin (juce::MathConstants<float>::twoPi * phase); break;
            case evo::lfoTriangle: v = 1.0f - 4.0f * std::abs (phase - 0.5f);               break;
            case evo::lfoSaw:      v = 2.0f * phase - 1.0f;                                 break;
            case evo::lfoSquare:   v = phase < 0.5f ? 1.0f : -1.0f;                         break;
            default:               v = held;                                                break;
        }

        const float target = active ? 0.05f + (0.30f + 0.65f * amt) * (v * 0.5f + 0.5f)
                                    : 0.03f;

        // the filament lights up quickly and cools down slower
        const float tau = target > level ? 0.012f : 0.055f;
        level += (target - level) * (1.0f - std::exp (-sdt / tau));
    }

    if (std::abs (level - painted) > 0.004f)
        repaint();
}

void LfoLed::paint (juce::Graphics& g)
{
    painted = level;
    const float L = juce::jlimit (0.0f, 1.0f, level);
    const auto  c = getLocalBounds().toFloat().getCentre();
    const float lensR = 6.5f, bezR = lensR + 2.6f;

    // --- light spilling onto the panel
    if (L > 0.04f)
    {
        const float a = L * 0.60f * theme().bloom;
        ColourGradient bloom (accent.withAlpha (a), c.x, c.y, accent.withAlpha (0.0f), c.x + 27.0f, c.y, true);
        bloom.addColour (0.28, accent.withAlpha (a * 0.55f));
        g.setGradientFill (bloom);
        g.fillEllipse (c.x - 27.0f, c.y - 27.0f, 54.0f, 54.0f);
    }

    // --- bezel (the metal seat the glass dome sits in), with a contact shadow
    juce::Path seat;
    seat.addEllipse (c.x - bezR, c.y - bezR, bezR * 2.0f, bezR * 2.0f);
    juce::DropShadow (Colours::black.withAlpha (0.55f), 5, { 1, 2 }).drawForPath (g, seat);

    g.setGradientFill (ColourGradient (Colour (0xffd5dce8), c.x - bezR * 0.7f, c.y - bezR * 0.8f,
                                       Colour (0xff0b0e14), c.x + bezR * 0.7f, c.y + bezR * 0.9f, false));
    g.fillPath (seat);

    // the bezel edge picks up colour from the lit lamp
    g.setColour (accent.withAlpha (L * 0.45f));
    g.drawEllipse (c.x - bezR + 0.9f, c.y - bezR + 0.9f, (bezR - 0.9f) * 2.0f, (bezR - 0.9f) * 2.0f, 1.0f);

    // dark groove between bezel and glass
    g.setColour (Colours::black.withAlpha (0.85f));
    g.drawEllipse (c.x - lensR - 0.9f, c.y - lensR - 0.9f, (lensR + 0.9f) * 2.0f, (lensR + 0.9f) * 2.0f, 1.6f);

    // --- the glass dome: dark blue glass when off, glowing blue with a white-hot centre when lit
    juce::Path dome;
    dome.addEllipse (c.x - lensR, c.y - lensR, lensR * 2.0f, lensR * 2.0f);

    const float e = std::pow (L, 0.8f);
    auto mix = [e] (Colour off, Colour on) { return off.interpolatedWith (on, e); };

    ColourGradient glass (mix (Colour (0xff0b1d3a), Colour (0xfff2fbff)), c.x, c.y + 0.3f,
                          mix (Colour (0xff030913), Colour (0xff1170cc)), c.x + lensR, c.y + 0.3f, true);
    glass.addColour (0.30, mix (Colour (0xff0a2147), Colour (0xffa4e0ff)));
    glass.addColour (0.65, mix (Colour (0xff071a38), Colour (0xff38a6f5)));
    g.setGradientFill (glass);
    g.fillPath (dome);

    g.saveState();
    g.reduceClipRegion (dome);

    // the LED die, seen through the glass
    const float dieR = 2.4f + 2.4f * L;
    g.setGradientFill (ColourGradient (accentHot.withAlpha (0.25f + 0.75f * L), c.x, c.y + 0.3f,
                                       accentHot.withAlpha (0.0f), c.x + dieR, c.y + 0.3f, true));
    g.fillEllipse (c.x - dieR, c.y - dieR + 0.3f, dieR * 2.0f, dieR * 2.0f);

    g.setColour (Colours::white.withAlpha (0.15f + 0.85f * L));   // the tiny hot point of the emitter
    g.fillEllipse (c.x - 1.0f, c.y - 0.7f, 2.0f, 2.0f);

    // thick glass darkens toward its edge
    ColourGradient edge (Colours::transparentBlack, c.x, c.y, Colours::black.withAlpha (0.55f), c.x + lensR, c.y, true);
    edge.addColour (0.62, Colours::transparentBlack);
    g.setGradientFill (edge);
    g.fillPath (dome);

    // soft window reflection across the upper left of the dome
    g.setGradientFill (ColourGradient (Colours::white.withAlpha (0.60f), c.x, c.y - lensR * 0.55f,
                                       Colours::white.withAlpha (0.04f), c.x, c.y + lensR * 0.10f, false));
    g.fillEllipse (c.x - lensR * 0.62f, c.y - lensR * 0.88f, lensR * 1.24f, lensR * 0.78f);

    // small sharp glint
    g.setColour (Colours::white.withAlpha (0.90f));
    g.fillEllipse (c.x - lensR * 0.52f, c.y - lensR * 0.66f, lensR * 0.34f, lensR * 0.20f);

    // faint bounce light along the lower right rim
    juce::Path bounce;
    bounce.addCentredArc (c.x, c.y, lensR * 0.82f, lensR * 0.82f, 0.0f,
                          juce::degreesToRadians (110.0f), juce::degreesToRadians (200.0f), true);
    g.setColour (Colour (0xff9fd8ff).withAlpha (0.16f + 0.25f * L));
    g.strokePath (bounce, juce::PathStrokeType (1.1f));

    g.restoreState();

    // outer rim of the glass
    g.setColour (Colours::black.withAlpha (0.55f));
    g.drawEllipse (c.x - lensR, c.y - lensR, lensR * 2.0f, lensR * 2.0f, 0.8f);
}

// ============================================================ SkinSwitch
void SkinSwitch::paint (juce::Graphics& g)
{
    juce::Font f = font (Face::bold, 10.0f);
    f.setExtraKerningFactor (0.2f);
    g.setFont (f);
    g.setColour (theme().text);
    g.drawText ("SKIN", 0, 0, 50, getHeight(), juce::Justification::centredLeft, false);

    for (int i = 0; i < 2; ++i)
    {
        const float cx = 70.0f + (float) i * 34.0f, cy = (float) getHeight() * 0.5f, r = 9.0f;

        if (i == 0)
            g.setGradientFill (ColourGradient (Colour (0xff6fd0ff), cx - 3.0f, cy - 4.0f, Colour (0xff0b3470), cx + 6.0f, cy + 7.0f, true));
        else
            g.setGradientFill (ColourGradient (Colour (0xffffffff), cx - 3.0f, cy - 4.0f, Colour (0xff9aa5b6), cx + 6.0f, cy + 7.0f, true));

        g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);
        g.setColour (Colours::black.withAlpha (0.55f));
        g.drawEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f, 1.0f);

        if (i == current)
        {
            g.setColour (getSkin() == 1 ? Colour (0xff1a2230) : accentHot);
            g.drawEllipse (cx - r - 3.5f, cy - r - 3.5f, (r + 3.5f) * 2.0f, (r + 3.5f) * 2.0f, 1.4f);
        }
    }
}

void SkinSwitch::mouseDown (const juce::MouseEvent& e)
{
    if (e.x > 50 && onPick)
        onPick (e.x > 87 ? 1 : 0);
}

// ============================================================== Section
Section::Section (juce::AudioProcessorValueTreeState& s, const juce::String& titleText)
    : state (s), title (titleText) {}

Knob* Section::addKnob (const juce::String& paramID, const juce::String& label)
{
    auto* k = new Knob (state, paramID, label);
    items.add (k);
    addAndMakeVisible (k);
    return k;
}

void Section::addChoice (const juce::String& paramID, const juce::String& label)
{
    addAndMakeVisible (items.add (new Choice (state, paramID, label)));
}

void Section::addCustom (juce::Component* c)
{
    items.add (c);
    addAndMakeVisible (c);
}

void Section::addSwitch (const juce::String& paramID, const juce::String& label)
{
    addAndMakeVisible (items.add (new Switch (state, paramID, label)));
}

void Section::paint (juce::Graphics& g)
{
    const auto& t = theme();
    const auto r = getLocalBounds().toFloat().reduced (2.0f);

    // recessed panel
    g.setGradientFill (ColourGradient (t.panelTop, 0, r.getY(), t.panelBottom, 0, r.getBottom(), false));
    g.fillRoundedRectangle (r, 7.0f);

    g.setColour (t.panelBorder);
    g.drawRoundedRectangle (r, 7.0f, 1.0f);

    g.setColour (t.panelBevel);
    g.drawRoundedRectangle (r.translated (0.0f, 1.0f), 7.0f, 1.0f);

    // silk-screened title with a rule running to the right edge
    juce::Font f = font (Face::bold, 11.0f);
    f.setExtraKerningFactor (0.16f);

    const auto txt = title.toUpperCase();
    juce::GlyphArrangement ga;
    ga.addLineOfText (f, txt, 0.0f, 0.0f);
    const float tw = ga.getBoundingBox (0, -1, true).getWidth();

    g.setFont (f);
    g.setColour (t.text);
    g.drawText (txt, juce::Rectangle<float> (r.getX() + 12.0f, r.getY() + 6.0f, tw + 6.0f, 16.0f),
                juce::Justification::centredLeft, false);

    g.setColour (t.panelBorder.withMultipliedAlpha (0.8f));
    const float lineEnd = r.getRight() - (hasLed ? 46.0f : 10.0f);
    g.drawLine (r.getX() + 20.0f + tw, r.getY() + 14.0f, lineEnd, r.getY() + 14.0f, 1.0f);
}

void Section::resized()
{
    auto area = getLocalBounds().reduced (6, 0);
    area.removeFromTop (30);
    area.removeFromBottom (4);

    if (items.isEmpty())
        return;

    const int w = area.getWidth() / items.size();

    for (auto* item : items)
        item->setBounds (area.removeFromLeft (w));
}
} // namespace ui

// =================================================================== Editor
PolyEvolverAudioProcessorEditor::PolyEvolverAudioProcessorEditor (PolyEvolverAudioProcessor& p)
    : AudioProcessorEditor (&p),
      proc (p),
      skinAttach (*p.apvts.getParameter ("skin"), [this] (float v) { applySkin ((int) (v + 0.5f)); })
{
    setLookAndFeel (&laf);

    // ---- Row 0: all four oscillators ----
    for (int i = 0; i < 2; ++i)
    {
        auto& s = addSection (0, "Analog Osc " + juce::String (i + 1));
        s.addKnob (evo::oscID (i, "level"),  "Level");
        s.addKnob (evo::oscID (i, "semi"),   "Semi");
        s.addKnob (evo::oscID (i, "fine"),   "Fine");
        s.addKnob (evo::oscID (i, "shape"),  "Shape");
        s.addKnob (evo::oscID (i, "pan"),    "Pan");
        s.addKnob (evo::oscID (i, "uni"),    "Unison");
        s.addKnob (evo::oscID (i, "unidet"), "Detune");
    }

    // ---- Row 0 (cont.): digital oscillators ----
    for (int i = 2; i < 4; ++i)
    {
        auto& s = addSection (0, "Digital Osc " + juce::String (i + 1));
        s.addKnob (evo::oscID (i, "level"), "Level");
        s.addKnob (evo::oscID (i, "semi"),  "Semi");
        s.addKnob (evo::oscID (i, "fine"),  "Fine");
        auto* wave = s.addKnob (evo::oscID (i, "shape"), "Wave");
        s.addKnob (evo::oscID (i, "pan"),   "Pan");

        wave->getSlider().textFromValueFunction = [] (double v)
        {
            return "Wave " + juce::String (1 + juce::roundToInt (v * (evo::numWaves - 1)));
        };
    }

    // ---- Row 1: amp envelope, filter, filter envelope, oscillator modulation ----
    {
        auto& ae = addSection (1, "Amp Envelope");
        ae.addKnob ("amp_attack",  "Atk");  ae.addKnob ("amp_decay",   "Dec");
        ae.addKnob ("amp_sustain", "Sus");  ae.addKnob ("amp_release", "Rel");

        auto& f = addSection (1, "Filter");
        f.addKnob   ("cutoff",    "Cutoff");
        f.addKnob   ("resonance", "Reso");
        f.addChoice ("poles",     "Poles");
        f.addKnob   ("filter_env", "Env Amt");
        f.addKnob   ("key_track", "Key Trk");

        auto& fe = addSection (1, "Filter Envelope");
        fe.addKnob ("flt_attack",  "Atk");  fe.addKnob ("flt_decay",   "Dec");
        fe.addKnob ("flt_sustain", "Sus");  fe.addKnob ("flt_release", "Rel");
    }

    {
        auto& m = addSection (1, "Osc Mod + Noise");
        m.addChoice ("osc_sync",    "Sync");
        m.addKnob   ("fm_4to3",     "FM 4>3");
        m.addKnob   ("fm_3to4",     "FM 3>4");
        m.addKnob   ("ring_mod",    "Ring");
        m.addKnob   ("noise_level", "Noise");
    }

    // ---- Row 2: LFOs (with glass-dome lights) and voice handling ----
    for (int i = 0; i < evo::numLfos; ++i)
    {
        auto& l = addSection (2, "LFO " + juce::String (i + 1));
        l.addKnob   (evo::lfoID (i, "rate"),   "Rate");
        l.addChoice (evo::lfoID (i, "sync"),   "Sync");
        l.addChoice (evo::lfoID (i, "shape"),  "Wave");
        l.addKnob   (evo::lfoID (i, "amount"), "Amount");
        l.addChoice (evo::lfoID (i, "dest"),   "Dest");
        l.setReservesLedSpace (true);
        lfoSections[i] = &l;
    }

    {
        auto& v = addSection (2, "Voices");
        v.addChoice ("voices",     "Voices");
        v.addChoice ("voice_mode", "Mode");
        v.addKnob   ("glide",      "Glide");
        v.addKnob   ("bend_range", "Bend");
    }

    // ---- Row 3: modulation matrix ----
    for (int i = 0; i < evo::numSlots; ++i)
    {
        auto& m = addSection (3, "Mod " + juce::String (i + 1));
        m.addChoice (evo::mmID (i, "src"), "Source");
        m.addChoice (evo::mmID (i, "dst"), "Dest");
        m.addKnob   (evo::mmID (i, "amt"), "Amount");
    }

    // ---- Row 4: effects and master ----
    {
        auto& d = addSection (4, "Distortion");
        d.addChoice ("dist_type", "Type");  d.addKnob ("dist_drive", "Drive");  d.addKnob ("dist_mix", "Mix");

        auto& c = addSection (4, "Chorus");
        c.addKnob ("chorus_rate", "Rate");  c.addKnob ("chorus_depth", "Depth");  c.addKnob ("chorus_mix", "Mix");

        auto& dl = addSection (4, "Delay");
        dl.addKnob   ("delay_time", "Time");   dl.addChoice ("delay_sync", "Sync");
        dl.addKnob   ("delay_feedback", "Fdbk");
        dl.addKnob   ("delay_tone", "Tone");   dl.addKnob   ("delay_mix", "Mix");

        auto& r = addSection (4, "Reverb");
        r.addKnob ("reverb_size", "Size");  r.addKnob ("reverb_damp", "Damp");  r.addKnob ("reverb_mix", "Mix");

        auto& m = addSection (4, "Master");
        m.addKnob ("analog", "Analog");  m.addKnob ("master", "Volume");
    }

    // ---- Row 5: sequencer, locked to the DAW's tempo ----
    {
        auto& q = addSection (5, "Step Sequencer");
        q.addChoice ("seq_on",     "Seq");
        q.addChoice ("seq_gate",   "Gate");
        q.addChoice ("seq_rate",   "Rate");
        q.addChoice ("seq_dest",   "Lane");
        q.addKnob   ("seq_length", "Length");
        q.addChoice ("seq_dir",    "Order");
        q.addKnob   ("seq_swing",  "Swing");

        auto* destPtr = proc.apvts.getRawParameterValue ("seq_dest");

        for (int i = 0; i < 16; ++i)
        {
            auto* cell = new ui::StepCell (proc.apvts, i);
            q.addCustom (cell);
            stepCells[i] = cell;
            auto* k = &cell->getKnob();

            // pitch steps click into whole semitones; cutoff and pan stay smooth
            k->getSlider().snapper = [destPtr] (double v)
            {
                return (int) (destPtr->load() + 0.5f) == 0 ? std::round (v * 12.0) / 12.0 : v;
            };

            // the pop-up reads in the units of whatever lane is being edited
            k->getSlider().textFromValueFunction = [destPtr] (double v) -> juce::String
            {
                const int d = (int) (destPtr->load() + 0.5f);

                if (d == 0)
                {
                    const int st = juce::roundToInt (v * 12.0);
                    return (st > 0 ? "+" : "") + juce::String (st) + " st";
                }

                if (d == 1)
                    return (v >= 0.0 ? "+" : "") + juce::String (v * 3.0, 1) + " oct";

                if (std::abs (v) < 0.005)
                    return "Center";

                return (v < 0.0 ? "L " : "R ") + juce::String (juce::roundToInt (std::abs (v) * 100.0));
            };
        }
    }

    for (int i = 0; i < evo::numLfos; ++i)
        addAndMakeVisible (leds.add (new ui::LfoLed (proc.apvts, i, proc.hostBpm)));

    skinSwitch.onPick = [this] (int idx) { skinAttach.setValueAsCompleteGesture ((float) idx); };
    addAndMakeVisible (skinSwitch);

    // ---- preset bar ----
    addAndMakeVisible (presetBox);
    addAndMakeVisible (prevButton);
    addAndMakeVisible (nextButton);
    addAndMakeVisible (saveButton);
    presetBox.setJustificationType (juce::Justification::centredLeft);
    presetBox.onChange = [this]
    {
        const int id = presetBox.getSelectedId();
        if (id <= 0)
            return;

        if (id < 1000)
            proc.presets.loadFactory (id - 1);
        else
            proc.presets.loadUser (presetBox.getText());

        shownPreset = proc.getPresetName();
    };
    prevButton.onClick = [this] { stepPreset (-1); };
    nextButton.onClick = [this] { stepPreset (+1); };
    saveButton.onClick = [this] { promptSavePreset(); };
    rebuildPresetMenu();

    setResizable (true, true);
    setResizeLimits (1260, 630, 2700, 1350);
    getConstrainer()->setFixedAspectRatio (1800.0 / 900.0);
    setSize (1800, 900);

    applyLane ((int) (proc.apvts.getRawParameterValue ("seq_dest")->load() + 0.5f));
    skinAttach.sendInitialUpdate();

    lastTick = juce::Time::getMillisecondCounterHiRes();
    startTimerHz (60);
}

PolyEvolverAudioProcessorEditor::~PolyEvolverAudioProcessorEditor()
{
    stopTimer();
    setLookAndFeel (nullptr);
}

ui::Section& PolyEvolverAudioProcessorEditor::addSection (int row, const juce::String& title)
{
    auto* sec = rows[row].add (new ui::Section (proc.apvts, title));
    addAndMakeVisible (sec);
    return *sec;
}

void PolyEvolverAudioProcessorEditor::applySkin (int index)
{
    ui::setSkin (index);
    skinSwitch.setCurrent (index);
    laf.applyTheme();
    sendLookAndFeelChange();
    repaint();
}

void PolyEvolverAudioProcessorEditor::applyLane (int lane)
{
    static const char* ids[3] = { "seq_step_", "seq_cut_", "seq_pan_" };
    lane = juce::jlimit (0, 2, lane);

    for (int i = 0; i < 16; ++i)
        stepCells[i]->getKnob().rebind (ids[lane] + juce::String (i + 1));

    shownLane = lane;
}

// ---------------------------------------------------------------- presets
void PolyEvolverAudioProcessorEditor::rebuildPresetMenu()
{
    presetBox.clear (juce::dontSendNotification);

    const auto& list = evo::factoryPresets();
    for (size_t i = 0; i < list.size(); ++i)
        presetBox.addItem (list[i].name, (int) i + 1);

    const auto user = evo::PresetManager::userNames();
    if (user.size() > 0)
    {
        presetBox.addSeparator();
        presetBox.addSectionHeading ("User presets");
        for (int i = 0; i < user.size(); ++i)
            presetBox.addItem (user[i], 1000 + i);
    }

    showCurrentPreset();
}

void PolyEvolverAudioProcessorEditor::showCurrentPreset()
{
    shownPreset = proc.getPresetName();

    for (int i = 0; i < presetBox.getNumItems(); ++i)
        if (presetBox.getItemText (i) == shownPreset)
        {
            presetBox.setSelectedItemIndex (i, juce::dontSendNotification);
            return;
        }

    presetBox.setSelectedId (0, juce::dontSendNotification);
    presetBox.setTextWhenNothingSelected (shownPreset);
}

void PolyEvolverAudioProcessorEditor::stepPreset (int delta)
{
    juce::StringArray names;
    for (const auto& f : evo::factoryPresets())
        names.add (f.name);

    const int numFactory = names.size();
    names.addArray (evo::PresetManager::userNames());

    int idx = names.indexOf (proc.getPresetName());
    idx = idx < 0 ? 0 : (idx + delta + names.size()) % names.size();

    if (idx < numFactory)
        proc.presets.loadFactory (idx);
    else
        proc.presets.loadUser (names[idx]);

    showCurrentPreset();
}

void PolyEvolverAudioProcessorEditor::promptSavePreset()
{
    auto* aw = new juce::AlertWindow ("Save preset", "Name for this sound:", juce::MessageBoxIconType::NoIcon, this);
    aw->addTextEditor ("name", proc.getPresetName() == "Init" ? juce::String() : proc.getPresetName());
    aw->addButton ("Save", 1, juce::KeyPress (juce::KeyPress::returnKey));
    aw->addButton ("Cancel", 0, juce::KeyPress (juce::KeyPress::escapeKey));

    juce::Component::SafePointer<PolyEvolverAudioProcessorEditor> safe (this);

    aw->enterModalState (true,
                         juce::ModalCallbackFunction::create ([safe, aw] (int result)
                         {
                             if (result == 1 && safe != nullptr)
                             {
                                 safe->proc.presets.saveUser (aw->getTextEditorContents ("name"));
                                 safe->rebuildPresetMenu();
                             }
                         }),
                         true);
}

void PolyEvolverAudioProcessorEditor::timerCallback()
{
    const double now = juce::Time::getMillisecondCounterHiRes();
    const float dt = juce::jlimit (0.001f, 0.1f, (float) ((now - lastTick) * 0.001));
    lastTick = now;

    for (auto* led : leds)
        led->tick (dt);

    const int step = proc.currentStep.load();
    if (step != shownStep)
    {
        shownStep = step;
        for (int i = 0; i < 16; ++i)
        {
            stepCells[i]->getKnob().setActive (i == step);
            stepCells[i]->setPlaying (i == step);
        }
    }

    const int lane = (int) (proc.apvts.getRawParameterValue ("seq_dest")->load() + 0.5f);
    if (lane != shownLane)
        applyLane (lane);

    if (++presetPoll >= 10)   // a few times a second: follow preset changes made by the host / program changes
    {
        presetPoll = 0;
        if (proc.getPresetName() != shownPreset)
            showCurrentPreset();
    }
}

void PolyEvolverAudioProcessorEditor::paint (juce::Graphics& g)
{
    using juce::Colour;
    using juce::ColourGradient;
    namespace Colours = juce::Colours;

    const auto& t = ui::theme();
    const auto b = getLocalBounds().toFloat();
    const int W = getWidth(), H = getHeight();

    // --- faceplate
    g.setGradientFill (ColourGradient (t.plateTop, 0, 0, t.plateBottom, 0, b.getHeight(), false));
    g.fillAll();

    g.setGradientFill (ColourGradient (t.plateGlow, b.getCentreX(), b.getHeight() * 0.30f,
                                       Colours::transparentBlack, 0, 0, true));
    g.fillAll();

    // fine horizontal brushing
    for (int y = 0; y < H; ++y)
    {
        const float a = (float) (((juce::uint32) y * 2654435761u >> 8) & 255u) / 255.0f;
        g.setColour (((y & 1) ? Colours::black : Colours::white).withAlpha (0.010f + 0.028f * a));
        g.fillRect (0, y, W, 1);
    }

    // vignette
    g.setGradientFill (ColourGradient (Colours::transparentBlack, b.getCentreX(), b.getCentreY(),
                                       Colours::black.withAlpha (t.vignette), 0, 0, true));
    g.fillAll();

    // --- black end cheeks
    for (int side = 0; side < 2; ++side)
    {
        const float x = side == 0 ? 0.0f : (float) W - 16.0f;
        g.setGradientFill (ColourGradient (Colour (0xff2b2f37), x, 0, Colour (0xff050608), x + 16.0f, 0, false));
        g.fillRect (x, 0.0f, 16.0f, (float) H);
        g.setColour (Colours::white.withAlpha (0.18f));
        g.fillRect (side == 0 ? 15.0f : (float) W - 16.0f, 0.0f, 1.0f, (float) H);
    }

    // --- header: logo and rule
    {
        g.setGradientFill (ColourGradient (t.logoTop, 0, 12.0f, t.logoBottom, 0, 46.0f, false));
        ui::drawLogo (g, 62.0f, 8.0f, 32.0f);

        juce::Font sub = ui::font (ui::Face::semiBold, 10.5f, 2.1f);
        g.setFont (sub);
        g.setColour (t.subtitle);
        g.drawText ("ANALOG / DIGITAL HYBRID  -  8 VOICE POLYPHONIC SYNTHESIZER", 64, 44, 640, 14,
                    juce::Justification::centredLeft, false);

        juce::ColourGradient rule (Colours::transparentBlack, 30.0f, 0, Colours::transparentBlack, (float) W - 30.0f, 0, false);
        rule.addColour (0.15, ui::accent.withAlpha (0.8f));
        rule.addColour (0.85, ui::accent.withAlpha (0.8f));
        g.setGradientFill (rule);
        g.fillRect (30.0f, 64.0f, (float) W - 60.0f, 1.5f);
    }

    // --- corner screws
    auto screw = [&g] (float cx, float cy, float rot)
    {
        g.setGradientFill (ColourGradient (Colour (0xffc7d0dc), cx - 3.0f, cy - 4.0f, Colour (0xff3a4250), cx + 5.0f, cy + 6.0f, true));
        g.fillEllipse (cx - 6.5f, cy - 6.5f, 13.0f, 13.0f);
        g.setColour (Colours::black.withAlpha (0.55f));
        g.drawEllipse (cx - 6.5f, cy - 6.5f, 13.0f, 13.0f, 1.0f);
        juce::Path slot;
        slot.addRectangle (-4.6f, -0.9f, 9.2f, 1.8f);
        g.setColour (Colours::black.withAlpha (0.8f));
        g.fillPath (slot, juce::AffineTransform::rotation (rot).translated (cx, cy));
    };
    screw (32.0f, 22.0f, 0.5f);                      screw ((float) W - 32.0f, 22.0f, 1.9f);
    screw (32.0f, (float) H - 20.0f, 1.1f);          screw ((float) W - 32.0f, (float) H - 20.0f, 2.4f);
}

void PolyEvolverAudioProcessorEditor::layoutRow (juce::Rectangle<int> area, const juce::OwnedArray<ui::Section>& row, int gap)
{
    // Single-knob sections (Noise, Master) get a little extra width so their titles fit.
    auto weight = [] (int items) { return juce::jmax ((float) items, 1.6f); };

    float totalItems = 0.0f;
    for (auto* s : row)
        totalItems += weight (s->getNumItems());

    if (totalItems <= 0.0f)
        return;

    const int usable = area.getWidth() - gap * (row.size() - 1);
    const float cell = (float) usable / totalItems;

    for (int i = 0; i < row.size(); ++i)
    {
        auto* s = row[i];
        const int w = (i == row.size() - 1) ? area.getWidth()
                                            : juce::roundToInt (cell * weight (s->getNumItems()));
        s->setBounds (area.removeFromLeft (w));
        area.removeFromLeft (gap);
    }
}

void PolyEvolverAudioProcessorEditor::resized()
{
    // Everything is laid out proportionally, so the plug-in can be resized freely.
    static const float rowWeight[numRows] = { 1.0f, 1.0f, 1.0f, 0.88f, 1.0f, 1.28f };

    auto area = getLocalBounds().reduced (30, 0);
    area.removeFromTop (74);
    area.removeFromBottom (34);

    const int gap = 8;
    float totalWeight = 0.0f;
    for (float w : rowWeight)
        totalWeight += w;

    const float unit = (float) (area.getHeight() - (numRows - 1) * gap) / totalWeight;

    for (int r = 0; r < numRows; ++r)
    {
        const int h = r == numRows - 1 ? area.getHeight() : juce::roundToInt (unit * rowWeight[r]);
        layoutRow (area.removeFromTop (h), rows[r], gap);
        area.removeFromTop (gap);
    }

    for (int i = 0; i < evo::numLfos; ++i)
        if (lfoSections[i] != nullptr)
        {
            const auto sb = lfoSections[i]->getBounds();
            leds[i]->setBounds (juce::Rectangle<int> (60, 60).withCentre ({ sb.getRight() - 26, sb.getY() + 15 }));
        }

    skinSwitch.setBounds (getWidth() - 30 - 130, 18, 130, 30);

    // preset bar: [<] [ name ] [>] [SAVE]
    auto bar = juce::Rectangle<int> (juce::jmax (520, getWidth() / 2 - 60), 20, 380, 26);
    prevButton.setBounds (bar.removeFromLeft (28));
    bar.removeFromLeft (4);
    saveButton.setBounds (bar.removeFromRight (56));
    bar.removeFromRight (4);
    nextButton.setBounds (bar.removeFromRight (28));
    bar.removeFromRight (4);
    presetBox.setBounds (bar);
}
