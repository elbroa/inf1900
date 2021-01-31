/// Implémentation de l'horloge
/// \file Horloge.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "Horloge.h"
#include "can.h"
#include "Debug.h"

/// Remet l'horloge à 00:00.
void remiseHorlogeZero()
{
    PORTD = (1 << PORTD0);
    _delay_ms(1000);
    PORTD = (0 << PORTD0);
}

/// Change l'affichage de l'horloge selon une heure et des minutes donnés.
/// \param heure    L'heure
/// \param minute   Les minutes
void changerHeureHorloge(uint8_t heure, uint8_t minute)
{
    remiseHorlogeZero();
    uint8_t nbMinutes = 60;
    
    for (uint8_t i = 0; i < heure; i++)
    {
        for (uint8_t j = 0; j < nbMinutes; j++)
        {
            PORTD = (0 << PORTD5);
            _delay_ms(0.5);
            PORTD = (1 << PORTD5);
        }
    }

    for (uint8_t i = 0; i < minute; i++)
    {
        PORTD = (0 << PORTD5);
        _delay_ms(0.5);
        PORTD = (1 << PORTD5);
    }
    PORTD = (0 << PORTD5);
}
