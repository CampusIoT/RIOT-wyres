# Communications LoRa

[Précédent](06.md) | [Sommaire](README.md) |  [Suivant](07.md)

Dans ce chapitre, vous apprendrez à implémenter un protocole minimaliste pour l'échange de messages LoRa au travers d'un réseau maillé multi-sauts.

## Rappel

> Configurez la carte cible pour `make`
```bash
export BOARD=wyres-base
export EXTERNAL_BOARD_DIRS=~/github/campusiot/RIOT-wyres/boards
```

Recherchez le  `tty` de la console et connectez-vous à celle-ci avec `tio`.
Sur Linux
```bash
lsusb
tio
tio -b 115200 -m INLCRNL /dev/ttyUSB0
```

Sur MacOS
```bash
lsusb
tio
tio -L
tio -b 115200 -m INLCRNL /dev/tty.usbserial-XXXX
```

> Pour mémoire, si vous utilisez Linux dans une machine virtuelle VirtualBox, il faut monter les 2 périphériques USBSerial et STLink dans le menu Péripériques de la machine virutelle.

## Les réseaux maillés multi-sauts

Un [réseau maillé multi-sauts](https://fr.wikipedia.org/wiki/R%C3%A9seau_maill%C3%A9) (*multi-hop mesh network*) est une architecture réseau décentralisée où les données peuvent passer d’un appareil (nœud) à un autre sur plusieurs étapes successives pour atteindre leur destination. Il n'y a pas de noeud central. Le réseau s'organise en fonction de l'apparision et la disparition des noeuds dans le réseau (panne, mobilité ...). Deux exemples de réseaux maillés multi-sauts utilisant des liaisons avec la modulation LoRa CSS sont Meshtastic et Meshcore.


## LoRaMesh₍ᐢ֎ﻌ֍ᐢ₎ʃ  (LoRaMeshChat)

Etendez le programme précédent LoRa₍ᐢ֎ﻌ֍ᐢ₎ʃ (LoRaChat) pour élaborer un chat ₍ᐢ֎ﻌ֍ᐢ₎ʃ en LoRa maillé multi-sauts par innodation controlée.

Pour cela, vous ajouterez un champs supplémentaire `ttl` (*Time to Live*) qui donne le nombre de sauts restants à relayer par le noeud récepteur.

`123@*:18,3:Salut à tous en multi-sauts (3 restants)`: signifie de la part de 123 pour tout le monde (*) (message #18 émis par 123 avec un `ttl` de 3)

L'algorithme d'accheminement des messages dans votre réseau maillé qui s'inspire de celui de Meshtastic, est le suivant: 

A la réception, un noeud attends `RelayDelay` millisecondes avant de répeter un message. La valeur de `RelayDelay` depends du SF, de la BW, du Preamble et du SNR de la réception. Le principe est le suivant : plus le SNR est haut, moins le noeud est prioritaire pour répéter un message. Notez que le `SF`, la `BW` et le `Preamble` définissent le débit de `DataRate` choisi par les noeuds.

Le `ttl` du message est décrémenté avant d'être relayé.

Les messages sans `ttl` ne sont pas relayés pour rester compatible avec LoRa₍ᐢ֎ﻌ֍ᐢ₎ʃ sans multi-saut.

Un noeud décide de ne pas répeter le message recu si le SNR de la première réception et des répétitions recues depasse le seuil `SNRThreshold`.

Ajoutez des commandes Shell au programme
* pour ajuster le seuil `SNRThreshold`.
* pour lister les derniers messages reçus (relayés, non rélayés, en cours de relai (aka *pending*)) en gérant une file FIFO de taille fixe. En cas de débordement de la file, les messages à relayer ne sont pas ajoutés à la file FIFO.

> Pensez à conserver les messages qui ont été émis, recus ou transistés par le noeud (dans une FIFO pendant un "certain" temps) afin d'éviter de les réémettre inutilement et d'éviter un phénoméne de bouclage. Un simple CRC du message (exluant le `ttl`) est suffisant. Vous pourrez utiliser les [fonctions utilitaires fournies par RIOT](https://github.com/RIOT-OS/RIOT/tree/master/sys/checksum).

> Conservez le numéro de séquence du dernier message provenant d'un noeud pour éviter d'afficher ou de retransmettre 

> Le SNR est récupéré dans la structure [`netdev_lora_rx_info_t`](https://github.com/RIOT-OS/RIOT/blob/master/drivers/include/net/netdev/lora.h) retournée par le driver lors de la réception ([fonction `_event_cb`](https://github.com/RIOT-OS/RIOT/blob/master/tests/drivers/sx127x/main.c))


## Autres types de messages

Vous pouvez améliorer votre protocole en ajoutant :
* un message `neighbour` qui contient la liste de la qualité du signal avec les "derniers" voisins directs (ie zero-hop).
* un message `traceroute` entre un émetteur et un destinataire qui enregistre la liste des noeuds ayant relayé le message à l'aller et au retour.

## Binarisation des messages LoRa₍ᐢ֎ﻌ֍ᐢ₎ʃ (LoRaChat)

Transformez le programme pour échanger plus efficacement les messages en format binaire compact plutôt qu'en format ASCII.

Définissez en groupe une [structure commune](../modules/minimesh) pour les messages LoRa échangés dans votre réseau maillé minimaliste.

> Pensez à ajouter un type de message (advert, text, text_unishox2, image_aeic_se, lpp, raw, ping, traceroute, neighbour, ...) (1 octet), le nombre de hops, un id d'émetteur (2 octets), un id de destinataire (2 octets) ou un hash de salon (2 octets), un timestamp (4 octets), la charge utile, et de terminer par un CMAC signé par une PSK AES128 (DH ou salon)

> NB: Meshtastic utilise le package [`nanopb`](https://github.com/RIOT-OS/RIOT/tree/master/tests/pkg/nanopb) pour encoder et pour décoder les messages au format Protobuf.


## Echanges de messages texte compressés sur LoRaMesh₍ᐢ֎ﻌ֍ᐢ₎ʃ

[Unishox2](https://github.com/siara-cc/Unishox2) est une bibliothèque de compression de chaines de caractères Unicode. Elle permet de diminuer le poids des massages par deux. Ajoutez la [bibliothèque Arduino](https://github.com/siara-cc/Unishox2/tree/master/Arduino) à votre programme pour échanger des messages textes compressés (type `text_unishox2`).

## Echanges d'images fortement compressées sur LoRaMesh₍ᐢ֎ﻌ֍ᐢ₎ʃ

Transformez le programme pour échanger des messages transportant des images compressés au moyen du codec [AEIC-SE 512](https://huggingface.co/zjs81/aeic-se-onnx) (Asymmetric Extreme Image Codec - Shallow Encoder) ([article](https://arxiv.org/html/2512.12229v2)). Ce codec permet de transfert d'une image couleur 512x512 pixels via un message d'une centaine d'octets sur des réseaux LPWAN terrestres ou non-terrestres (LoRaWAN, LoRa mesh, Mioty, Kineis ...). Le [codec](https://github.com/LuizScarlet/AEIC) est exécuté sur votre machine hôte.

![](images/chien_de_protection_512.jpg) ![](images/chien_de_protection_512ai.jpg)

