/****************************************************************************
 * Copyright (c) 2024 Nitra Games Ltd., Istanbul, Turkey                    *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice should not be      *
 * deleted from the source form of the Software.                            *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 * Author: Noyan Culum & Mustafa Kemal Keskin, 2024-Sep                                            *
 ****************************************************************************/

/*
 * gipOscillator.h
 *
 *  Created on: Sept 22, 2024
 *      Author: Noyan Culum & Mustafa Kemal Keskin
*/

#ifndef SRC_GIPOSCILLATOR_H_
#define SRC_GIPOSCILLATOR_H_

#include "gBaseComponent.h"
#include <functional>


/**
 * gipOscillator is a GlistEngine component that generates signals to calibrate connected devices.
 */
class gipOscillator : public gBaseComponent{
public:

	/**
	 * Each enumeration signifies a wave type that developers can choose.
	 *
	 * There are 6 different sawtooth wave types that act differently.
	 * POSITIVE or NEGATIVE after the underscore means that the wave can have values in the intervals of
	 * [0.0f , 1.0f] or [-1.0f , 0.0f] respectively. INCREASING or DECREASING after POSITIVE OR NEGATIVE means that the wave
	 * goes from a lower value to a higher value. Solely INCREASING or DECREASING after the underscore means that the wave
	 * can have values between -1.0f to 1.0f.
	 */
	enum {
		WAVETYPE_SINE, WAVETYPE_SQUARE, WAVETYPE_TRIANGLE, WAVETYPE_SAWPOSITIVEINCREASING, WAVETYPE_SAWPOSITIVEDECREASING,
		WAVETYPE_SAWNEGATIVEINCREASING, WAVETYPE_SAWNEGATIVEDECREASING, WAVETYPE_SAWINCREASING, WAVETYPE_SAWDECREASING,
		WAVETYPE_COMPLEX
	};

	gipOscillator();
	virtual ~gipOscillator();

	/**
	 * Initializes values of variables
	 *
	 * Initial values are:
	 * - signal = 0.0f;
	 * - wavetype = WAVETYPE_SINE;
	 * - anglerad = 0.0f;
	 * - anglelimit = PI / 2;
	 * - anglediff = PI / 60;
	 * - wavelength = 1.0f;
	 * - iscomplexfuncset = false;
	 *
	 * anglerad is the angle or the main index. It is processed in functions and methods.
	 *
	 * anglediff is the change index that is calculated by the method setWaveLength(float waveLength).
	 * It can either be angular or numerical.
	 */

	void setup();

	/**
	 * Updates the angle and includes functions that make oscillations work.
	 *
	 * NOTE: None of the calculations result higher than 1.0f and lower than -1.0f.
	 * NOTE: Deevelopers must enter a wave length and a wave type in order for this function to make calculations.
	 *
	 *
	 * In order to generate a SINE WAVE, this function changes the angle by constantly adding the angular change index calculated by
	 * setWaveLength(float waveLength) method. Then, continuously calculates the sine of the angle.
	 * When the angle is at the upper or the lower angle limit, the function changes the sign of the angular change index.
	 * By this way, the wave oscillation limit stays between -1.0f and 1.0f.
	 *
	 * In order to generate a SQUARE WAVE, this function changes the angle by adding the angular change index calculated by
	 * setWaveLength(float waveLength) method. Then, continuously calculates the sine of the angle.
	 * Later, takes the sign by using gSign() method and multiplies it by 1.0f.
	 * When the angle is at the upper or the lower angle limit, the function changes the sign of the angular change index.
	 * By this way, the wave can only have -1.0f or 1.0f as value.
	 *
	 * In order to generate a TRIANGLE WAVE, this function changes the ordinate's value by constantly adding the change index calculated by
	 * setWaveLength(float waveLength) method. When the result is equal to 1.0f or -1.0f, the function changes the sign
	 * of the change index.
	 *
	 * In order to generate any type of SAWTOOTH WAVE types enumerated, this function changes the ordinate's value by constantly adding
	 * the change index calculated by setWaveLength(float waveLength) method. Each wave type has its own limits and change
	 * conditions. Detailed information can be found at the explanation lines of the enumerated wave types.
	 *
	 * In order to generate a COMPLEX WAVE, developers must enter a complex function (std::function<float(float)>) to
	 * setComplexWaveFunction(std::function<float(float)> complexFunc). Later on, the function will continously find the
	 * result of the function depending on the change index calculated by the method setWaveLength(float waveLength)
	 * into which developers must enter the wavelength.
	 */
	void update();

	/**
	 * Changes the type of the wave in order to calculate
	 *
	 * @param waveType One of the enumeration values from WAVETYPE_SINE to WAVETYPE_COMPLEX
	 */
	void setWaveType(int waveType);

	/**
	 * Returns the wave type set
	 *
	 * @return wavetype
	 */
	int getWaveType();

	/**
	 * Sets the wavelength and calculates the angular or numerical change index (anglediff).
	 *
	 * @param wavelength A float value that developers may enter freely.
	 */
	void setWaveLength(float waveLength);

	/**
	 * Returns the wavelength
	 *
	 * @return wavelength
	 */
	float getWaveLength();

	/**
	 * Returns angular or numerical change index (anglediff).
	 *
	 * @return anglediff
	 */
	float getAngleDiff();

	/**
	 * Returns the signal
	 *
	 * @return signal
	 */
	float getSignal();

	/**
	 * Sets the complex wave function entered by developers. After the entry, the function becomes processed by update() in order
	 * to calculate results of the function.
	 */
	void setComplexWaveFunction(std::function<float(float)> complexFunc);

	void setFramerate(int frameRate);
	int getFramerate();

private:
	float signal;
	int wavetype;
	float anglerad;
	float anglelimit;
	float anglediff;
	float wavelength;
	std::function<float(float)> complexfunc;
	bool iscomplexfuncset;
	int framerate;
};

#endif /* SRC_GIPOSCILLATOR_H_ */
