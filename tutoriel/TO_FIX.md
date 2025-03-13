


# Chap 03

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/vbat
make -j 4 flash

 ➜  vbat git:(master) make 
There are unsatisfied feature requirements: periph_vbat
/home/labs/github/RIOT-OS/RIOT/tests/periph/vbat/../../../Makefile.include:1026: *** You can let the build continue on expected errors by setting CONTINUE_ON_EXPECTED_ERRORS=1 to the command line. Arrêt.

```
Pétites coquilles 

> parallèle au lieu de parellele
> offre des mécanismes 

Les threads permettent de réaliser plusieurs tâches en parellele par le programme. 
RIOT offre de mécanismes de barrière de concurrence entre les threads (mutex par exemple) et des moyens de communication par message.


# Tension de l'alimentation

> Problème de compilation 

```
cd ~/github/RIOT-OS/RIOT/tests/periph/vbat
make -j 4 flash

There are unsatisfied feature requirements: periph_vbat
/home/labs/github/RIOT-OS/RIOT/tests/periph/vbat/../../../Makefile.include:1026: *** You can let the build continue on expected errors by setting CONTINUE_ON_EXPECTED_ERRORS=1 to the command line. Arrêt.

```


# Chap 04


LED/DEL

 > Impossible d'avoir accès à la console après avoir flashé la carte

Normal ? 


External I/O

Capteur analogique de luminosité

> Je n'arrive pas à éblouir la LED avec la lumière de téléphone le pourcentage n'augmente pas.



# Chap 05 

Accéléromêtre

> Impossible de prendre la console


# Chap 06 

> Reboot and kernel panic.

Cause : 

Dans la fonction 
```c
 int init_sx1272_cmd(int argc, char **argv)
{
        //removed for simplicity


	    if (netdev->driver->init(netdev) < 0) {
	        puts("Failed to initialize SX127x device, exiting");
	        return 1;
	    }

	    netdev->event_callback = _event_cb; /// must be called before init

        //removed for simplicity
}

```

Car appélé ici: 

```c
// in source file sx127x_netdev.c

static int _init(netdev_t *netdev)
{
    // remove code for simplicity ...


    /* signal link UP */
   netdev->event_callback(netdev, NETDEV_EVENT_LINK_UP); // event_callback is NULL here, not initialized

   return 0;
}
```

# Chap 07
Dans la console ChirpStack (https://lns.campusiot.imag.fr/#/organizations/47/device-profiles): 
> OTAA_CLASS_A_TEXT n'est pas défini dans Device-profiles


# Chap 11 

TensorFlow Lite Micro 

> compilation failed with rom overflow

```bash

/usr/lib/gcc/arm-none-eabi/13.2.0/../../../../arm-none-eabi/bin/ld: /home/labs/github/RIOT-OS/RIOT/tests/pkg/tflite-micro/bin/wyres-base/tests_tflite-micro.elf section `.ARM.exidx' will not fit in region `rom'
/usr/lib/gcc/arm-none-eabi/13.2.0/../../../../arm-none-eabi/bin/ld: region `rom' overflowed by 1288 bytes
collect2: error: ld returned 1 exit status
make: *** [/home/labs/github/RIOT-OS/RIOT/tests/pkg/tflite-micro/../../../Makefile.include:751: /home/labs/github/RIOT-OS/RIOT/tests/pkg/tflite-micro/bin/wyres-base/tests_tflite-micro.elf] Error 1

```


