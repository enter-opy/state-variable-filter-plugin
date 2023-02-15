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

    cutoffValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, CUTOFF_ID, cutoffSlider);
    resonanceValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, RESONANCE_ID, resonanceSlider);
    filterTypeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, FILTERTYPE_ID, filterTypeMenu);

    filterTypeMenu.setJustificationType(Justification::centred);
    filterTypeMenu.addItem("Low Pass", 1);
    filterTypeMenu.addItem("Band Pass", 2);
    filterTypeMenu.addItem("High Pass", 3);
    addAndMakeVisible(&filterTypeMenu);

    cutoffSlider.setSliderStyle(Slider::Rotary);
    cutoffSlider.setRange(20.0f, 20000.0f);
    cutoffSlider.setValue(600.0f);
    cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    cutoffSlider.setPopupDisplayEnabled(true, true, this);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0f);
    addAndMakeVisible(&cutoffSlider);

    resonanceSlider.setSliderStyle(Slider::Rotary);
    resonanceSlider.setRange(1.0f, 5.0f);
    resonanceSlider.setValue(2.0f);
    resonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    resonanceSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&resonanceSlider);
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
}

void FilterAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);

    filterTypeMenu.setBounds(area.removeFromTop(20));
    cutoffSlider.setBounds(30, 90, 70, 70);
    resonanceSlider.setBounds(100, 90, 70, 70);
}
