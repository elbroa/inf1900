
/**
 *  Description: objectif controler les moteur avec une minuterie
 *               Pour un pont en H
 **/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>


void ajustementPWM (uint8_t duree) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    OCR1A = duree;
    OCR1B = duree;

    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (1 << WGM10) ;
    //La division CSn2,1,0 Permet de change a frequence
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

int main()
{
    DDRD = 0xff;
    DDRB = 0xff;
    PORTB = (1 << PORTB0);
    while(true)
    {
        _delay_ms (2000);
        ajustementPWM(0x40);
        _delay_ms (2000);
        ajustementPWM(0x80);
        _delay_ms(2000);
        ajustementPWM(0xBF);
        _delay_ms(2000);
        ajustementPWM(0xFE);
        _delay_ms(2000);
    }
}