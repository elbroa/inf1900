#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

bool isPressed(){
    if((PIND & (1 << PIND2))){
        _delay_ms(10);
        if((PIND & (1 << PIND2))){
            return true;
        }
    }
    return false;
}

int main(){
    DDRA = 0xff;
    DDRD = 0x00; 

    const uint8_t rouge = 1 << PORTA0; //0x01
    const uint8_t vert = 1 << PORTA1; //0x02

    while(true){
        if (isPressed()){
            PORTA = rouge;
            _delay_ms(10);
        }
        else
        {
            PORTA = vert;
            _delay_ms(10);
        }
    
    }
return 0;
}