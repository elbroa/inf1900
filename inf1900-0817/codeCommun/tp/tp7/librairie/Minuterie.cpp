#include "Minuterie.h"

void partirMinuterie(uint16_t duree)
{
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    //initialisation du timer a zero
    TCNT1 = 0;

    OCR1A = duree;
    //on le met egal a zero etant donner que nous ne prenons pas
    //valeur provenant des PORT pour l'instant
    TCCR1A = 0;
    //set mode to 1024(divise le clock par 1024)
    // on veut modifier CS12 et CS10
    //Registre a 8 bit
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;
    //set flags interrupt timer
    //on veut que le timer arrète quand il arrive a sa fin
    //ou lorsque nous somme arrivée a OCR1A donc on veut les deux
    //OCIE1A Fait une intéruption lorsque OCR1A = TCNT1
    //TOIE1 en cas d'overflow fait une intéruption
    TIMSK1 = (1 << OCIE1A) | (1 << TOIE1);
}