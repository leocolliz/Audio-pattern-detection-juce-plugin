/*
  ==============================================================================

    Page2.h
    Created: 30 May 2023 9:24:35am
    Author:  leo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Page3.h"

//==============================================================================
/*
*/
class Page2  : public juce::Component
{
public:
    Page2();
    ~Page2() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::ShapeButton recBtn;
    juce::ShapeButton stopBtn;
    juce::TextButton undoBtn;
    juce::Label titleLabel;
    juce::Label OSCcommandLabel;
    juce::TextButton saveBtn;

    Page3 p3;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Page2)
};