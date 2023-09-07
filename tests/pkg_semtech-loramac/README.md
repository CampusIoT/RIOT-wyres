# Simple test of the loramac stack 

You should comment the FEATURES_OPTIONAL += periph_eeprom in the Makefile, it is not defined in the board definition

## Build

LORA_DRIVER=sx1272 BOARD=wyres-base make -j 16


## Usage

In term type help to see commands

type command to see how to use

basic use to check communication with gateway :

set the lorawan variables
```
> loramac set deveui <deveui>
> loramac set appeui 0000000000000000
> loramac set appkey <appkey>
> loramac join otaa
Join procedure succeeded!
```
join message sould appear on chirpstack at this stage

use link_check command to display more information for next lora transaction
```
> loramac link_check
Link check request scheduled
```

Use cnf to ask for ACK
specify port next
```
> loramac tx HELLO cnf 12
Link check information:
  - Demodulation margin: 23
  - Number of gateways: 3
Received ACK from network
Message sent with success
```
see frame in chirpstack in Device Data on the device

