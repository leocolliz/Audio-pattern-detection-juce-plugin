/*
  ==============================================================================

    Page0.cpp
    Created: 23 Jun 2023 12:00:38pm
    Author:  leo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Page0.h"

//==============================================================================
Page0::Page0()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    createBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    createBtn.setButtonText("Create new session");

    addAndMakeVisible(createBtn);

    openBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    openBtn.setButtonText("Open session");

    addAndMakeVisible(openBtn);
}

Page0::~Page0()
{
}

void Page0::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Page0::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();

    createBtn.setBounds(area.getCentreX()-80,area.getCentreY()-100,160,60);
    openBtn.setBounds(area.getCentreX()-80,area.getCentreY()-30,160,60);

    p1.setBounds(area);
    p4.setBounds(area);
}
