/*
  ==============================================================================

    Page2.cpp
    Created: 30 May 2023 9:24:35am
    Author:  leo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Page2.h"

//==============================================================================
Page2::Page2() : recBtn("recButton", juce::Colours::red, juce::Colours::red, juce::Colours::red),
                 stopBtn("stopButton", juce::Colours::grey, juce::Colours::darkgrey, juce::Colours::darkgrey)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::Path buttonShape;

    buttonShape.addEllipse (0,0, 50, 50);
    recBtn.setShape(buttonShape, true, true, false);

    addAndMakeVisible(recBtn);

    buttonShape.addRoundedRectangle(0,0, 50, 50, 5);
    stopBtn.setShape(buttonShape, true, true, false);

    addAndMakeVisible(stopBtn);

    undoBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    undoBtn.setButtonText("UNDO");

    addAndMakeVisible(undoBtn);

    titleLabel.setFont(16.0f);
    titleLabel.setText("OSC command:", juce::dontSendNotification);
    titleLabel.attachToComponent(&OSCcommandLabel, true);

    OSCcommandLabel.setEditable(true);
    OSCcommandLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    OSCcommandLabel.setJustificationType(juce::Justification::left);

    saveBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    saveBtn.setButtonText("SAVE");
}

Page2::~Page2()
{
}

void Page2::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    auto area = getLocalBounds();
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font("Arial", 18.0f, juce::Font::bold));
    g.drawText (seshName.toUpperCase(), area.getCentreX()-150, area.getCentreY()-150, 300, 30, juce::Justification::centred, true);
}

void Page2::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto area = getLocalBounds();
    
    recBtn.setCentrePosition(getWidth()/10+30,getHeight()/6+20);
    stopBtn.setCentrePosition(getWidth()/10+30,getHeight()/6+80);
    undoBtn.setBounds(getWidth()-105,getHeight()/6+40,80,30);
    OSCcommandLabel.setBounds(area.getCentreX()-80, getHeight()-85, 160, 30);
    saveBtn.setBounds(area.getCentreX()-40,getHeight()-25,80,30);
    p3.setBounds(area);
}