/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const int ENTERBTN = 1;
const int PLAYBTN = 2;
const int CONFIRMBTN = 11;
const int RECORDBTN = 21;
const int STOPBTN = 22;
const int UNDOBTN = 23;
const int SAVEBTN = 24;

//==============================================================================
OSCrecieverAudioProcessorEditor::OSCrecieverAudioProcessorEditor (OSCrecieverAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    audioProcessor.recThread.nPattern = &(inputNum);

    if(connect(8000)){
        std::cout << "Connected reciever (PLUGIN)" << std::endl;
    }

    if(sender.connect("127.0.0.1", 9000)){
        std::cout << "Connected sender (PLUGIN)" << std::endl;
    }

    addListener(this, "/juce");

    setSize (400, 300);
}

OSCrecieverAudioProcessorEditor::~OSCrecieverAudioProcessorEditor()
{
}

//==============================================================================
void OSCrecieverAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void OSCrecieverAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void OSCrecieverAudioProcessorEditor::oscMessageReceived(const juce::OSCMessage &message){
    if(message.size() == 3 && message[1].isInt32()){
        switch(message[1].getInt32()){
            case ENTERBTN:
            {
                break;
            }
            case PLAYBTN:
            {
                break;
            }
            case CONFIRMBTN:
            {
                inputNum=message[2].getInt32();
                break;
            }
            case RECORDBTN:
            {   
                audioProcessor.sequencePositionCounter = 0;
                audioProcessor.startRec=true;
                break;
            }
            case STOPBTN:
            {
                audioProcessor.startRec=false;
                audioProcessor.recThread.addMMS(audioProcessor.mms);
                if(audioProcessor.recThread.isThreadRunning()){
                    audioProcessor.recThread.run();
                }else{
                    audioProcessor.recThread.startThread();
                }
                if(audioProcessor.recThread.seq->getNumEvents()==0){
                    juce::OSCMessage mex("/warning");
                    mex.addInt32(0);
                    if(!sender.send(mex)){
                        std::cout << "Cannot send the message" << std::endl;
                    }
                    std::cerr << "Empty track recorded!" << std::endl;
                }
                break;
            }
            case UNDOBTN:
            {
                if(audioProcessor.recThread.index>0){
                    audioProcessor.recThread.index--;
                }
                juce::String fileName = "track";
                fileName+=audioProcessor.recThread.index;
                fileName+=".mid";
                auto midiFile = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile(fileName);
                if(midiFile.deleteFile()){
                    std::cout << fileName << " deleted correctly" << std::endl;
                }
                break;
            }
            case SAVEBTN:
            {
                inputCommand = message[4].getString();    
                std::cout << "OSC command " << inputCommand << " saved correctly in OSC.txt" << std::endl;
                auto OSCfile = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("OSC.txt");
                if(audioProcessor.recThread.index==1){
                    OSCfile.replaceWithText(inputCommand+'\n');
                }else{
                    OSCfile.appendText(inputCommand+'\n');
                }
                std::cout << "OSC command " << inputCommand << " saved correctly in OSC.txt" << std::endl;
                break;
            }
        }
    }
}