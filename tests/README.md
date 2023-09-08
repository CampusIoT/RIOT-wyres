# RIOT test for `wyres-base` board

On-board
* [ ] button (interupt)
* [ ] tests/periph/eeprom
* [ ] tests/periph/wdt
* [ ] tests/periph/rtc
* [ ] tests/periph/pwm (pin PA1 on Speaker PA14/TP5 pad) play sound/alarm
* [ ] tests/drivers/lpsxxx
* [ ] tests/drivers/lis2dh12
* [ ] [SPH0641LM4H-1](https://www.knowles.com/docs/default-source/default-document-library/sph0641lm4h-1_morello_datasheet.pdf) MEMS microphone on I2S bus

Groove I2C connector (CN2)
* [ ] tests/drivers/bmx280
* [ ] tests/drivers/adcxx1c (I2C ADC multi-resolution)
* [ ] tests/drivers/sht1x
* [ ] tests/drivers/sht2x
* [ ] tests/drivers/sht3x
* [ ] tests/drivers/vl6180x (distance ToF for snow level)

Groove UART connector (CN3)
* [ ] gnss on UART(0)
* [ ] [pms7003](https://github.com/airqualitystation/firmware_for_bmx280_pms7003)

SPI connector (CN5)
* [ ] sdcard reader (for data logging)

GPIO Pad
* [ ] Rain gauge (PA8 on TP3 pad)
* [ ] PT1000 temperature probe (-85°C fridge)
* [ ] One Wire DS18B20 temperature probe (-55°C fridge)

Low-power mode
