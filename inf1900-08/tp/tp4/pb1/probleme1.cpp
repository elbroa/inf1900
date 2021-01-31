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
 *Tableau des etats
 *
 *Etat present    D2    Etat suivant    Sortie DEL
 *INIT            0        INIT          Eteinte
 *INIT            1         EA           Eteinte
 *EA              0         EA           Vert
 *EA              1         EB           Vert
 *EB              0         EB           Rouge
 *EB              1        INIT          Rouge
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t ETEINT = 0x00;

volatile uint8_t etat = 0;

Etat = {INIT, EA, EB};
Etat etat = INIT;

// placer le bon type de signal d'interruption

// à prendre en charge en argument
ISR(INT0_vect)
{
    // laisser un delai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms(30);

    switch (etat)
    {
        case INIT:
            etat = EA;
            break;

        case EA:
            etat = EB;
            break;

        case EB:
            etat = INIT;
            break;
    }

    // se souvenir ici si le bouton est pressé ou relâché

    // changements d'états tels que ceux de la

    // semaine précédente

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0);
}

void initialisation(void)
{
    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontroleur n'est pas prêt...

    cli();

    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables

    DDRA = 0xff;
    DDRD = 0x00;

    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC01) | (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.

    sei();
}

int main()
{
    initialisation();
    while (true)
    {
        switch (etat)
        {
        case INIT:
            PORTA = ETEIN;
            break;
        case EA:
            PORTA = VERT;
            break;
        case EB:
            PORTA = ROUGE;
            break;
        }
    }

    return 0;
}
