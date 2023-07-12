/*
  ==============================================================================

    Page0.h
    Created: 23 Jun 2023 12:00:38pm
    Author:  leo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Page1.h"
#include "Page4.h"

//==============================================================================
/*
*/
class Page0  : public juce::Component
{
public:
    Page0();
    ~Page0() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::TextButton createBtn;
    juce::TextButton openBtn;

    Page1 p1;
    Page4 p4;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Page0)
};
