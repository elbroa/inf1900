#include "Bouton.h"

int main()
{
    DDRA = 0xff; //port A en sortie
    DDRD = 0x00; //port D en entrée

    const uint8_t ROUGE = 1 << PORTA0;
    const uint8_t VERT = 1 << PORTA1;

    while (true)
    {
        if (isPressedD2())
        {
            PORTA = ROUGE;
            _delay_ms(10);
        }
        else
        {
            PORTA = VERT;
            _delay_ms(10);
        }
    }
}