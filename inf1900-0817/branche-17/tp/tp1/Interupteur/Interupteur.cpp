/*
*  Nom: InterupteurDEL
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


bool verification(){
    if (PIND & 0x04){
        _delay_ms (10);
        return (PIND & 0x04);
    }
    return false;
}


int main(){
    DDRA = 0xff; //définie port A comme une sotie.
    DDRD = 0x00; //définie port D comme une entrée
    

    for(;;){
       if (verification()){
           PORTA = (1<<PORTA0);
       }
       else
       {
           PORTA = (1<<PORTA1);
       }
    }
}