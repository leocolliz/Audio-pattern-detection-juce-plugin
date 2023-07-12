/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//#include </usr/local/lib/onnxruntime-linux-x64-1.15.0/include/onnxruntime_cxx_api.h>

using namespace juce;

float currNote = 0;
float ptcBnd = 0;
float tmpNote = 0;
const int buffer_len = 50;

//==============================================================================
OSCrecieverAudioProcessor::OSCrecieverAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

OSCrecieverAudioProcessor::~OSCrecieverAudioProcessor()
{
    bcgThread.stopThread(10);
    recThread.stopThread(10);
}

//==============================================================================
const juce::String OSCrecieverAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OSCrecieverAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OSCrecieverAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OSCrecieverAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OSCrecieverAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OSCrecieverAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OSCrecieverAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OSCrecieverAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OSCrecieverAudioProcessor::getProgramName (int index)
{
    return {};
}

void OSCrecieverAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OSCrecieverAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mms.clear();
    bcgThread.noteBuffer.clear();
}

void OSCrecieverAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OSCrecieverAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void OSCrecieverAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (auto midiMessage : midiMessages) {
        auto midiEvent = midiMessage.getMessage();
        auto note = midiEvent.getNoteNumber();
        std::cout << midiEvent.getDescription() << " " << midiEvent.getTimeStamp() << std::endl;
        if(startRec){
            /*if (midiEvent.isNoteOn()) {
            tmpNote = midiEvent.getNoteNumber();
            currNote = tmpNote;
            }
            if (midiEvent.isPitchWheel()&&tmpNote!=0) {
                ptcBnd = midiEvent.getPitchWheelValue();
                currNote = tmpNote + (ptcBnd-8192)/(8192/2);
            }
            if (midiEvent.isNoteOff()) {
                tmpNote = 0;
                currNote = 1;
            }*/
            
            midiTime+=midiEvent.getTimeStamp();
            midiEvent.setTimeStamp(midiTime);
            std::cout << midiEvent.getDescription() << " " << midiEvent.getTimeStamp() << std::endl;
            mms.addEvent(midiEvent);
        }
    }
}

//==============================================================================
bool OSCrecieverAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OSCrecieverAudioProcessor::createEditor()
{
    return new OSCrecieverAudioProcessorEditor (*this);
}

//==============================================================================
void OSCrecieverAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OSCrecieverAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OSCrecieverAudioProcessor();
}

void OSCrecieverAudioProcessor::recordingThread::record(){
    if(index<=*nPattern && seq->getNumEvents()!=0){
        juce::MidiFile pattern;

        pattern.setTicksPerQuarterNote(96);
        //pattern.setSmpteTimeFormat(25,40);
        
        juce::String fileName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+*(sessionName)+"/track";
        fileName+=index;
        fileName+=".mid";

        juce::File midiFile(fileName);
        midiFile.create();
        FileOutputStream stream(midiFile);

        if(stream.openedOk()){
                std::cout << "Track" << index  << ".mid " << " opened correctly" << std::endl;
        }
        
        stream.setPosition(0);

        //correction of the MidiMessageSequence
        int i = 0;
        for(const auto midiMex : *seq){
            if(!(midiMex->message.isNoteOn())){
                seq->deleteEvent(i, false);
                i++;
            }else{
                double t = seq->getEventPointer(i)->message.getTimeStamp();
                for(const auto midiMex : *seq){
                    midiMex->message.setTimeStamp(midiMex->message.getTimeStamp()-t);
                    if (midiMex->message.isNoteOn()) {
                        tmpNote = midiMex->message.getNoteNumber();
                        currNote = tmpNote;
                    }
                    if (midiMex->message.isPitchWheel()&&tmpNote!=0) {
                        ptcBnd = midiMex->message.getPitchWheelValue();
                        currNote = tmpNote + (ptcBnd-8192)/(8192/2);
                    }
                    if (midiMex->message.isNoteOff()) {
                        tmpNote = 0;
                        currNote = 1;
                    }
                    patternBuffer.push_back(currNote);
                }
                break;
            }
        }
        
        seq->updateMatchedPairs();

        pattern.addTrack(*seq);
        pattern.writeTo(stream);

        if(stream.getStatus().failed()){
            DBG ("An error occurred in the FileOutputStream");
        }else{
            std::cout << "Track" << index  << ".mid " << " saved" << std::endl << "If you want to delete it press UNDO" << std::endl;
        }

        seq->clear();

        index++;
    }
}

void OSCrecieverAudioProcessor::backgroundThread::checkNotes() {
    while(34){
        sleep(30);
        if(noteBuffer.size() == buffer_len){
            noteBuffer.erase(noteBuffer.begin());
            //noteBuffer.assign(noteBuffer.begin() + 1, noteBuffer.end());
        }
        noteBuffer.push_back(currNote);
        if(noteBuffer.size() == buffer_len-1){
            DBG("READY SET GO!!!");
            //dummyClass::function(noteBuffer);
            //DBG(currNote);
        }   
    }
}