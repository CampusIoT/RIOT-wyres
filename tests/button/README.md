# LED test

This is a basic example how to toogle the leds

## Build
```
make
```


## Console
```bash
make term
```

```bash
tio -L
tio -b 115200 -m INLCRNL /dev/tty.usbmodem142xxx
```

```
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)

Test light sensor

Successfully initialized ADC_LINE(0)
ADC_LINE(0): raw value: 0157, percent: 03 % 
ADC_LINE(0): raw value: 0159, percent: 03 % 
ADC_LINE(0): raw value: 0160, percent: 03 % 
ADC_LINE(0): raw value: 0153, percent: 03 % 
ADC_LINE(0): raw value: 0201, percent: 04 % 
ADC_LINE(0): raw value: 0325, percent: 07 % 
ADC_LINE(0): raw value: 0567, percent: 13 % 
ADC_LINE(0): raw value: 0496, percent: 12 % 
ADC_LINE(0): raw value: 0524, percent: 12 % 
ADC_LINE(0): raw value: 0427, percent: 10 % 
ADC_LINE(0): raw value: 0245, percent: 05 % 
ADC_LINE(0): raw value: 0164, percent: 04 % 
``