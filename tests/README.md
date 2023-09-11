# RIOT test for `wyres-base` board

On-board
* [ ] button (interupt)
* [ ] tests/periph/eeprom
* [ ] tests/periph/wdt
* [ ] tests/periph/rtc
* [ ] tests/periph/pwm (pin PA1 on Speaker PA14/TP5 pad) - application : play sound/alarm
* [ ] tests/drivers/lpsxxx - application : altimeter
* [ ] tests/drivers/[lis2dh12](https://www.st.com/en/mems-and-sensors/lis2dh12.html) - application :  motion sensor for door opening, bird nest activity, inclinometer (windsocks, railway barrier on Level crossing, bike theft)... 
* [ ] [SPH0641LM4H-1](https://www.knowles.com/docs/default-source/default-document-library/sph0641lm4h-1_morello_datasheet.pdf) MEMS microphone on I2S bus - application : sound/noise dB level, shootgun timestamping ...

Groove I2C connector (CN2)
* [ ] tests/drivers/bmx280
* [ ] tests/drivers/adcxx1c (I2C ADC multi-resolution) - application : 
* [ ] tests/drivers/sht1x - application : microclimat station (temperature, humidity and pressure)
* [ ] tests/drivers/sht2x - application : microclimat station (temperature, humidity and pressure)
* [ ] tests/drivers/sht3x - application : microclimat station (temperature, humidity and pressure)
* [ ] tests/drivers/vl6180x - application : ToF distance  for snow level with IGE (Aiguille du Midi), parking sensor ...
* [ ] tests/drivers/at24cxxx - application : external I2C EEPROM for data logging
* [ ] tests/drivers/at25cxxx - application : external I2C EEPROM for data logging

Groove UART connector (CN3)
* [ ] gnss on UART(0) - application : sounding balloon
* [ ] [pms7003](https://github.com/airqualitystation/firmware_for_bmx280_pms7003) - application : Air quality station

SPI connector (CN5)
* [ ] sdcard reader - application : for data logging

Button Pad
* [ ] tests/periph/gpio - application : panic button, reset with reed switch, reed switch for door/window opening, [tiltmeter](https://en.wikipedia.org/wiki/Tiltmeter)

GPIO Pad
* [ ] Rain gauge (PA8 on TP3 pad) - application : microclimat station
* [ ] PT1000 temperature probe (-200°C to -85°C) - application : fridge monitor (UFR Pharmacie @ Bat Jean Roger)
* [ ] One Wire DS18B20 temperature probe (-55°C) - application : fridge monitor (UFR Pharmacie @ Bat Jean Roger), Permafrost (@ Aiguille du Midi)

Low-power mode
* [ ] [X-NUCLEO-LPM01A Power Shield](https://github.com/CampusIoT/tutorial/tree/master/x-nucleo-lpm01a)
* [ ] [nRF PPK II](https://github.com/CampusIoT/tutorial/tree/master/nrf-ppk2)
