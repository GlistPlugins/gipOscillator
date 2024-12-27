/*
 * gApp.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GAPP_H_
#define GAPP_H_

#include "gBaseApp.h"
#include "gipOscillator.h"

/**
 * gApp in GlistOscillator project is a generative application to test gipOscillator component.
 */
class gApp : public gBaseApp {
public:
	gApp();
	gApp(int argc, char **argv);
	~gApp();

	/**
	 * Sets the framerate to 60fps.
	 *
	 * Sets oscillator object.
	 *
	 * Sets oscillator's complex wave function (if applicable).
	 *
	 * Sets oscillators's wavelength.
	 *
	 * Sets oscillator's wave type.
	 */
	void setup();
	void update();

	/**
	 * Returns the value of the complex wave signal.
	 *
	 * @param inputValue Developers may enter whatever complex function here.
	 * @return calculateComplexSignal(inputValue).
	 */
	float getComplexSignal(float inputValue);

private:
	gipOscillator oscillator;

	/**
	 * Returns the complex wave function.
	 *
	 * @param inputValue Developers may enter whatever complex function here.
	 * @return inputValue The complex wave function.
	 */
	float calculateComplexSignal(float inputValue);
};

#endif /* GAPP_H_ */
