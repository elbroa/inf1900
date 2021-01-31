/*
*Programme permettant de controler une DEL qui est eteinte au depart. Si le bouton-poussoir sur D2 est appuyé, la DEL devient rouge.  
*Par contre, si le bouton-poussoir sur D3 est appuyé en premier, la DEL devient verte. Par la suite, lorsque le bouton-poussoir sur D2,
*est appuyé la DEL devient rouge. Une fois que la DEL est rouge, en appuyant sur le bouton-poussoir sur D3, la DEL devient verte. Ensuite,
*en appuyant sur le bouton-poussoir sur D3, la DEL s'éteint. Toutefois, en appuyant sur le bouton-poussoir sur D2, la DEL devient rouge.
*Si la DEL est rouge, lorsque le bouton-poussoir sur D2 est réappuyé, la DEL reprend la couleur verte précédente, ce qui permet de réappuyer
*sur le bouton-poussoir sur D3 pour éteindre la DEL afin de recommencer un cycle.
*Nom du fichier : probleme2.cpp
*Section : 01
*Equipe : 08
*Auteurs : Jeremy Perreault (1903274), Eloise Brosseau (2011037) et Douaa Bergheul (2006583)
*
*Tableau des etats
*
*Etat present    D2  D3  Etat suivant    Sortie DEL
*INIT            0   0   INIT            Eteinte
*INIT            0   1   EA              Eteinte
*INIT            1   0   EB              Eteinte
*EA              1   X   EB              Vert
*EB              X   1   EC              Rouge
*EC              0   1   INIT            Vert
*EC              1   0   ED              Vert
*ED              1   X   EC              Rouge             
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
                if(isD3Pressed() && !(isD2Pressed())){
                    etat = EA;
                }
                else if(isD2Pressed() && !(isD3Pressed())){
                    etat = EB;
                }
                    break;       

            case EA: PORTA = vert;
                    if(isD2Pressed()){
                        etat = EB;
                    }
                    break;

            case EB: PORTA = rouge;
                    if(isD3Pressed()){
                        etat = EC;
                    }
                    break;

            case EC: PORTA = vert;
                    if(isD3Pressed() && !(isD2Pressed())){
                        etat = INIT;
                    }
                    else if(isD2Pressed() && !(isD3Pressed())){
                        etat = ED;
                    }
                    break;

            case ED: PORTA = rouge;
                    if(isD2Pressed()){
                    etat = EC;
                    }
                    break;
        }
    }
return 0;
}

