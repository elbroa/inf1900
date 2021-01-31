/// Horloge
/// \file Horloge.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include <avr/io.h>
#include <util/delay.h>

#ifndef HORLOGE_H
#define HORLOGE_H

void remiseHorlogeZero();
void changerHeureHorloge(uint8_t heure, uint8_t minute);

#endif
