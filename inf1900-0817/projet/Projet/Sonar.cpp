/// Implémentation du sonar
/// \file Sonar.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include <util/delay.h>

#include <avr/io.h>
#include "Sonar.h"
#include "Debug.h"

/// Srcute la valeur du sonar.
/// \return     Un bool qui représente si
bool scruterSonar()
{
    uint16_t compteurUS = 0;

    PORTD = 1 << PORTD1;
    _delay_ms(0.01);
    PORTD = 0 << PORTD1;

    while (!(PIND & (1 << PIND2)))
    {
    }

    while (PIND & (1 << PIND2))
    {
        _delay_ms(0.1);
        compteurUS++;
    }

    //Délai suite à la lecture
    _delay_ms(10);

    uint8_t convEnM = 58;
    float distance = compteurUS / convEnM;
    uint8_t distanceMax = 2;

    if (distance < distanceMax)
    {
        return true;
    }

    return false;
}