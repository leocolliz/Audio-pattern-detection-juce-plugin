#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    if( sender.connect("127.0.0.1", 8000)){
        std::cout << "Connected" << std::endl;
    }   
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

MainComponent::~MainComponent()
{
    sender.disconnect();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    auto area = getLocalBounds();
    enterBtn.setBounds(area.getCentreX()-80,area.getCentreY()-100,160,60);
    playBtn.setBounds(area.getCentreX()-80,area.getCentreY()-30,160,60);

    p1.setBounds(area);
    p4.setBounds(area);
}

void MainComponent::labelTextChanged(juce::Label* labelThatHasChanged)
{
    //PAGE 1 LABEL
    if(labelThatHasChanged==patternLabel){
        addAndMakeVisible(confButton);
    }
    //PAGE 2 LABEL
    if(labelThatHasChanged==OSClabel){
        
    }
}

void MainComponent::buttonClicked (juce::Button * button)
{
    //INITIAL PAGE BUTTONS
    if(button==&enterBtn){
        addAndMakeVisible(p1);

        if(!sender.send("/juce", 1, 0 , " ")){
            std::cout << "Cannot send the message" << std::endl;
        }
    }if(button==&playBtn){
        addAndMakeVisible(p4);

        if(!sender.send("/juce", 2, 0 , " ")){
            std::cout << "Cannot send the message" << std::endl;
        }
    }
    //PAGE 1 BUTTONS
    if(button==confButton){
        inputNum = patternLabel->getText().getIntValue();
        std::cout << "You can now record your " << inputNum << " patterns" << std::endl;
        addAndMakeVisible(p1.p2);

        if(!sender.send("/juce", 11, inputNum, " ")){
            std::cout << "Cannot send the message" << std::endl;
        }

        stopButton->setEnabled(false);
        undoButton->setEnabled(false);
        saveButton->setEnabled(false);
    }
    //PAGE 2 BUTTONS
    if(button==recButton){
        recButton->setOutline(juce::Colours::darkred, 10);
        std::cout << "Recording..." << std::endl;
        startRec=true;
        
        if(!sender.send("/juce", 21, 0 , " ")){
            std::cout << "Cannot send the message" << std::endl;
        }

        stopButton->setEnabled(true);
        undoButton->setEnabled(false);
        saveButton->setEnabled(false);

    }if(button==stopButton && startRec){
        std::cout << "Stopped recording!" << std::endl;
        recButton->setVisible(false);
        recButton->setOutline(juce::Colours::red, 10);
        addAndMakeVisible(recButton);
        startRec=false;

        if(!sender.send("/juce", 22, 0 , " ")){
            std::cout << "Cannot send the message" << std::endl;
        }

        /*if(audioProcessor.recThread.seq->getNumEvents()!=0){      //DA PENSARE
            addAndMakeVisible(OSClabel);
            addAndMakeVisible(saveButton);
            undoButton->setEnabled(true);
            saveButton->setEnabled(true);
            recButton->setEnabled(false);
            stopButton->setEnabled(false);   
        }else{
            std::cerr << "Empty track recorded!" << std::endl;
        }*/

    }if(button==undoButton){
        inputNum++;
        if(!sender.send("/juce", 23, 0 , " ")){
            std::cout << "Cannot send the message" << std::endl;
        }
        OSClabel->setVisible(false);
        saveButton->setVisible(false);

        recButton->setEnabled(true);

    }if(button==saveButton){
        inputCommand = OSClabel->getText();
        if(!inputCommand.isEmpty()){
            OSClabel->setText("", juce::dontSendNotification);
            if(inputNum!=0){
                OSClabel->setVisible(false);
                saveButton->setVisible(false);
            }else{
                addAndMakeVisible(p1.p2.p3);
            }

            if(!sender.send("/juce", 24, 0, inputCommand)){
                std::cout << "Cannot send the message" << std::endl;
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
