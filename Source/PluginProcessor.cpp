/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
ChaseGP03MMTDAudioProcessor::ChaseGP03MMTDAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(wetDryParam = new AudioParameterFloat("Wet/Dry", // parameterID,
        "WetDry", // parameterName,
        -1.0f, // fully dry,
        1.0f, // fully wet,
        0)); // wet and dry mixed equally by default

    AudioParameterFloat* tempDly;
    AudioParameterFloat* tempFb;
    AudioParameterBool* tempEnab;

    for (int i = 0; i < numTaps; i++) {
        addParameter(tempDly = new AudioParameterFloat("delay" + std::to_string(i + 1), // parameterID,
            "Delay " + std::to_string(i + 1) + " (ms)", // parameterName,
            0.0f, // minValue,
            5000.0f, // maxValue,
            40.0f + (20.0f * i))); // default

        addParameter(tempFb = new AudioParameterFloat("fb" + std::to_string(i + 1), // parameterID,
            "Feedback " + std::to_string(i + 1) + " (%)", // parameterName,
            0.0f, // minValue,
            100.0f, // maxValue,
            15.0f)); // default

        addParameter(tempEnab = new AudioParameterBool("enabled" + std::to_string(i + 1), // parameterID,
            "Enabled " + std::to_string(i + 1) + "", // parameterName,
            true)); // default

        taps.push_back(DelayParams(tempEnab, tempFb, tempDly));
    }
    
}

ChaseGP03MMTDAudioProcessor::~ChaseGP03MMTDAudioProcessor()
{
}

//==============================================================================
const String ChaseGP03MMTDAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChaseGP03MMTDAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChaseGP03MMTDAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChaseGP03MMTDAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChaseGP03MMTDAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChaseGP03MMTDAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChaseGP03MMTDAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChaseGP03MMTDAudioProcessor::setCurrentProgram (int index)
{
}

const String ChaseGP03MMTDAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChaseGP03MMTDAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChaseGP03MMTDAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ChaseGP03MMTDAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChaseGP03MMTDAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChaseGP03MMTDAudioProcessor::setWetDryBalance(float userIn) {
    userIn *= 0.5;
    wetGain = userIn + 0.5f;
    dryGain = abs(userIn - 0.5f); // can be negative
}

void ChaseGP03MMTDAudioProcessor::calcAlgorithmParams() {
    setWetDryBalance(wetDryParam->get());
}

void ChaseGP03MMTDAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // run calculations
    calcAlgorithmParams();

    auto* channelL = buffer.getWritePointer(0);
    auto* channelR = buffer.getWritePointer(1);

    for (int samp = 0; samp < buffer.getNumSamples(); samp++)
    {
        // Apply each filter in sequence
        for (int i = 0; i < numTaps; i++) {
            //channelL[samp] = filterLs[i].tick(channelL[samp]);
            //channelR[samp] = filterRs[i].tick(channelR[samp]);
        }
    }
}

//==============================================================================
bool ChaseGP03MMTDAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChaseGP03MMTDAudioProcessor::createEditor()
{
    return new ChaseGP03MMTDAudioProcessorEditor (*this);
}

//==============================================================================
void ChaseGP03MMTDAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChaseGP03MMTDAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChaseGP03MMTDAudioProcessor();
}
