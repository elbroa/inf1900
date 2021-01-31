/// Implémentation du servomoteur
/// \file Servomoteur.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "Servomoteur.h"
#include "math.h"

/// Calcul le delai selon l'angle donné.
/// \param angle    L'angle donné.
/// \return         Le delai selon la fréquence de l'horloge et le prescaler choisi.
uint8_t calculerDelai(uint8_t angle)
{
    float angleMax = 180.0;
    uint16_t secEnMs = 1000;
    uint32_t freqHorloge = 8000000;
    uint16_t prescaler = 1024;

    float delai = ((angle / angleMax) + 1) / secEnMs;
    return floor(freqHorloge * delai / prescaler);
}

/// Effectue le PWM du servomoteur E.
/// \param delaiE   Le delai pour le servomoteur E.  
void servomoteurPWME(uint8_t delaiE)
{
    OCR2A = delaiE;

    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
}

/// Effectue le PWM du servomoteur F.
/// \param delaiF   Le delai pour le servomoteur F.
void servomoteurPWMF(uint8_t delaiF)
{
    OCR2B = delaiF;

    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
}