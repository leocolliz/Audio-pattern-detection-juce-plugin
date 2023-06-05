/*
  ==============================================================================

    Page1.h
    Created: 29 May 2023 4:47:14pm
    Author:  leo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Page2.h"

//==============================================================================
/*
*/
class Page1  : public juce::Component
{
public:
    Page1();
    ~Page1() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::Label patLabel;
    juce::TextButton confBtn;

    Page2 p2;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Page1)
};
