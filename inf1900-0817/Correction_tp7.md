# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
  Travail    : Mise en commun du code et formation de librairies
  Section #  : 1
  Équipe #   : 0817
  Correcteur : Tristan Rioux

# Code:
– La qualités et le choix de vos portions de code choisies   (4.1/5)
– La qualités de vos modifications aux Makefiles             (4.5/5)

# Le rapport:
– Explications cohérentes par rapport au code retenu
  pour former la librairie                                   (1.5/2)
– Explications cohérentes par rapport aux Makefiles modifiés (2.0/2)
– Explications claires avec un bon niveau de détails         (1.8/2)
– Bon français                                               (1/1)

# Généralités:
– Bonne soumission de l'ensemble du code (compilation sans
  erreurs, …) et du rapport selon le format demandé          (1.5/3)

__Total des points: 16.4/20__

# Commentaires du correcteur:
Bonjour,

Voici les endroits où j'ai enlevé des points:
- Duplication de code dans `isPressedD2` et `isPressedD3`;
- On ne peut pas recevoir avec le USART;
- Peu de code dans la librairie, mais tout de même efficace;
- Lignes inutiles non retirées dans les makefiles;
- On parle de classe dans le rapport, mais il n'y en a aucune;
- Ne mentionne pas que `partirMinuterie` doit appeler `sei()` et avoir les fonctions `ISR` définit;
- Mauvaise emplacement des fichiers de remise;
- Pas de fichier `.simu`.


# Basé sur le commit suivant
```
commit 78987474fda824fce65901fa154106e0e251bf64
Author: Douâa Bergheul <Vous@exemple.com>
Date:   Tue Nov 3 10:16:11 2020 -0500

    TP7 et son rapport corrigés.
```

# Fichiers indésirables
```
branche-08/tp/tp1/pb1/compteur32bits.o
branche-08/tp/tp1/pb1/test32bits.hex
branche-17/tp/tp1/tp1environnement/compteur32bits.o
```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans codeCommun/tp7/librairie =============================
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Minuterie.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Bouton.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c PWM.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c UART.cpp
avr-ar  -crs  -o libCommune.a  Minuterie.o Bouton.o PWM.o UART.o

======================= Sortie de make dans codeCommun/tp7/projet =============================
avr-gcc -I. -I/usr/include/simavr  -MMD -I ../librairie -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
avr-gcc -Wl,-Map,test.elf.map -mmcu=atmega324pa -o test.elf  main.o \
-lm -l Commune -L ../librairie 
avr-objcopy -j .text -j .data \
	-O ihex test.elf test.hex

```
