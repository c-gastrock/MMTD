#include "DelayModule.h"

DelayModule::DelayModule() {
	this->feedbackKnob = nullptr;
	this->delayKnob = nullptr;
	this->enabled = false;
}

DelayModule::DelayModule(Slider* feedbackKnob, Slider* delayKnob, bool enabled) {
	this->feedbackKnob = feedbackKnob;
	this->delayKnob = delayKnob;
	this->enabled = enabled;
}