# periph/vbat

Le périphérique `periph/vbat` qui donne la tension de l'alimentation (ie VCC de la batterie) n'est pas implémenté par RIOT au niveau du STM32L151.

```bash
export BOARD=wyres-base
export EXTERNAL_BOARD_DIRS=~/github/campusiot/RIOT-wyres/boards
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/vbat
make -j 16 flash
```


## Quelques pistes pour l'ajout

* https://github.com/Lora-net/LoRaMac-node/blob/6384af8f4c4a57016c83f3d34430f0f68855e695/src/boards/NucleoL073/board.c#L278
* https://github.com/wyres/mynewt-generic-base/blob/master/generic/src/sensorMgr.c#L695
* https://github.com/Lora-net/LoRaMac-node/blob/master/src/boards/mcu/stm32/STM32L1xx_HAL_Driver/Inc/stm32l1xx_hal_adc.h#L451C1-L452C148



Dans https://github.com/wyres/mynewt-generic-base/blob/f27c7ede5e48b621667b98170349ed64fecd1872/generic/src/sensorMgr.c#L47

```c
#define BATTERY_GPIO    (128)                   // needs a gpio pin number, but of a value that is beyond 'real' ones
#define BATTERY_ADCCHAN (ADC_CHANNEL_VREFINT)

#define ADC_MAX_VALUE                               4095    // 12 bits max value
// Should read the factory calibrated vref from the eerom at 0x1FF8 00F8/9
#define ADC_VREF_BANDGAP                            1224    // vRef in mV for ADC


        if (BATTERY_GPIO>=0) 
        {
            int newvalue = GPIO_readADC(BATTERY_GPIO);       
            // We don't use the VREF from calibValues here, rather a constant calculation
            // calculate the Voltage in millivolt
            if (newvalue > 0) {
                newvalue = ( uint32_t )ADC_VREF_BANDGAP * ( uint32_t )ADC_MAX_VALUE / ( uint32_t )newvalue;
            }
            _ctx.currBattmV = (newvalue + _ctx.currBattmV)/2;   // Average it a little as battery value changes slowly over time
//            log_debug("S bat %d", _ctx.currBattmV);
```