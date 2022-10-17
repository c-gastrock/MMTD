#include "DelayModule.h"

DelayParams::DelayParams() {
	this->enabled = nullptr;
	this->feedback = nullptr;
	this->delay = nullptr;
}

DelayParams::DelayParams(AudioParameterBool* enabled, AudioParameterFloat* feedback, AudioParameterFloat* delay) {
	this->enabled = enabled;
	this->feedback = feedback;
	this->delay = delay;
}

DelayModule::DelayModule() {
	this->feedbackKnob = nullptr;
	this->delayKnob = nullptr;
	this->enabledBt = nullptr;
}

DelayModule::DelayModule(Slider* feedbackKnob, Slider* delayKnob, ToggleButton* enabledBt) {
	this->feedbackKnob = feedbackKnob;
	this->delayKnob = delayKnob;
	this->enabledBt = enabledBt;
}