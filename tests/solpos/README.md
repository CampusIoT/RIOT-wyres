# Solar Position and Intensity

From https://www.nrel.gov/grid/solar-resource/solpos.html

NREL's Solar Position and Intensity (SOLPOS 2.0) C function calculates the apparent solar position and intensity (theoretical maximum solar energy) based on date, time, and location on Earth.

By accessing these files, you agree to abide by the NREL data disclaimer. This software has been tested on a variety of platforms, but it is not guaranteed to work on yours. It is provided here as a convenience
Documentation

This documentation provides an overview of the software functionality. The sample program `main.c` provides additional information by example on how the function is set up and called from an application program. That program serves as the only tutorial for the use of S_solpos.

The module contains three functions: 

* `S_solpos`` – Performs calculations
* `S_init` – Initializes S_solpos
* `S_decode` – Decodes the return value from `S_solpos`.

To obtain references for the algorithms, see the references section below. Comments in the source code specify references for each function.

`S_solpos` 	(computes solar position and intensity from time and place)
* INPUTS: (via posdata struct defined in solpos00.h) year, daynum, hour, minute, second, latitude, longitude, timezone, interval
* OPTIONAL: (via posdata struct) month, day, press, temp, tilt, aspect, function
* OUTPUTS: EVERY variable in the struct posdata (defined in solpos00.h)

`S_init` 	(optional initialization for all input parameters in the posdata struct)
* INPUTS: struct posdata*
* OUTPUTS: struct posdata*
Initializes the required S_solpos INPUTS above to out-of-bounds conditions, forcing the user to supply the parameters; initializes the OPTIONAL S_solpos inputs above to nominal values. See listing below for default values provided by S_init.

`S_decode` 	(optional utility for decoding the S_solpos return code)
* INPUTS: long int S_solpos return value, struct posdata*
* OUTOUTS: Text to stderr 