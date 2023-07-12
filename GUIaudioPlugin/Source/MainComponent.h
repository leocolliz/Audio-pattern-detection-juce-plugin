#pragma once

#include <JuceHeader.h>
#include "Page0.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::Label::Listener, public juce::Button::Listener, public juce::ComboBox::Listener, public juce::OSCReceiver, public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::RealtimeCallback>
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //Page 0 
    Page0 p0;
    juce::TextButton* createButton;
    juce::TextButton* openButton;

    //Page 1
    juce::Label* sessionLabel;
    juce::Label* patternLabel;
    juce::TextButton* confButton;
    juce::String sessionName;
    int inputNum;

    //Page 2
    juce::ShapeButton* recButton;
    juce::ShapeButton* stopButton;
    juce::TextButton* undoButton;
    juce::Label* OSClabel;
    juce::TextButton* saveButton;
    juce::String inputCommand;
    bool startRec = false;
    bool emptyTrack = false;

    //Page 3
    juce::TextButton* trainButton;

    //Page 4
    juce::ComboBox* sessionBox;
    juce::TextButton* startButton;
    juce::TextButton* deleteButton;

    void labelTextChanged(juce::Label* labelThatHasChanged) override;
    void buttonClicked(juce::Button * button) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    juce::OSCSender sender;

    void oscMessageReceived (const juce::OSCMessage &message) override;
private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
