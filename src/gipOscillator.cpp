/*
 * gipOscillator.cpp
 *
 *  Created on: Sept 22, 2024
 *      Author: Noyan Culum & Mustafa Kemal Keskin
 */

#include "gipOscillator.h"
#include <cmath>



gipOscillator::gipOscillator() {
}

gipOscillator::~gipOscillator() {
}

void gipOscillator::setup() {
	signal = 0.0f;
	wavetype = WAVETYPE_SINE;
	anglerad = 0.0f;
	anglelimit = PI / 2;
	anglediff = PI / 60;
	wavelength = 1.0f;
	iscomplexfuncset = false;
	framerate = 60;
}

void gipOscillator::update() {
	if(wavetype == WAVETYPE_SINE || wavetype == WAVETYPE_SQUARE || wavetype == WAVETYPE_COMPLEX) {
		anglerad += anglediff;
		if(anglerad >= anglelimit || anglerad <= -anglelimit) {
			float sar = gSign(anglerad);
			if(sar == 0.0f) sar = 1.0f;
			anglerad = sar * anglelimit;
			anglediff = -anglediff;
		}
		if(wavetype == WAVETYPE_SQUARE || wavetype == WAVETYPE_SINE) signal = std::sin(anglerad);
		if(wavetype == WAVETYPE_SQUARE) {
			float ssi = gSign(signal);
			if(ssi == 0.0f) ssi = 1.0f;
			signal = ssi * 1.0f;
		}
		else if (wavetype == WAVETYPE_COMPLEX) {
			if(!iscomplexfuncset) return;
			signal = complexfunc(anglerad);
		}
	} else if(wavetype == WAVETYPE_TRIANGLE) {
		 signal += anglediff;
		 if(signal >= 1.0f || signal <= -1.0f) anglediff = -anglediff;


	} else if(wavetype == WAVETYPE_SAWPOSITIVEINCREASING) {
		 signal += anglediff;
		 if(signal >= 1.0f) signal = 0.0f;
	} else if(wavetype == WAVETYPE_SAWNEGATIVEDECREASING) {
		 signal -= anglediff;
		 if(signal <= -1.0f) signal = 0.0f;
	} else if(wavetype == WAVETYPE_SAWPOSITIVEDECREASING) {
		 signal -= anglediff;
		 if(signal <= 0.0f) signal = 1.0f;
	} else if(wavetype == WAVETYPE_SAWNEGATIVEINCREASING) {
		 signal += anglediff;
		 if(signal >= 0.0f) signal = -1.0f;
	} else if(wavetype == WAVETYPE_SAWINCREASING) {
		 signal += anglediff;
		 if(signal >= 1.0f) signal = -1.0f;
	} else if(wavetype == WAVETYPE_SAWDECREASING) {
		 signal -= anglediff;
		 if(signal <= -1.0f) signal = 1.0f;
	}

	if(signal > 1.0f) signal = 1.0f;
	if(signal < -1.0f) signal = -1.0f;
}

void gipOscillator::setWaveType(int waveType) {
	wavetype = waveType;
}

int gipOscillator::getWaveType() {
	return wavetype;
}

void gipOscillator::setWaveLength(float waveLength) {
	wavelength = waveLength;
	if(wavetype == WAVETYPE_TRIANGLE || wavetype == WAVETYPE_SAWPOSITIVEINCREASING || wavetype == WAVETYPE_SAWNEGATIVEINCREASING
	   || wavetype == WAVETYPE_SAWPOSITIVEDECREASING || wavetype == WAVETYPE_SAWNEGATIVEINCREASING
	   || wavetype == WAVETYPE_SAWINCREASING || wavetype == WAVETYPE_SAWDECREASING) {
		anglediff = wavelength / getFramerate();
	} else {
		anglediff = PI / (wavelength * getFramerate());
	}
	//gLogi("gipOscillator") << "anglediff:" << anglediff;
}

float gipOscillator::getWaveLength() {
	return wavelength;
}

float gipOscillator::getAngleDiff() {
	return anglediff;
}

float gipOscillator::getSignal() {
	return signal;
}

void gipOscillator::setComplexWaveFunction(std::function<float(float)> complexFunc) {
	complexfunc = complexFunc;
	iscomplexfuncset = true;
}

void gipOscillator::setFramerate(int frameRate) {
	framerate = frameRate;
}

int gipOscillator::getFramerate() {
	return framerate;
}
