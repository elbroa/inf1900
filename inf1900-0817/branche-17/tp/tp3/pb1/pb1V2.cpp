/*
* Nom: pb1.cpp
* Description eteindre un del de faç progressive.
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


//Diminue l'intensite de la del jusqu'a l'etiendre de la couleur Rouge
void diminutionIntensiteRouge(){
    for(int i = 0; i < 3001 ;i++){
        //Del a 100
        if(i < 500){
            PORTA = (1<<PORTA0);
            _delay_ms (1);
        } //Del a 90
        else if(i < 1000){
            PORTA = (1<<PORTA0);
            _delay_ms (0.9);
            PORTA = (0<<PORTA0);
            _delay_ms (0.1);
        }//Del a 70
        else if(i < 1500){
            PORTA = (1<<PORTA0);
            _delay_ms (0.7);
            PORTA = (0<<PORTA0);
            _delay_ms (0.3);
        }//Del a 50
        else if(i < 2000){
            PORTA = (1<<PORTA0);
            _delay_ms (0.5);
            PORTA = (0<<PORTA0);
            _delay_ms (0.5);
        }//Del a 30
        else if(i < 2500){
            PORTA = (1<<PORTA0);
            _delay_ms (0.3);
            PORTA = (0<<PORTA0);
            _delay_ms (0.7);
        }//Del a 10
        else{
            PORTA = (1<<PORTA0);
            _delay_ms (0.1);
            PORTA = (0<<PORTA0);
            _delay_ms (0.9);
        }
    }
}
//Diminue l'intensite de la del jusqu'a l'etiendre de la couleur Vert
void diminutionIntensiteVert(){
    for(int i = 0; i < 3001 ;i++){
        //Del a 100
        if(i < 500){
            PORTA = (1<<PORTA1);
            _delay_ms (1);
        } //Del a 90
        else if(i < 1000){
            PORTA = (1<<PORTA1);
            _delay_ms (0.9);
            PORTA = (0<<PORTA1);
            _delay_ms (0.1);
        }//Del a 70
        else if(i < 1500){
            PORTA = (1<<PORTA1);
            _delay_ms (0.7);
            PORTA = (0<<PORTA1);
            _delay_ms (0.3);
        }//Del a 50
        else if(i < 2000){
            PORTA = (1<<PORTA1);
            _delay_ms (0.5);
            PORTA = (0<<PORTA1);
            _delay_ms (0.5);
        }//Del a 30
        else if(i < 2500){
            PORTA = (1<<PORTA1);
            _delay_ms (0.3);
            PORTA = (0<<PORTA1);
            _delay_ms (0.7);
        }//Del a 10
        else{
            PORTA = (1<<PORTA1);
            _delay_ms (0.1);
            PORTA = (0<<PORTA1);
            _delay_ms (0.9);
        }
    }
}


int main(){
    DDRA = 0xff; //définie port A comme une sotie.
       
    
    uint8_t compteur = 0;

    for(;;){
        compteur++;
        PORTA = compteur;
        diminutionIntensiteRouge();
        compteur++;
        PORTA = compteur;
        diminutionIntensiteVert();
        compteur = compteur + 2; 
    }
    
}