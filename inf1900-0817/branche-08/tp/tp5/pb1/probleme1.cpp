/*
 *Section : 01
 *Equipe : 08
 *Auteurs : Jeremy Perreault (1903274), Eloise Brosseau (2011037) et Douaa Bergheul (2006583)
 *
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t ETEINT = 0x00;

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    uint8_t* adresse = 0x0000;
    char chaine[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*0";

    for (int i = 0; i < 47; i++)
    {
        eeprom_write_byte(adresse, chaine[i]);
    }

    uint8_t chaineLue[47];

    for (int i = 0; i < 47; i++)
    {
        chaineLue[i] = eeprom_read_byte(adresse);
    }

    bool same = true;
    int i = 0;

    while (same && i < 47)
    {
        if (chaineLue[i] != chaine[i])
        {
            same = false;
        }
        i++;
    }

    if (same)
    {
        PORTA = VERT;
    }

    else
    {
        PORTA = ROUGE;
    }

    return 0;
}
