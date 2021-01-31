/*
* Nom: pb2.cpp
* Description: objectif faire tourner une roue a une fréquence
*              de 60 hz pendant 10 avec des puissance differente
*              et par la suite même concepte mais un fréquence de 400Hz
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

void setPORTB(int direction, int enable){
    PORTB = (direction<<PORTB1) | (enable<<PORTB0);
}

//Roue qui tourne a 60Hz
void tourne60(int direction){
    //i < 601 pour quel tourne 10s, 10s * 60Hz = 600
    for(int i = 0; i < 601; i++){
        //Tourne a zero
        if(i < 120){
            setPORTB(direction, 0);
            _delay_us (16666);
        }//tourne a 25
        else if(i < 240){
            setPORTB(direction, 1);
            _delay_us (4166);
            setPORTB(direction, 0);
            _delay_us (12500);
        }//tourne a 50
        else if(i < 360){
            setPORTB(direction, 1);
            _delay_us (8333);
            setPORTB(direction, 0);
            _delay_us (8333);
        }//tourne 75
        else if(i < 480){
            setPORTB(direction, 1);
            _delay_us (12500);
            setPORTB(direction, 0);
            _delay_us (4166);
        }//tourne a 100
        else{
            setPORTB(direction, 1);
            _delay_us (16666);
        }
    }
}

//Roue qui tourne a 400Hz
void tourne400(int direction){
    //i < 4001 pour quel tourne 10s, 10s * 400Hz = 4000
    for (int i = 0; i < 4001; i++){
        //tourne a 0
        if(i < 800){
            setPORTB(direction, 0);
            _delay_us (2500);
        }//tourne a 25
        else if(i < 1600){
            setPORTB(direction, 1);
            _delay_us (625);
            setPORTB(direction, 0);
            _delay_us (1875);
        }//Tourne a 50
        else if(i < 2400){
            setPORTB(direction, 1);
            _delay_us (1250);
            setPORTB(direction, 0);
            _delay_us (1250);
        }//Tourne a 75
        else if(i < 3200){
            setPORTB(direction, 1);
            _delay_us (1875);
            setPORTB(direction, 0);
            _delay_us (625);
        }//tourne a 100
        else{
            setPORTB(direction, 1);
            _delay_us (2500);
        }
    }
}

int main(){
    DDRB = 0xff; //definie port B comme une sortie.

    while(true){
        //Tourne dans le sens horaire dans notre circuit
        tourne60(0);
        tourne400(0);
        //Tourne dans le sens anti-horaire dans notre circuit
        tourne60(1);
        tourne400(1);
    }    
}