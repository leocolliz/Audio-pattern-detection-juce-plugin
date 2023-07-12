/*
  ==============================================================================

    Page4.cpp
    Created: 3 Jun 2023 6:38:54pm
    Author:  leo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Page4.h"

//==============================================================================
Page4::Page4()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(sessionBox);

    startBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    startBtn.setButtonText("START SESSION");

    deleteBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    deleteBtn.setButtonText("DELETE SESSION");

    addAndMakeVisible(startBtn);
    addAndMakeVisible(deleteBtn);

}

Page4::~Page4()
{
}

void Page4::paint (juce::Graphics& g)
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
    g.drawText ("Select the session", area.getCentreX()-150, area.getCentreY()-75, 300, 30, juce::Justification::centred, true);
}

void Page4::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto area = getLocalBounds();

    sessionBox.setBounds(area.getCentreX()-80,getHeight()-190,160, 30);
    startBtn.setBounds(area.getCentreX()-60,getHeight()-150,120,30);
    deleteBtn.setBounds(area.getCentreX()-60,getHeight()-110,120,30);
}