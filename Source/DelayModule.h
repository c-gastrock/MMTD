#pragma once
#include "JuceHeader.h"

using namespace juce;
	
class DelayModule : Component
{
	public:
		bool enabled;
		Slider* feedbackKnob;
		Slider* delayKnob;

		DelayModule();
		DelayModule(Slider* feedbackKnob, Slider* delayKnob, bool enabled);
};

