#pragma once
#include "JuceHeader.h"

using namespace juce;

class DelayParams {
	public:
		AudioParameterBool* enabled;
		AudioParameterFloat* feedback;
		AudioParameterFloat* delay; // maybe int

		DelayParams();
		DelayParams(AudioParameterBool* enabled, AudioParameterFloat* feedback, AudioParameterFloat* delay);
};
	
class DelayModule : Component
{
	public:
		ToggleButton* enabledBt;
		Slider* feedbackKnob; // % feedback
		Slider* delayKnob; // delay amount

		DelayModule();
		DelayModule(Slider* feedbackKnob, Slider* delayKnob, ToggleButton* enabledBt);
};

