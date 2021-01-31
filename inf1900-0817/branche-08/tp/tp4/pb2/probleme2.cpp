/*
 *Programme permettant de controler une DEL qui est eteinte au depart. Si le bouton-poussoir sur D2 est appuyé, la DEL devient rouge.
 *Par contre, si le bouton-poussoir sur D3 est appuyé en premier, la DEL devient verte. Par la suite, lorsque le bouton-poussoir sur D2,
 *est appuyé la DEL devient rouge. Une fois que la DEL est rouge, en appuyant sur le bouton-poussoir sur D3, la DEL devient verte. Ensuite,
 *en appuyant sur le bouton-poussoir sur D3, la DEL s'éteint. Toutefois, en appuyant sur le bouton-poussoir sur D2, la DEL devient rouge.
 *Si la DEL est rouge, lorsque le bouton-poussoir sur D2 est réappuyé, la DEL reprend la couleur verte précédente, ce qui permet de
 *réappuyer sur le bouton-poussoir sur D3 pour éteindre la DEL afin de recommencer un cycle. Nom du fichier : probleme1.cpp Section : 01
 *Equipe : 08
 *Auteurs : Jeremy Perreault (1903274), Eloise Brosseau (2011037) et Douaa Bergheul (2006583)
 *
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t ETEINT = 0x00;

volatile uint8_t minuterieExpiree = 0;
volatile uint8_t boutonPoussoir = 0;

volatile uint16_t duree = 7812;

ISR(TIMER1_COMPA_vect)
{
    minuterieExpiree = 1;
}

ISR(INT0_vect)
{
    _delay_ms(30);
    if (PIND & (1 << PIND2))
    {
        boutonPoussoir = 1;
    }
}

void partirMinuterie(uint16_t duree)
{
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = 0 << WGM10 | 0 << WGM11;
    TCCR1B = 1 << CS12 | 1 << CS10 | 0 << CS11 | 1 << WGM12 | 0 << WGM13;
    TCCR1C = 0;
    TIMSK1 = 1 << OCIE1A;
}

void initialisation(void)
{
    cli();
    DDRA = 0xff;
    DDRD = 0x00;

    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC01) | (1 << ISC00);

    sei();
}

int main()
{
    initialisation();

    _delay_ms(10000);

    PORTA = ROUGE;

    _delay_ms(100);

    PORTA = ETEINT;

    partirMinuterie(duree);
    
    while (minuterieExpiree == 0 && boutonPoussoir == 0);

    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.   

    cli();
    // Verifier la réponse
    if(minuterieExpiree == 0)
    {
        PORTA = VERT;
    }
    else
    {
        PORTA = ROUGE;
    }
    
    return 0;
}
