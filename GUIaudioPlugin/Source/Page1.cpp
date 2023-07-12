/*
  ==============================================================================

    Page1.cpp
    Created: 29 May 2023 4:47:14pm
    Author:  leo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Page1.h"

//==============================================================================
Page1::Page1()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    seshLabel.setEditable(true);
    seshLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    seshLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(seshLabel);

    titleLabel.setFont(16.0f);
    titleLabel.setText("Number of patterns:", juce::dontSendNotification);
    titleLabel.attachToComponent(&patLabel, true);

    patLabel.setEditable(true);
    patLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    patLabel.setJustificationType(juce::Justification::centred);
    
    confBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    confBtn.setButtonText("Confirm");
}

Page1::~Page1()
{
}

void Page1::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    auto area = getLocalBounds();
    g.setColour (juce::Colours::white);
    g.setFont (16.0f);
    g.drawText ("Enter session name", area.getCentreX()-150, area.getCentreY()-80, 300, 30, juce::Justification::centred, true);
}

void Page1::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    
    seshLabel.setBounds(area.getCentreX()-50, area.getCentreY()-50, 100, 30);
    patLabel.setBounds(area.getCentreX()-20, area.getCentreY(), 40, 30);
    confBtn.setBounds(area.getCentreX()-40,area.getCentreY()+60,80,30);
    p2.setBounds(area);
}
