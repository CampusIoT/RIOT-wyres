# Simple test of driver

## Build

```bash
make
make BOARD=wyres-base DRIVER=sx1272 -j 16
```

## Usage

In term type help to see commands

type command to see how to use

basic use to check communication between 2 boards :

* On receving board :
```
> setup 125 12 5
> channel set 868000000
> listen
```

* On seending board :
```
> setup 125 12 5
> channel set 868000000
> send This\ is\ RIOT!
```

* On receiving board you should see :
```
{Payload: "This is RIOT!" (13 bytes), RSSI: 103, SNR: 240}
```
