#pragma once
#include "JuceHeader.h"

using namespace juce;

class DelayParams {
	public:
		AudioParameterBool* enabled;
		AudioParameterFloat* feedback;
		AudioParameterFloat* delay; // maybe int
		AudioParameterFloat* gain;

		DelayParams();
		DelayParams(AudioParameterBool* enabled, AudioParameterFloat* feedback, AudioParameterFloat* gain, AudioParameterFloat* delay);
};
	
class DelayModule : Component
{
	public:
		ToggleButton* enabledBt;
		Slider* feedbackKnob; // % feedback
		Slider* delayKnob; // delay amount
		Slider* gainKnob;

		DelayModule();
		DelayModule(Slider* feedbackKnob, Slider* delayKnob, Slider* gainKnob, ToggleButton* enabledBt);
};

