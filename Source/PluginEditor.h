/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace juce;

//==============================================================================
/**
*/
class ChaseGP03MMTDAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ChaseGP03MMTDAudioProcessorEditor (ChaseGP03MMTDAudioProcessor&);
    ~ChaseGP03MMTDAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChaseGP03MMTDAudioProcessor& audioProcessor;
    int numTaps = 3;
    std::vector<DelayModule> delayModules;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChaseGP03MMTDAudioProcessorEditor)
};
