# gipOscillator
This is a GlistEngine component who helps developers calibrate their connected devices by generating various types of signals for the calibration of devices and 3rd party software to be connected to the computer.

gipOscillator contains 10 different wave types who are the most common in the industry. These wave types are enumerated as follows:
WAVETYPE_SINE, WAVETYPE_SQUARE, WAVETYPE_TRIANGLE, WAVETYPE_SAWPOSITIVEINCREASING, WAVETYPE_SAWPOSITIVEDECREASING, WAVETYPE_SAWNEGATIVEINCREASING, WAVETYPE_SAWNEGATIVEDECREASING, WAVETYPE_SAWINCREASING, WAVETYPE_SAWDECREASING, WAVETYPE_COMPLEX

Note that complex wave type requires users to enter a specific function to create signals. And for all types of waves, developers can enter a wavelength value of their choice. Otherwise, initial value will apply. The wavelength variable is used to calculate the change index value, who is used in signal operations.

gipOscillator also contains a method to modify the wave length of the signals. Using this method, developers may calculate the value of angular or numerical change index depending on the wave type. 

This component is adaptable to framerate changes in the project that it is plugged in. This is assured by a method it contains.
