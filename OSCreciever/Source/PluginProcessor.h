/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class OSCrecieverAudioProcessor  : public juce::AudioProcessor, public juce::OSCReceiver, public juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::RealtimeCallback>
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    OSCrecieverAudioProcessor();
    ~OSCrecieverAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //------------------------------------------------------------------------------

    int midiTime = 0;
    juce::MidiMessageSequence mms;
    bool startRec = false;

    class recordingThread : public juce::Thread {
    public:
        recordingThread() : juce::Thread("Recording Thread"){
        }
        void run() override {
            record();
        }
        void record();
        void addMMS(juce::MidiMessageSequence &m){
          seq = &m;
        }
        std::vector <float> patternBuffer;
        juce::MidiMessageSequence* seq;
        int index = 1;
        int nPattern;
        juce::String sessionName;
    };
    recordingThread recThread;

    class backgroundThread : public juce::Thread {
    public:
        std::vector <float> noteBuffer; 
        backgroundThread() : juce::Thread("BCG thread"), noteBuffer(50){
        }
        void run() override {
            checkNotes();
        }
        void checkNotes();
    };
    backgroundThread bcgThread;

    juce::String inputCommand;
    juce::String trainCommand;

    void oscMessageReceived (const juce::OSCMessage &message) override; 	
    juce::OSCSender sender;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCrecieverAudioProcessor)
};
