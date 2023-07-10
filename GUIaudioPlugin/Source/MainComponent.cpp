#include "MainComponent.h"
#include <unistd.h> 

//==============================================================================
MainComponent::MainComponent()
{
    if( sender.connect("127.0.0.1", 8000)){
        std::cout << "Connected sender GUI" << std::endl;
    }

    if(connect(9000)){
        std::cout << "Connected reciever GUI" << std::endl;
    }

    addListener(this, "/data");

    //Page 0 buttons
    
    createButton=   &(p0.createBtn);
    openButton  =   &(p0.openBtn);

    createButton->addListener(this);
    openButton->addListener(this);

    //Page 1 buttons

    sessionLabel=   &(p0.p1.seshLabel);
    patternLabel=   &(p0.p1.patLabel);
    confButton  =   &(p0.p1.confBtn);
    
    sessionLabel->addListener(this);
    patternLabel->addListener(this);
    confButton->addListener(this);

    //Page 2 buttons

    recButton   =   &(p0.p1.p2.recBtn);
    stopButton  =   &(p0.p1.p2.stopBtn);
    undoButton  =   &(p0.p1.p2.undoBtn);
    OSClabel    =   &(p0.p1.p2.OSCcommandLabel);
    saveButton  =   &(p0.p1.p2.saveBtn);
    
    recButton->addListener(this);
    stopButton->addListener(this);
    undoButton->addListener(this);
    OSClabel->addListener(this);
    saveButton->addListener(this);

    //Page 3 buttons

    trainButton =   &(p0.p1.p2.p3.trainBtn);
    p0.p1.p2.p3.seshName = &(sessionName);

    trainButton->addListener(this);

    //Page 4 buttons

    sessionBox  =   &(p0.p4.sessionBox);
    startButton =   &(p0.p4.startBtn);
    deleteButton =  &(p0.p4.deleteBtn);

    sessionBox->addListener(this);
    startButton->addListener(this);
    deleteButton->addListener(this);
    
    addAndMakeVisible(p0);
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

    p0.setBounds(area);
}

void MainComponent::labelTextChanged(juce::Label* labelThatHasChanged)
{
    //PAGE 1 LABEL
    if(labelThatHasChanged==sessionLabel){
        addAndMakeVisible(patternLabel);
    }
    if(labelThatHasChanged==patternLabel){
        addAndMakeVisible(confButton);
    }
    //PAGE 2 LABEL
    if(labelThatHasChanged==OSClabel){
        
    }
}

void MainComponent::buttonClicked (juce::Button * button)
{
    juce::OSCMessage mex("/juce");
    mex.addInt32(1);
    mex.addInt32(0);
    mex.addString(" ");

    //PAGE 0 BUTTONS
    if(button==createButton){
        addAndMakeVisible(p0.p1);
        for(auto ip : juce::IPAddress::getAllAddresses()){
            std::cout << ip.toString() << std::endl;
        }
        if(!sender.send(mex)){
            std::cout << "Cannot send the message" << std::endl;
        }
    }if(button==openButton){
        addAndMakeVisible(p0.p4);
        startButton->setVisible(false);
        deleteButton->setVisible(false);
        mex[0]=2;
        if(!sender.send(mex)){
            std::cout << "Cannot send the message" << std::endl;
        }
    }
    //PAGE 1 BUTTONS
    if(button==confButton){
        sessionName=sessionLabel->getText();
        inputNum = patternLabel->getText().getIntValue();
        if(!sessionName.isEmpty()&&inputNum<=10){
            p0.p1.p2.seshName = sessionName;
            std::cout << "You can now record your " << inputNum << " patterns" << std::endl;
            addAndMakeVisible(p0.p1.p2);

            mex[0]=11;
            mex[1]=inputNum;
            mex[2]=sessionName;
            if(!sender.send(mex)){
                std::cout << "Cannot send the message" << std::endl;
            }

            stopButton->setEnabled(false);
            undoButton->setEnabled(false);
            saveButton->setEnabled(false);
        }if(sessionName.isEmpty()){
            std::cerr << "Empty session name" << std::endl;
        }if(inputNum>10){
            std::cerr << "Max number of patterns is 10" << std::endl;
        }
    }
    //PAGE 2 BUTTONS
    if(button==recButton){
        recButton->setOutline(juce::Colours::darkred, 10);
        std::cout << "Recording..." << std::endl;
        startRec=true;
        
        mex[0]=21;
        if(!sender.send(mex)){
            std::cout << "Cannot send the message" << std::endl;
        }

        recButton->setEnabled(false);
        stopButton->setEnabled(true);
        undoButton->setEnabled(false);
        saveButton->setEnabled(false);

    }if(button==stopButton && startRec){
        std::cout << "Stopped recording!" << std::endl;
        recButton->setVisible(false);
        recButton->setOutline(juce::Colours::red, 10);
        addAndMakeVisible(recButton);
        startRec=false;

        mex[0]=22;
        if(!sender.send(mex)){
            std::cout << "Cannot send the message" << std::endl;
        }
        sleep(1);
        if(!emptyTrack){                        
            addAndMakeVisible(OSClabel);
            addAndMakeVisible(saveButton);
            undoButton->setEnabled(true);
            saveButton->setEnabled(true);
            recButton->setEnabled(false);
            stopButton->setEnabled(false);
            inputNum--;
        }else{
            std::cerr << "Empty track recorded!" << std::endl;
        }

    }if(button==undoButton){
        inputNum++;

        mex[0]=23;
        if(!sender.send(mex)){
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
                addAndMakeVisible(p0.p1.p2.p3);
            }

            mex[0]=24;
            mex[2]=inputCommand;
            if(!sender.send(mex)){
                std::cout << "Cannot send the message" << std::endl;
            } 

            undoButton->setEnabled(false);
            recButton->setEnabled(true);
            
        }else{
            std::cerr << "Empty OSC command" << std::endl;
        }if(inputNum==0){
            addAndMakeVisible(p0.p1.p2.p3);
        }
    }

    //PAGE 3 BUTTONS
    if(button==trainButton){
        mex[0]=31;
        if(!sender.send(mex)){
            std::cout << "Cannot send the message" << std::endl;
        }
    }

    //PAGE 4 BUTTONS
    if(button==startButton){
        //start the inference
    }if(button==deleteButton){
        mex[0]=42;
        mex[2]=sessionBox->getText();
        sessionBox->clear();
        if(!sender.send(mex)){
            std::cout << "Cannot send the message" << std::endl;
        }
        p0.p4.setVisible(false);
    }
}

void MainComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged){
    if(comboBoxThatHasChanged==sessionBox){
        startButton->setVisible(true);
        deleteButton->setVisible(true);
    }
}

void MainComponent::oscMessageReceived(const juce::OSCMessage &message){
    if(message[0].isInt32()){
        if(message[0].getInt32()==0){
            emptyTrack=true;
        }if(message[0].getInt32()==1){
            juce::MessageManagerLock mml;
            p0.p4.setVisible(false);
        }if(message[0].getInt32()==200){
            std::cout << "Trained model downloaded" << std::endl;
        }if(message[0].getInt32()==404){
            std::cout << "Download failed" << std::endl;
            juce::MessageManagerLock mml;
            p0.p1.p2.p3.setVisible(false);
            p0.p1.p2.setVisible(false);
            p0.p1.setVisible(false);
        }
    }if(message[0].isString()){
        int i = 0;
        while(!message[i].isInt32()){
            sessionBox->addItem(message[i].getString(),i+1);
            i++;
        }
    }
}