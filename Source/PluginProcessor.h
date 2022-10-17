/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DelayModule.h"
#include "StkLite-4.6.2/StkLite-4.6.2/Delay.h"

#define MAXDELAYMS 2500.0f // 2500.0 b/c could potentially have many taps
#define PI MathConstants<float>::pi

using namespace juce;

//==============================================================================
/**
*/
class ChaseGP03MMTDAudioProcessor  : public AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ChaseGP03MMTDAudioProcessor();
    ~ChaseGP03MMTDAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    // User
    AudioParameterFloat* wetDryParam;

    // Private algo
    int numTaps = 3;
    float wetGain, dryGain;
    std::vector<DelayParams> tapParamList;

    std::vector<stk::Delay> delaysL, delaysR;
    float mFs;

    // Helper methods
    void setWetDryBalance(float userIn);
    void calcAlgorithmParams();
    int calcMsecToSamps(float maxDelay);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChaseGP03MMTDAudioProcessor)
};
