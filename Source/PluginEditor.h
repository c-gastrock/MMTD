/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ChaseGP03MMTDAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChaseGP03MMTDAudioProcessorEditor (ChaseGP03MMTDAudioProcessor&);
    ~ChaseGP03MMTDAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChaseGP03MMTDAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChaseGP03MMTDAudioProcessorEditor)
};
