/*
*  Nom: Controleur DEL
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main(){
    DDRA = 0xff; //définie port A comme une sotie.
       
    
    uint8_t compteur = 0;

    for(;;){
        compteur++;
        PORTA = compteur;
        _delay_ms (500);
        compteur++;
        PORTA = compteur;
        _delay_ms (500);
        compteur = compteur + 2; 
    }
    
}