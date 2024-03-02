
# Chap 01 


> à prendre en main au lieu de à prendre en moins

Cependant, dans le cadre de ce tutoriel, Visual Code Studio sera plus facile et rapide à prendre en moin. 







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


> je mets en gras ce qui cloche

La commande ps du Shell permet de lister les threads **courantes** dans le programme. 
main correspond à la fonction main() qui exécute le Shell et isr_stack 
correspond à la thread qui exécute les traitants des interuptions, timers ... 
Il faut **fréquent** ajuster la taille de la pile de isr_stack avec 
CFLAGS += -DISR_STACKSIZE=2048 par exemple. Idem pour main avec THREAD_STACKSIZE_MAIN.

> On peur re-écrire comme ça ? 
La commande ps du Shell permet de lister les threads actives dans le programme. 
main correspond à la fonction main() qui exécute le Shell, et isr_stack correspond 
au thread qui gère les traitements des interruptions, timers, etc. 
Il est souvent nécessaire d'ajuster la taille de la pile de isr_stack avec 
CFLAGS += -DISR_STACKSIZE=2048, par exemple. 
De même pour main, cela se fait avec THREAD_STACKSIZE_MAIN.

> en gras ce qui manque

L'EEPROM est une (petite) mémoire persistante qui est en général utilisé pour des paramêtres de personnalisation ou de configuration de l'équipement.



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


External I/O , lien mort :  [LIS2DE12](https://github.com/RIOT-OS/RIOT/tree/master/tests/driver_lis2dh12)


Capteur analogique de luminosité

> Je n'arrive pas à éblouir la LED avec la lumière de téléphone le pourcentage n'augmente pas.


Module GNSS

> pétite coquille, en gras ce qui cloche, il faut mettre interface.


Cependant, comme la carte Wyres ne possède qu'une seule **inerface** 


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



# Chapitre 8A 

> Il faut rajouter l'etape de la construction de l'image nodered
```
docker compose build nodered

```
> Car sinon le pull échoue

```

➜  backend git:(main) ✗ docker compose pull
[+] Pulling 4/4
 ✔ grafana Pulled                                                        1.2s 
 ✔ thingsboard Pulled                                                    1.2s 
 ! nodered Warning                                                       1.4s 
 ✔ influxdb Pulled                                                       1.2s 
WARNING: Some service image(s) must be built from source by running:
    docker compose build nodered
1 error occurred:
	* Error response from daemon: pull access denied for iot-dashboard/nodered, repository does not exist or may require 'docker login': denied: requested access to the resource is denied


```
# Chap 10 

Hachage

> Compilation echouée

```bash
cd ~/github/RIOT-OS/RIOT/tests/unittests/tests-hashes
make -j 4 flash


Makefile:1: /Makefile.base: Aucun fichier ou dossier de ce nom
make: *** Aucune règle pour fabriquer la cible « /Makefile.base ». Arrêt

```



# Chap 11 

TensorFlow Lite Micro 

> compilation failed with rom overflow

```bash

/usr/lib/gcc/arm-none-eabi/13.2.0/../../../../arm-none-eabi/bin/ld: /home/labs/github/RIOT-OS/RIOT/tests/pkg/tflite-micro/bin/wyres-base/tests_tflite-micro.elf section `.ARM.exidx' will not fit in region `rom'
/usr/lib/gcc/arm-none-eabi/13.2.0/../../../../arm-none-eabi/bin/ld: region `rom' overflowed by 1288 bytes
collect2: error: ld returned 1 exit status
make: *** [/home/labs/github/RIOT-OS/RIOT/tests/pkg/tflite-micro/../../../Makefile.include:751: /home/labs/github/RIOT-OS/RIOT/tests/pkg/tflite-micro/bin/wyres-base/tests_tflite-micro.elf] Error 1

```


