/*
  ==============================================================================

    Page3.cpp
    Created: 31 May 2023 9:06:35am
    Author:  leo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Page3.h"

//==============================================================================
Page3::Page3()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    trainBtn.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    trainBtn.setButtonText("TRAIN MODEL");

    addAndMakeVisible(trainBtn);

}

Page3::~Page3()
{
}

void Page3::paint (juce::Graphics& g)
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
    g.drawText (seshName->toUpperCase(), area.getCentreX()-150, area.getCentreY()-150, 300, 30, juce::Justification::centred, true);
}

void Page3::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto area = getLocalBounds();

    trainBtn.setBounds(area.getCentreX()-60,area.getCentreY()-15,120,30);
}