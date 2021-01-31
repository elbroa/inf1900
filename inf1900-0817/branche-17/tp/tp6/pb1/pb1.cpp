/**
 * Author: David Anastacio
 * Description: l'obejctif est de convertir les donnée analogique
 *              provenant d'un capteur photoresistance en valeur numérique.
 *              Cela nous permettera de determiner l'intensiter de la lumiere
 *              proche de notre robot.
 * Port utiliser: PORTA0 est le port qui nous permet la lecture des donnée analogique.
 *                PORTB0 et PORTB1 sont connecter a un led permettant d'afficher sur un del
 *                l'insiter de la lumiere: faible => couleur de del vert
 *                                         bon intensiter => couleur ambré
 *                                         trop fort => couleur rouge
 **/

#include "can.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main()
{
    //PORTA definie en mode lecture
    //DDRA = 0x00;
    //PORTB definie en mode ecriture
    DDRB = 0xff;

    //construction de la classe can, convertisseur analogique en numerique
    can canPhoto = can();

    uint16_t intensiter;

    while (true)
    {
        //Lit intensiter sur le PORTA le zero en paramètre permet de dire a la fonction
        //de lire sur le PORTA0
        intensiter = canPhoto.lecture(0);
        //fait un decalage de 2 bit vers la droite pour ce débaraser des deux bit moins significatif
        //et de prendre en considerer les deux bit les plus significatif
        intensiter = intensiter >> 2;

        //La valeur a droite de l'opérant varie en fonction du voltage max que que notre circuit
        //VoltageMax = 255 en binaire donc valeur en binaire = voltageDesirer * 255 / VoltageMax
        //Dans notre cas le voltageMax est 3.9V et le voltageDesirer = 2.78 V donc valeur = 255 * 2.78/3.9 = 182
        //dans ce cas la led est verte car la source de lumiere est faible
        if (intensiter <= 182)
        {
            PORTB = (1 << PORTB0);
        }
        //VoltageDesirer entre 2.78 V et 3.18 V car dans cette situation lumiere a une bonne intensiter
        //ValeurMinDesirer = 255 * 2.78/3.9 = 182 et valeurMaxDesirer = 255 * 3.18/3.9 = 208
        else if (intensiter > 182 && intensiter <= 208)
        {
            //Alternance couleur rouge et verte dans le but d'afficher une couleur ambrée dans la vrai vie
            PORTB = (1 << PORTB0);
            _delay_ms(500);
            PORTB = (1 << PORTB1);
            _delay_ms(500);
        }
        //Voltage suppérieur a 3.18 ce qui implique lumiere trop intence et on affiche la couleur rouge
        else
        {
            PORTB = (1 << PORTB1);
        }
    }
}
