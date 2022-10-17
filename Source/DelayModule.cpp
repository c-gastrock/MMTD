#include "DelayModule.h"

DelayParams::DelayParams() {
	this->enabled = nullptr;
	this->feedback = nullptr;
	this->delay = nullptr;
	this->gain = nullptr;
}

DelayParams::DelayParams(AudioParameterBool* enabled, AudioParameterFloat* feedback, AudioParameterFloat* gain, AudioParameterFloat* delay) {
	this->enabled = enabled;
	this->feedback = feedback;
	this->delay = delay;
	this->gain = gain;
}

DelayModule::DelayModule() {
	this->feedbackKnob = nullptr;
	this->delayKnob = nullptr;
	this->enabledBt = nullptr;
	this->gainKnob = nullptr;
}

DelayModule::DelayModule(Slider* feedbackKnob, Slider* delayKnob, Slider* gainKnob, ToggleButton* enabledBt) {
	this->feedbackKnob = feedbackKnob;
	this->delayKnob = delayKnob;
	this->enabledBt = enabledBt;
	this->gainKnob = gainKnob;
}