/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <string.h>
#include <vector>

const int CREATEBTN = 1;
const int ENTERBTN = 2;
const int CONFIRMBTN = 11;
const int RECORDBTN = 21;
const int STOPBTN = 22;
const int UNDOBTN = 23;
const int SAVEBTN = 24;
const int TRAINBTN = 31;
const int STARTBTN = 41;
const int DELETEBTN = 42;

using namespace juce;

//==============================================================================
OSCrecieverAudioProcessorEditor::OSCrecieverAudioProcessorEditor (OSCrecieverAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    audioProcessor.recThread.nPattern = &(inputNum);
    audioProcessor.recThread.sessionName = &(sessionName);

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
    if(message.size() == 3 && message[0].isInt32()){
        switch(message[0].getInt32()){
            case CREATEBTN:
            {
                break;
            }
            case ENTERBTN:
            {
                juce::OSCMessage mex("/data");
                //juce::String fileName = "/home/mind/myPlugin/metadata.txt";
                juce::String fileName = "~/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/metadata.txt";
                juce::File sessionFile(fileName);
                if(sessionFile.existsAsFile()){
                    juce::FileInputStream inputStream(sessionFile);
                    inputStream.setPosition(0);
                    int i = 0;
                    while(!inputStream.isExhausted()){
                        mex.addString(inputStream.readNextLine());
                        i++;
                    }
                    if(i==0){
                        std::cerr << "You have 0 session recorded!" << std::endl;
                    }
                    mex.addInt32(1);
                    if(!sender.send(mex)){
                        std::cout << "Cannot send the message" << std::endl;
                    }
                }else{
                    std::cout << "non esiste" << std::endl;
                }
                break;
            }
            case CONFIRMBTN:
            {
                sessionName=message[2].getString();
                inputNum=message[1].getInt32();

                //juce::String dirName = "/home/mind/myPlugin/" + sessionName;
                juce::String dirName = "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/" + sessionName;
                juce::File sessionDir(dirName);
                sessionDir.createDirectory();

                //juce::String fileName = "/home/mind/myPlugin/metadata.txt";
                juce::String fileName = "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/metadata.txt";
                juce::File sessionFile(fileName);
                sessionFile.appendText(sessionName + '\n');

                trainCommand = "curl -g -o  /home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/" + sessionName+ "/" + sessionName + ".onnx" + " https://a895307b697c-9003014567992963579.ngrok-free.app/files/" + sessionName + ".onnx/?data=[[";
                //trainCommand = "curl -g -o  /home/mind/myPlugin/" + sessionName+ "/" + sessionName + ".onnx" + " https://a895307b697c-9003014567992963579.ngrok-free.app/files/" + sessionName + ".onnx/?data=[[";
                break;
            }
            case RECORDBTN:
            {   
                if(audioProcessor.bcgThread.isThreadRunning()){
                    audioProcessor.bcgThread.run();
                }else{
                    audioProcessor.bcgThread.startThread();
                }audioProcessor.startRec=true;
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
                    juce::OSCMessage mex("/data");
                    mex.addInt32(0);
                    if(!sender.send(mex)){
                        std::cout << "Cannot send the message" << std::endl;
                    }
                    std::cerr << "Empty track recorded!" << std::endl;
                }

                for(auto item : audioProcessor.bcgThread.noteBuffer){
                    trainCommand += juce::String(item);
                    //std::cout << item << "--";
                    trainCommand += ",";
                }
                trainCommand = trainCommand.upToLastOccurrenceOf(",",false,true);
                trainCommand += "]";
                //std::cout << std::endl;
                if(audioProcessor.recThread.index<inputNum){
                    trainCommand += ",";
                }

                break;
            }
            case UNDOBTN:
            {
                if(audioProcessor.recThread.index>0){
                    audioProcessor.recThread.index--;
                }
                //juce::String fileName = "/home/mind/myPlugin/"+sessionName+"/track";
                juce::String fileName = "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+sessionName+"/track";
                fileName+=audioProcessor.recThread.index;
                fileName+=".mid";
                juce::File midiFile(fileName);
                if(midiFile.deleteFile()){
                    std::cout << fileName << " deleted correctly" << std::endl;
                }
                trainCommand = trainCommand.upToLastOccurrenceOf("[",false,true);
                break;
            }
            case SAVEBTN:
            {
                inputCommand = message[2].getString();    
                //juce::String fileName = "/home/mind/myPlugin/"+sessionName+"/"+sessionName+".txt";
                juce::String fileName = "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+sessionName+"/"+sessionName+".txt";
                juce::File OSCfile(fileName);
                OSCfile.appendText(inputCommand+'\n');
                std::cout << "OSC command " << inputCommand << " saved correctly in " << sessionName << ".txt" << std::endl;
                break;
            }
            case TRAINBTN:
            {
                trainCommand+="]";
                std::cout << trainCommand << std::endl;
                const char* com = static_cast<const char*>(trainCommand.toUTF8());
                system(com);
                trainCommand.clear();
                
                break;
            }
            case STARTBTN:
            {
                //INFERENCE CODE
                break;
            }
            case DELETEBTN:
            {
                juce::String sessionToDelete = message[2].getString();
                juce::StringArray text;
                juce::String fileName = "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/metadata.txt";
                juce::File sessionFile(fileName);
                if(sessionFile.existsAsFile()){
                    juce::FileInputStream inputStream(sessionFile);
                    inputStream.setPosition(0);
                    while(!inputStream.isExhausted()){
                        juce::String str = inputStream.readNextLine();
                        if(str!=sessionToDelete){
                            text.add(str);
                        }
                    }
                    sessionFile.replaceWithText("");
                    for(auto sesh : text){
                        sessionFile.appendText(sesh+'\n');
                    }
                }
                //juce::String dirName = "/home/mind/myPlugin/" + sessionName;
                juce::String dirName = "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/" + sessionName;
                juce::File sessionDir(dirName);
                sessionDir.deleteRecursively();
                std::cout << sessionToDelete << " deleted" << std::endl;
                break;
            }
        }
    }
}