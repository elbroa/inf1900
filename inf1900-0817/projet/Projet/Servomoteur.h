/// Servomoteur
/// \file Servomoteur.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include <avr/io.h>
#include <util/delay.h>

#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

uint8_t calculerDelai(uint8_t angle);
void servomoteurPWME(uint8_t delaiE);
void servomoteurPWMF(uint8_t delaiF);

#endif