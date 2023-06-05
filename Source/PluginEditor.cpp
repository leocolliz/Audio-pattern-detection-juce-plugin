/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <unistd.h>
#include <string.h>

using namespace juce;

//==============================================================================
TestAudioProcessorEditor::TestAudioProcessorEditor (TestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    //Initial page buttons

    enterBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    enterBtn.setButtonText("Enter patterns");
    addAndMakeVisible(enterBtn);

    playBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    playBtn.setButtonText("Play");
    addAndMakeVisible(playBtn);
    
    enterBtn.addListener(this);
    playBtn.addListener(this);

    //Page 1 buttons

    patternLabel=   &(p1.patLabel);
    confButton  =   &(p1.confBtn);

    patternLabel->addListener(this);
    confButton->addListener(this);

    audioProcessor.recThread.nPattern = &(inputNum);

    //Page 2 buttons

    recButton   =   &(p1.p2.recBtn);
    stopButton  =   &(p1.p2.stopBtn);
    undoButton  =   &(p1.p2.undoBtn);
    OSClabel    =   &(p1.p2.OSCcommandLabel);
    saveButton  =   &(p1.p2.saveBtn);
    
    recButton->addListener(this);
    stopButton->addListener(this);
    undoButton->addListener(this);
    OSClabel->addListener(this);
    saveButton->addListener(this);

    //Page 3 buttons

    modelNameLabel =&(p1.p2.p3.modelLabel);
    trainButton =   &(p1.p2.p3.trainBtn);

    modelNameLabel->addListener(this);
    trainButton->addListener(this);

    //Page 4 buttons

    modelName   =   &(p4.modelLabel);
    goButton    =   &(p4.goBtn);

    setSize (400, 300);
}

TestAudioProcessorEditor::~TestAudioProcessorEditor()
{
}

//==============================================================================
void TestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void TestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto area = getLocalBounds();
    enterBtn.setBounds(area.getCentreX()-80,area.getCentreY()-100,160,60);
    playBtn.setBounds(area.getCentreX()-80,area.getCentreY()-30,160,60);

    p1.setBounds(area);
    p4.setBounds(area);
}

void TestAudioProcessorEditor::labelTextChanged(juce::Label* labelThatHasChanged)
{
    //PAGE 1 LABEL
    if(labelThatHasChanged==patternLabel){
        addAndMakeVisible(confButton);
    }
    //PAGE 2 LABEL
    if(labelThatHasChanged==OSClabel){
        
    }
}

void TestAudioProcessorEditor::buttonClicked (Button * button)
{
    //INITIAL PAGE BUTTONS
    if(button==&enterBtn){
        addAndMakeVisible(p1);
    }if(button==&playBtn){
        addAndMakeVisible(p4);
    }
    //PAGE 1 BUTTONS
    if(button==confButton){
        inputNum = patternLabel->getText().getIntValue();
        std::cout << "You can now record your " << inputNum << " patterns" << std::endl;
        addAndMakeVisible(p1.p2);

        stopButton->setEnabled(false);
        undoButton->setEnabled(false);
        saveButton->setEnabled(false);
    }
    //PAGE 2 BUTTONS
    if(button==recButton){
        std::cout << "Recording..." << std::endl;
        recButton->setOutline(juce::Colours::darkred, 10);
        audioProcessor.sequencePositionCounter = 0;
        audioProcessor.startRec=true;

        stopButton->setEnabled(true);
        undoButton->setEnabled(false);
        saveButton->setEnabled(false);

    }if(button==stopButton&&audioProcessor.startRec){
        std::cout << "Stopped recording!" << std::endl;
        recButton->setVisible(false);
        recButton->setOutline(juce::Colours::red, 10);
        addAndMakeVisible(recButton);
        audioProcessor.startRec=false;
        audioProcessor.recThread.addMMS(audioProcessor.mms);
        if(audioProcessor.recThread.isThreadRunning()){
            audioProcessor.recThread.run();
        }else{
            audioProcessor.recThread.startThread();
        }
        if(audioProcessor.recThread.seq->getNumEvents()!=0){
            addAndMakeVisible(OSClabel);
            addAndMakeVisible(saveButton);
            undoButton->setEnabled(true);
            saveButton->setEnabled(true);
            recButton->setEnabled(false);
            stopButton->setEnabled(false);   
        }else{
            std::cerr << "Empty track recorded!" << std::endl;
        }
    }if(button==undoButton){
        if(audioProcessor.recThread.index>0){
            audioProcessor.recThread.index--;
        }
        juce::String fileName = "track";
        fileName+=audioProcessor.recThread.index;
        fileName+=".mid";
        auto midiFile = File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile(fileName);
        if(midiFile.deleteFile()){
            std::cout << fileName << " deleted correctly" << std::endl;
        }
        OSClabel->setVisible(false);
        saveButton->setVisible(false);

        recButton->setEnabled(true);

    }if(button==saveButton){
        inputCommand = OSClabel->getText();
        if(!inputCommand.isEmpty()){
            std::cout << "OSC command " << inputCommand << " saved correctly in OSC.txt" << std::endl;
            OSClabel->setText("", dontSendNotification);
            auto OSCfile = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getChildFile("OSC.txt");
            if(audioProcessor.recThread.index==1){
                OSCfile.replaceWithText(inputCommand+'\n');
            }else{
                OSCfile.appendText(inputCommand+'\n');
            }
            if(audioProcessor.recThread.index<=*(audioProcessor.recThread.nPattern)){
                OSClabel->setVisible(false);
                saveButton->setVisible(false);
            }else{
                addAndMakeVisible(p1.p2.p3);
            }
            undoButton->setEnabled(false);
            recButton->setEnabled(true);
        }else{
            std::cerr << "Empty OSC command" << std::endl;
        }
    }

    //PAGE 3 BUTTONS
    if(button==trainButton){

    }

    //PAGE 4 BUTTONS
    if(button==goButton){

    }
}