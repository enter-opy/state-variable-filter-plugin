/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/

class SliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    // we are creating a customLookAndFeel class inherited from lookAndFeel class
    // and overriding the function drawRotarySlider
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotatoryStartAngle, float rotatoryEndAngle, juce::Slider& slider) override
    {
        float diameter = jmin(width, height);
        float radius = diameter / 2;
        float centerX = x + width / 2;
        float centerY = y + height / 2;
        float rx = centerX - radius;
        float ry = centerY - radius;
        float angle = rotatoryStartAngle + sliderPos * (rotatoryEndAngle - rotatoryStartAngle);

        Rectangle<float> dialArea(rx, ry, diameter, diameter);

        g.setColour(Colours::crimson);
        g.fillEllipse(dialArea);

        Path dialTick;
        dialTick.addRectangle(0, -radius + 2.0, 2.0f, radius * 0.5);
        g.setColour(Colours::aliceblue);
        g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));
    }
};

class FilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FilterAudioProcessorEditor (FilterAudioProcessor&);
    ~FilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterAudioProcessor& audioProcessor;

    Slider cutoffSlider;
    Slider resonanceSlider;
    ComboBox filterTypeMenu;

    SliderLookAndFeel sliderLookAndFeel;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> cutoffValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> resonanceValue;
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterAudioProcessorEditor)
};
