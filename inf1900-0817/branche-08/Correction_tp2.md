v# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 1
+ Équipe #   : 08
+ Correcteur : Sami Sadfa

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0/0.5)     |
| Noms de variables décrivent l'intention      | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.0/1.5)__ |

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme ou procédure 
 + peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Indentation   

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Indentation structurée                       |            |
| Indentation uniforme dans le programme       |            |
| __Résultat partiel__                         | __(1.0/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Bonne application des concepts de systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation des registres appropriée         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisés    |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4.0/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (1.5/1.5)     |
| Absence de fichiers inutiles                 | (1.5/1.5)     |
| __Résultat partiel__                         | __(3.0/3.0)__ |


## Compilation    

| Pénalité par erreur                          | -2.0       |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation |            |
| Absence de messages d'attention (*warning*)  |            |
| __Résultat partiel__                         | __(2.0/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (2.5/2.5)     |
| Cas limites observables                      | (2.5/2.5)     |
| __Résultat partiel__                         | __(5.0/5.0)__ |

# Résultat

__Total des points: 19.5/20__

# Commentaires du correcteur:

- chiffre magique 1000 ligne 97 pb1
- isD3Pressed devrait avoir l'air de : if(pressed){while(pressed); return true;} else{return false;}

# Basé sur le commit suivant
```
commit cb46bf30facb7404444b91b860d39226094bb297
Author: elbroa <eloise.brosseau@polymtl.ca>
Date:   Wed Sep 16 09:11:06 2020 -0400

    ajout du simulateur
```

# Fichiers indésirables
```

```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans tp/tp6/pb1 =============================
make: *** correction_tp2/08/tp/tp6/pb1: No such file or directory.  Stop.

======================= Sortie de make dans tp/tp6/pb2 =============================
make: *** correction_tp2/08/tp/tp6/pb2: No such file or directory.  Stop.


```
