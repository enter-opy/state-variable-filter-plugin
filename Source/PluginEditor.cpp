/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterAudioProcessorEditor::FilterAudioProcessorEditor (FilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);

    filterTypeMenu.setJustificationType(Justification::centred);
    filterTypeMenu.addItem("Low Pass", 1);
    filterTypeMenu.addItem("Band Pass", 2);
    filterTypeMenu.addItem("High Pass", 3);
    addAndMakeVisible(&filterTypeMenu);

    filterCutoffDial.setSliderStyle(Slider::Rotary);
    filterCutoffDial.setRange(20.0f, 20000.0f);
    filterCutoffDial.setValue(600.0f);
    filterCutoffDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffDial.setPopupDisplayEnabled(true, true, this);
    filterCutoffDial.setSkewFactorFromMidPoint(1000.0f);
    addAndMakeVisible(&filterCutoffDial);

    filterResonanceDial.setSliderStyle(Slider::Rotary);
    filterResonanceDial.setRange(1.0f, 5.0f);
    filterResonanceDial.setValue(2.0f);
    filterResonanceDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterResonanceDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterResonanceDial);

    filterCutoffValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTree, "cutoff", filterCutoffDial);
    filterResonanceValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.valueTree, "resonance", filterResonanceDial);
    filterTypeChoice = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.valueTree, "filtertype", filterTypeMenu);
}

FilterAudioProcessorEditor::~FilterAudioProcessorEditor()
{
}

//==============================================================================
void FilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Filter", titleArea, Justification::centredTop);
    g.drawText("Cutoff", 46, 70, 50, 25, Justification::centredLeft);
    g.drawText("Resonance", 107, 70, 70, 25, Justification::centredLeft);

    Rectangle <float> area(25, 25, 150, 150);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void FilterAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);

    filterTypeMenu.setBounds(area.removeFromTop(20));
    filterCutoffDial.setBounds(30, 90, 70, 70);
    filterResonanceDial.setBounds(100, 90, 70, 70);
}
