#pragma once

#include <JuceHeader.h>
#include "Page1.h"
#include "Page4.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::Label::Listener, public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

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
    bool startRec;

    //Page 3
    juce::Label* modelNameLabel;
    juce::TextButton* trainButton;

    //Page 4
    Page4 p4;
    juce::Label* modelName;
    juce::TextButton* goButton;

    void labelTextChanged(juce::Label* labelThatHasChanged) override;
    void buttonClicked(juce::Button * button) override;

    juce::OSCSender sender;

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
