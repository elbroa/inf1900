/*
*Programme permettant de controler une DEL qui est eteinte au depart, qui devient vert apres que le bouton-poussoir
*sur D3 ait été appuyé et relaché, qui devient rouge pendant une seconde apres avoir appuyé sur le bouton-poussoir sur D2 trois
fois et qui redevient eteinte pour commencer un nouveau cycle.
*
*Nom du fichier : probleme1.cpp
*Section : 01
*Equipe : 08
*Auteurs : Jeremy Perreault (1903274), Eloise Brosseau (2011037) et Douaa Bergheul (2006583)
*
*Tableau des etats
*
*Etat present    D2  D3  Etat suivant    Sortie DEL
*INIT            X   0   INIT            Eteinte
*INIT            X   1   EA              Eteinte
*EA              0   X   EA              Vert
*EA              1   X   EB              Vert
*EB              0   X   EB              Vert
*EB              1   X   EC              Vert
*EC              0   X   EC              Vert
*EC              1   X   ED              Vert
*ED              X   X   INIT            Rouge
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

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

    while(true){
        switch(etat){
            case INIT: PORTA = eteint;
                    if(isD3Pressed()){
                    etat = EA;
                    }
                    break;       

            case EA: PORTA = vert;
                    if(isD2Pressed()){
                        etat = EB;
                    }
                    break;

            case EB: PORTA = vert;
                    if(isD2Pressed()){
                        etat = EC;
                    }
                    break;

            case EC: PORTA = vert;
                    if(isD2Pressed()){
                        etat = ED;
                    }
                    break;

            case ED: PORTA = rouge;
                    _delay_ms(1000);
                    etat = INIT;
                    break;
        }
    }
return 0;
}

