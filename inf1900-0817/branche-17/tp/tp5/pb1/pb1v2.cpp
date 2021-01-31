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
    //ecrit sur le eeprom bite par bit a partir l'adresse 0x0000
    uint8_t* adresse = 0x00;
    bool egal = true;

    for (uint8_t i = 0; i < 47; i++){
        eeprom_write_byte(adresse, mot[i]);
        //un byte prend l'adresse memoire de 0x00 a 0x07 ce qui explique 
        //augmentation de 0x08 a chaque fois
        adresse = adresse + 0x08;
    }
    //Met 0xFF pour determiner la fin des donnee utile
    eeprom_write_byte(adresse, 0xFF);

    //Lecture du eeprom
    _delay_ms (2000);
    //met l'adresse a zéro pour faire comparaison
    adresse = 0x00;
    uint8_t j = 0;
    
    while(eeprom_read_byte(adresse) != 0xFF){
        //comparaison
        if(eeprom_read_byte(adresse) != mot[j]){
            egal = false;
        }
        adresse = adresse + 0x08;
        j++;
    }
    
    //Affiche si egal
    if(egal){
        PORTA = (1 << PORTA0);
    }else
    {
        PORTA = (1 << PORTA1);
    }
    
}