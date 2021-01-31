/// Clavier
/// \file Clavier.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include <avr/io.h>

#ifndef CLAVIER_H
#define CLAVIER_H

const uint8_t TOUCHE_ZERO = 1 << PORTC0;
const uint8_t TOUCHE_UN = (1 << PORTC1) | (1 << PORTC0);
const uint8_t TOUCHE_DEUX = (1 << PORTC2) | (1 << PORTC0);
const uint8_t TOUCHE_TROIS = (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC0);
const uint8_t TOUCHE_QUATRE = (1 << PORTC3) | (1 << PORTC0);
const uint8_t TOUCHE_CINQ = (1 << PORTC1) | (1 << PORTC3) | (1 << PORTC0);
const uint8_t TOUCHE_SIX = (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC0);
const uint8_t TOUCHE_SEPT = (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC0);
const uint8_t TOUCHE_HUIT = (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_NEUF = (1 << PORTC1) | (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_A = (1 << PORTC2) | (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_B = (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_C = (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_D = (1 << PORTC1) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_E = (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC0);
const uint8_t TOUCHE_F = (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC0);

const uint8_t clavier[4][4] = {{TOUCHE_ZERO, TOUCHE_UN, TOUCHE_DEUX, TOUCHE_TROIS},
                               {TOUCHE_QUATRE, TOUCHE_CINQ, TOUCHE_SIX, TOUCHE_SEPT},
                               {TOUCHE_HUIT, TOUCHE_NEUF, TOUCHE_A, TOUCHE_B},
                               {TOUCHE_C, TOUCHE_D, TOUCHE_E, TOUCHE_F}};

enum Etats
{
    init,
    option1,
    option2,
    option3,
    option4,
    option5,
    option6
};

uint8_t detecterTouche();
Etats definirEtat(uint8_t touche);
void afficherMessage(Etats etat);

#endif