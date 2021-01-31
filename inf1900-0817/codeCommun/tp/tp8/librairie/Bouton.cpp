#include "Bouton.h"

bool isPressedD2()
{
    if (PIND & (1 << PIND2))
    {
        _delay_ms(10);
        return (PIND & (1 << PIND2));
    }
    return false;
}

bool isPressedD3()
{
    if (PIND & (1 << PIND3))
    {
        _delay_ms(10);
        return (PIND & (1 << PIND3));
    }
    return false;
}
