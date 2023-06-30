/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <string.h>

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
                auto sessionFile = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("metadata.txt");
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
                }
                break;
            }
            case CONFIRMBTN:
            {
                sessionName=message[2].getString();
                inputNum=message[1].getInt32();
                juce::String dirName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/" + sessionName;
                juce::File sessionDir(dirName);
                sessionDir.createDirectory();
                auto sessionFile = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("metadata.txt");
                sessionFile.appendText(sessionName + '\n');
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
                    juce::OSCMessage mex("/data");
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
                juce::String fileName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+sessionName+"/track";
                fileName+=audioProcessor.recThread.index;
                fileName+=".mid";
                juce::File midiFile(fileName);
                if(midiFile.deleteFile()){
                    std::cout << fileName << " deleted correctly" << std::endl;
                }
                break;
            }
            case SAVEBTN:
            {
                inputCommand = message[2].getString();    
                juce::String fileName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+sessionName+"/"+sessionName+".txt";
                juce::File OSCfile(fileName);
                OSCfile.appendText(inputCommand+'\n');
                std::cout << "OSC command " << inputCommand << " saved correctly in " << sessionName << ".txt" << std::endl;
                break;
            }
            case TRAINBTN:
            {
                /*juce::URL url("https://ae4f-193-205-210-74.ngrok-free.app/files/test.onnx/?data=[[1,2,3,4,5],[2,3,4,5,6],[1,2,3,4,5]]");
                juce::String fileName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+sessionName+"/test.onnx";
                //juce::String fileName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/test.onnx";
                juce::File destFile(fileName);
                destFile.deleteFile();
                URL::DownloadTaskOptions opt;
                url.downloadToFile(destFile, opt.withListener(this));
                //url.launchInDefaultBrowser();*/
                
                juce::String fileName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/"+sessionName+"/" + sessionName + ".onnx";
                juce::String command = "curl -g -o " + fileName + " https://a895307b697c-9003014567992963579.ngrok-free.app/files/" + sessionName + ".onnx/?data=[[1,2,3,4,5],[2,3,4,5,6],[1,2,3,4,5]]";
                const char* com = static_cast<const char*>(command.toUTF8());
                system(com);
                
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
                auto sessionFile = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("metedata.txt");
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
                juce::String dirName = "~/UNI/tirocinio/Audio-pattern-detection-juce-plugin/OSCreciever/" + sessionName;
                juce::File sessionDir(dirName);
                sessionDir.deleteRecursively();
                std::cout << sessionToDelete << " deleted" << std::endl;
                break;
            }
        }
    }
}

/*void OSCrecieverAudioProcessorEditor::finished(juce::URL::DownloadTask* task, bool success){
    juce::OSCMessage mex("/data");
    if(success){
        std::cout << "The model has been trained" << std::endl;
        mex.addInt32(200);
    }else{
        std::cerr << "Model training failed" << std::endl;
        mex.addInt32(404);
    }
    if(!sender.send(mex)){
        std::cout << "Cannot send the message" << std::endl;
    }
}*/