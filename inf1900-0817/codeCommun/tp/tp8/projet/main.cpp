#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Debug.h"

/*************************************************************************//**
*  Déterminer si le bouton-poussoir sur D2 a été appuyé et relâché
*  \return  \c true si le bouton-poussoir a été appuyé et relaĉhé.
*/
bool isD2Pressed(){
    if((PIND & (1 << PIND2))){
        _delay_ms(10);
        if(!(PIND & (1 << PIND2))){
            _delay_ms(10);
            return (!(PIND & (1 << PIND2)));
        }
    }
    return false;
}

/*************************************************************************//**
*  Déterminer si le bouton-poussoir sur D3 a été appuyé et relâché
*  \return  \c true si le bouton-poussoir a été appuyé et relaĉhé.
*/
bool isD3Pressed(){
    if((PIND & (1 << PIND3))){
        _delay_ms(10);
        if(!(PIND & (1 << PIND3))){
            _delay_ms(10);
            return (!(PIND & (1 << PIND3)));
        }
    }
    return false;
}

int main(){
    DDRA = 0xff;
    DDRD = 0x00; 

    const uint8_t rouge = 0x01;
    const uint8_t vert = 0x02;
    const uint8_t eteint = 0x00;

    enum Etats {INIT, EA, EB, EC, ED};
    Etats etat = INIT;

    bool estPasEcrit = true;

    while(true){
        switch(etat){
            case INIT: PORTA = eteint;
                    if (estPasEcrit)
                    {
                        DEBUG_PRINT(("INFO: etat = init"));
                        estPasEcrit = false;
                    }
                    if(isD3Pressed()){
                    etat = EA;
                    estPasEcrit = true;
                    }
                    break;       

            case EA: PORTA = vert;
                    if (estPasEcrit)
                    {
                        DEBUG_PRINT(("INFO: etat = EA"));
                        estPasEcrit = false;
                    }
                    if(isD2Pressed()){
                        etat = EB;
                        estPasEcrit = true;
                    }
                    break;

            case EB: PORTA = vert;
                    if (estPasEcrit)
                    {
                        DEBUG_PRINT(("INFO: etat = EB"));
                        estPasEcrit = false;
                    }
                    if(isD2Pressed()){
                        etat = EC;
                        estPasEcrit = true;
                    }
                    break;

            case EC: PORTA = vert;
                    if (estPasEcrit)
                    {
                        DEBUG_PRINT(("INFO: etat = EC"));
                        estPasEcrit = false;
                    }
                    if(isD2Pressed()){
                        etat = ED;
                        estPasEcrit = true;
                    }
                    break;

            case ED: PORTA = rouge;
                    if (estPasEcrit)
                    {
                        DEBUG_PRINT(("INFO: etat = ED"));
                        estPasEcrit = false;
                    }
                    _delay_ms(1000);
                    etat = INIT;
                    estPasEcrit = true;
                    break;
        }
    }
return 0;
}