#pragma once

#include <JuceHeader.h>
#include "BinaryData.h"

// Inter (SIL Open Font License) is bundled into the plugin, so the look is identical on every Mac.
namespace ui
{
enum class Face { bold, semiBold, displayBlack, displayExtraLight };

inline juce::Typeface::Ptr typefaceFor (Face f)
{
    static juce::Typeface::Ptr bold  = juce::Typeface::createSystemTypefaceFor (BinaryData::InterBold_otf,           BinaryData::InterBold_otfSize);
    static juce::Typeface::Ptr semi  = juce::Typeface::createSystemTypefaceFor (BinaryData::InterSemiBold_otf,       BinaryData::InterSemiBold_otfSize);
    static juce::Typeface::Ptr black = juce::Typeface::createSystemTypefaceFor (BinaryData::InterDisplayBlack_otf,   BinaryData::InterDisplayBlack_otfSize);
    static juce::Typeface::Ptr light = juce::Typeface::createSystemTypefaceFor (BinaryData::InterDisplayExtraLight_otf, BinaryData::InterDisplayExtraLight_otfSize);

    switch (f)
    {
        case Face::bold:              return bold;
        case Face::semiBold:          return semi;
        case Face::displayBlack:      return black;
        case Face::displayExtraLight: return light;
    }
    return bold;
}

inline juce::Font font (Face f, float height, float trackingPx = 0.0f)
{
    juce::Font out (juce::FontOptions (typefaceFor (f)).withHeight (height));
    out.setExtraKerningFactor (trackingPx / height);
    return out;
}

// Logo 12: bold "Z-" followed by a light "SYNTH". Returns the width used.
inline float drawLogo (juce::Graphics& g, float x, float baselineTop, float height)
{
    const auto bold  = font (Face::displayBlack,      height, 4.0f * height / 32.0f);
    const auto light = font (Face::displayExtraLight, height, 8.0f * height / 32.0f);

    auto widthOf = [] (const juce::Font& f, const juce::String& s)
    {
        juce::GlyphArrangement ga;
        ga.addLineOfText (f, s, 0.0f, 0.0f);
        return ga.getBoundingBox (0, -1, true).getWidth();
    };

    const float w1 = widthOf (bold, "Z-") + 4.0f * height / 32.0f;
    g.setFont (bold);
    g.drawText ("Z-", juce::Rectangle<float> (x, baselineTop, w1 + 20.0f, height * 1.25f), juce::Justification::centredLeft, false);
    g.setFont (light);
    g.drawText ("SYNTH", juce::Rectangle<float> (x + w1, baselineTop, 400.0f, height * 1.25f), juce::Justification::centredLeft, false);
    return w1 + widthOf (light, "SYNTH");
}
} // namespace ui
