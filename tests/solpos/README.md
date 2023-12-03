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

## Console

```bash
gmake -j 16
```

```
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)

***** TEST S_solpos: *****

Note that your final decimal place values may vary
based on your computer's floating-point storage and your
compiler's mathematical algorithms.  If you agree with
NREL's values for at least 5 significant digits, assume it works.

Note that S_solpos has returned the day and month for the
input daynum.  When configured to do so, S_solpos will reverse
this input/output relationship, accepting month and day as
input and returning the day-of-year in the daynum variable.

NREL    -> 1999.07.22, daynum 203, retval 0, amass 1.335752, ampress 1.326522
SOLTEST -> 1999.7.22, daynum 203, retval 0, amass 1.335752, ampress 1.326522
NREL    -> azim 97.032875, cosinc 0.912569, elevref 48.409931
SOLTEST -> azim 97.032875, cosinc 0.912569, elevref 48.409931
NREL    -> etr 989.668518, etrn 1323.239868, etrtilt 1207.547363
SOLTEST -> etr 989.668518, etrn 1323.239868, etrtilt 1207.547363
NREL    -> prime 1.037040, sbcf 1.201910, sunrise 347.173431
SOLTEST -> prime 1.037040, sbcf 1.201910, sunrise 347.173431
NREL    -> sunset 1181.111206, unprime 0.964283, zenref 41.590069
SOLTEST -> sunset 1181.111206, unprime 0.964283, zenref 41.590069
Raw airmass loop:
NREL    -> 37.92  5.59  2.90  1.99  1.55  1.30  1.15  1.06  1.02  1.00
SOLTEST -> 37.92  5.59  2.90  1.99  1.55  1.30  1.15  1.06  1.02  1.00 
```