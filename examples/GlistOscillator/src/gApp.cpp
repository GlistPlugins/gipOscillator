/*
 * gApp.cpp
 *
 *  Created on: May 6, 2024
 *      Author: Mustafa Kemal Keskin, Noyan Culum
 */

#include "gApp.h"


gApp::gApp() {
}

gApp::gApp(int argc, char **argv) : gBaseApp(argc, argv) {
}

gApp::~gApp() {
}

void gApp::setup() {
	oscillator.setFramerate(60);
	setTargetFramerate(oscillator.getFramerate());
	oscillator.setup();
	oscillator.setComplexWaveFunction(std::bind(&gApp::getComplexSignal, this, std::placeholders::_1));
	oscillator.setWaveLength(1.0f);

	// CHANGE THIS FOR OTHER WAVE TYPES
	oscillator.setWaveType(gipOscillator::WAVETYPE_SAWDECREASING);
}

void gApp::update() {
	gLogi("gApp") << "Signal:" << oscillator.getSignal();
}

float gApp::getComplexSignal(float inputValue) {
	return calculateComplexSignal(inputValue);
}

float gApp::calculateComplexSignal(float inputValue) {
	float inputvalue = inputValue;
	inputvalue *= 0.5f; // Whatever complex function you want here
	return inputvalue;
}
