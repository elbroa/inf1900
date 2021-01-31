/// Implémentation de la classe PorteLed
/// \file PorteLed.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "PorteLed.h"

const uint8_t NB_DEL = 8;

/// Crée le constructeur par défaut de la classe PorteLed.
PorteLed::PorteLed()
{
    porteA = ouverte;
    porteB = ouverte;
    porteC = ouverte;
    porteD = ouverte;
}

/// Change l'état de la porte led sélectionnée.
/// \param porte    La porte led dont l'état doit être changé.
/// \param etat     L'état choisi (ouverte ou fermée).
void PorteLed::changerEtatPorte(char porte, EtatPorte etat)
{
    switch (porte)
    {
    case 'A':
        if (etat != porteA)
        {
            porteA = etat;
            for (uint8_t i = 0; i < NB_DEL; i++)
            {
                PORTA |= (1 << PORTA4);
                afficherPorte(porteD);
                afficherPorte(porteC);
                afficherPorte(porteB);
                afficherPorteModifiee(porteA, i);
                PORTA &= (0 << PORTA4);
                _delay_ms(125);
            }
        }
        break;
    case 'B':
        if (etat != porteB)
        {
            porteB = etat;
            for (uint8_t i = 0; i < NB_DEL; i++)
            {
                PORTA |= (1 << PORTA4);
                afficherPorte(porteD);
                afficherPorte(porteC);
                afficherPorteModifiee(porteB, i);
                afficherPorte(porteA);
                PORTA &= (0 << PORTA4);
                _delay_ms(125);
            }
        }
        break;
    case 'C':
        if (etat != porteC)
        {
            porteC = etat;
            for (uint8_t i = 0; i < NB_DEL; i++)
            {
                PORTA |= (1 << PORTA4);
                afficherPorte(porteD);
                afficherPorteModifiee(porteC, i);
                afficherPorte(porteB);
                afficherPorte(porteA);
                PORTA &= (0 << PORTA4);
                _delay_ms(125);
            }
        }
        break;
    case 'D':
        if (etat != porteD)
        {
            porteD = etat;
            for (uint8_t i = 0; i < NB_DEL; i++)
            {
                PORTA |= (1 << PORTA4);
                afficherPorteModifiee(porteD, i);
                afficherPorte(porteC);
                afficherPorte(porteB);
                afficherPorte(porteA);
                PORTA &= (0 << PORTA4);
                _delay_ms(125);
            }
        }
        break;
    }
}

/// Affiche la porte selon l'etat.
/// \param etat     L'etat dans lequel la porte doit être mise.
void PorteLed::afficherPorte(uint8_t etat)
{
    for (uint8_t i = 0; i < NB_DEL; ++i)
    {
        PORTA |= (1 << PORTA3);
        PORTA |= (etat << PORTA2);
        PORTA |= (1 << PORTA0);
        _delay_ms(0.5);
        PORTA &= (0 << PORTA0) | (1 << PORTA3) | (1 << PORTA4);
    }
    _delay_ms(0.5);
    PORTA |= (1 << PORTA1);
    _delay_ms(0.5);
    PORTA &= (0 << PORTA1) | (1 << PORTA3) | (1 << PORTA4);
}

/// Affiche la porte qui a été modifiée.
/// \param etat     L'etat de la porte.
/// \param indice   L'indice correspondant la del.
void PorteLed::afficherPorteModifiee(EtatPorte etat, uint8_t indice)
{
    for (uint8_t i = 0; i < NB_DEL; i++)
    {
        if (etat == ouverte)
        {
            if (i <= indice)
            {
                PORTA |= (0 << PORTA2) | (1 << PORTA3) | (1 << PORTA4);
            }
            else
            {
                PORTA |= (1 << PORTA2) | (1 << PORTA3) | (1 << PORTA4);
            }
        }
        else
        {
            uint8_t indiceMax = 7;
            int8_t convNbNeg = -1;
            if (i < (convNbNeg * (indice - indiceMax)))
            {
                PORTA |= (0 << PORTA2) | (1 << PORTA3) | (1 << PORTA4);
            }
            else
            {
                PORTA |= (1 << PORTA2) | (1 << PORTA3) | (1 << PORTA4);
            }
        }
        PORTA |= (1 << PORTA0);
        _delay_ms(0.5);
        PORTA &= (0 << PORTA0) | (1 << PORTA3) | (1 << PORTA4);
    }
    _delay_ms(0.5);
    PORTA |= (1 << PORTA1);
    _delay_ms(0.5);
    PORTA &= (0 << PORTA1) | (1 << PORTA3) | (1 << PORTA4);
}