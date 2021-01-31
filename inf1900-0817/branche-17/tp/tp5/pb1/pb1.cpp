#include <avr/io.h>
#include <avr/eeprom.h>
#define F_CPU 8000000
#include <util/delay.h>

int main()
{
    DDRA =0xff;
    //"*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    //2a 50 2a 4f 2a 4c 2a 59 2a 54 2a 45 2a 43 2a 48 2a 4e
    // 2a 49 2a 51 2a 55 2a 45 2a 
    //20 2a 4d 2a 4f 2a 4e 2a 54 2a 52 2a 45 2a 41 2a 4c 2a 00
    char mot[47] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    //ecrit sur le eeprom en block a l'adresse 0x0000
    eeprom_write_block(mot, 0x0000, 46);
    
    bool egal = true;
    _delay_ms(2000);

    char motLu[47];
    //lecture sur le eeprom en block a l'addresse 0x0000
    eeprom_read_block(motLu, 0x0000, 46);

    for(int i = 0; i < 47; i++){
        if(mot[i] != motLu[i]){
            egal = false;
        }
    }
    
    if(egal){
        PORTA = (1 << PORTA0);
    }else
    {
        PORTA = (1 << PORTA1);
    }   
}