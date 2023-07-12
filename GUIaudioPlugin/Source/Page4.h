/*
  ==============================================================================

    Page4.h
    Created: 3 Jun 2023 6:38:54pm
    Author:  leo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Page4  : public juce::Component
{
public:
    Page4();
    ~Page4() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::TextButton startBtn;
    juce::TextButton deleteBtn;

    juce::ComboBox sessionBox;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Page4)
};
