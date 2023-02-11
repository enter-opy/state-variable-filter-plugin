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
class FilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FilterAudioProcessorEditor (FilterAudioProcessor&);
    ~FilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> filterResonanceValue;
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeChoice;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterAudioProcessor& audioProcessor;

    Slider filterCutoffDial;
    Slider filterResonanceDial;
    ComboBox filterTypeMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterAudioProcessorEditor)
};
