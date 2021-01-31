/*
*Programme permettant de faire changer une DEL de couleur selon la proximité de l'ampoule avec la photorésistance. 
Si la lumière est basse sur la photorésistance, la DEL prendra la couleur verte.
Si la lumière est à un bon niveau, la DEL sera ambrée.
Si la lumière est trop forte, la DEL sera rouge.
*
*Nom du fichier : main.cpp
*Section : 01
*Equipe : 08
*Auteurs : Jeremy Perreault (1903274), Eloise Brosseau (2011037) et Douaa Bergheul (2006583)
*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include "can.h"

const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;
const uint8_t ETEINT = 0x00;

// Émets une lumière ambrée sur la DEL branchée sur le Port B.
void Ambree()
{
    PORTB = ROUGE;
    _delay_ms(10);
    PORTB = VERT;
    _delay_ms(10);
}

int main()
{
    // Objet de type "can" permettant de lire l'intensité de la lumière reçue par la
    // photorésistance'
    can capteur;

    DDRA = 0x00; //Port A en entrée
    DDRB = 0xff; //Port B en sortie

    while (true)
    {
        // Convertion de la valeur analogique à numérique sur la broche A0.
        uint8_t mesureIntensite = capteur.lecture(0) >> 2;

        // Les valeurs inscrites ci-dessous proviennent de mesures effectuées directement sur
        // le circuit.

        // L'intervalle qui permet d'obtenir la couleur verte pour une résistance comprise entre
        // 9 kiloohms et 11 kiloohms.
        if (mesureIntensite >= 0 && mesureIntensite <= 133)
        {
            PORTB = VERT;
        }
        // L'intervalle qui permet d'obtenir la couleur verte pour une résistance comprise entre
        // 4 kiloohms et 6 kiloohms.
        else if (mesureIntensite >= 160 && mesureIntensite <= 255)
        {
            PORTB = ROUGE;
        }
        // L'intervalle qui permet d'obtenir la couleur verte pour une résistance comprise entre
        // 7 kiloohms et 8 kiloohms.
        else
        {
            Ambree();
        }
    }
}