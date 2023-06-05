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

    modelLabel.setEditable(true);
    modelLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    modelLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(modelLabel);

    goBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    goBtn.setButtonText("GO");

    addAndMakeVisible(goBtn);

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
    g.setFont (14.0f);
    g.drawText ("Enter the model name", area.getCentreX()-150, area.getCentreY()-75, 300, 30, juce::Justification::centred, true);
}

void Page4::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto area = getLocalBounds();

    modelLabel.setBounds(area.getCentreX()-80, area.getCentreY()-40, 160, 30);
    goBtn.setBounds(area.getCentreX()-60,getHeight()-110,120,30);
}
