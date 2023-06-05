/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Page1.h"
#include "Page4.h"

using namespace juce;

//==============================================================================
/**
*/
class TestAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Label::Listener, public juce::Button::Listener
{
public:
    TestAudioProcessorEditor (TestAudioProcessor&);
    ~TestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestAudioProcessor& audioProcessor;

    juce::TextButton enterBtn;
    juce::TextButton playBtn;

    //Page 1
    Page1 p1;
    juce::Label* patternLabel;
    juce::TextButton* confButton;
    int inputNum;

    //Page 2
    juce::ShapeButton* recButton;
    juce::ShapeButton* stopButton;
    juce::TextButton* undoButton;
    juce::Label* OSClabel;
    juce::TextButton* saveButton;
    juce::String inputCommand;

    //Page 3
    juce::Label* modelNameLabel;
    juce::TextButton* trainButton;

    //Page 4
    Page4 p4;
    juce::Label* modelName;
    juce::TextButton* goButton;


    void labelTextChanged(juce::Label* labelThatHasChanged) override;
    void buttonClicked(Button * button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessorEditor)
};