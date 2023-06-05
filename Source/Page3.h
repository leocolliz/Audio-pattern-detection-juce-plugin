/*
  ==============================================================================

    Page3.h
    Created: 31 May 2023 9:06:35am
    Author:  leo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Page3  : public juce::Component
{
public:
    Page3();
    ~Page3() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Label modelLabel;
    juce::TextButton trainBtn;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Page3)
};
