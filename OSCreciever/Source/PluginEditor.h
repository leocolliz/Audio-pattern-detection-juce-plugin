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
class OSCrecieverAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::OSCReceiver, public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::RealtimeCallback>//, public juce::URL::DownloadTaskListener
{
public:
    OSCrecieverAudioProcessorEditor (OSCrecieverAudioProcessor&);
    ~OSCrecieverAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    String getResultText (const URL& url);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OSCrecieverAudioProcessor& audioProcessor;

    juce::String sessionName;
    int inputNum;
    juce::String inputCommand;

    void oscMessageReceived (const juce::OSCMessage &message) override;
    //void finished (juce::URL::DownloadTask* task, bool success) override; 	
    juce::OSCSender sender;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCrecieverAudioProcessorEditor)
};
