/*
* Nom: David Anastacio, Douaa Bergheul et Hamza Aquede
* Description: Il s'agit d'un machine a etat qui nous 
*              permet d'allumer un del en fonction de l'etat;
* Fonction: verificationPIND2 
*           Description: vérifie si bouton-poussoir conecter au 
*           PORTD2 est activer.
*           verificationPIND3 
*           Description: vérifie si bouton-poussoir conecter au 
*           PORTD3 est activer.
* Materiel: PORTD2 Considere comme un entree connecter a un bouton-poussoir
*           PORTD3 Considere comme un entree connecter a un bouton-poussoir
*           PORTA0 Considere comme un sortie connecter a une Del rouge
*           PORTA1 Considere comme un sortie connecter a une Del verte
* Table Etat:
*       Etat present    PIND2   PIND3   Etat suivant    PORTA0  PORTA1
*          etat0          0       0         etat0          0       0
*          etat0          1       0         etat0          0       0
*          etat0          x       1         etat1          0       1
*          etat1          0       x         etat1          0       1
*          etat1          1       x         etat2          0       1
*          etat2          0       x         etat2          0       1
*          etat2          1       x         etat3          0       1
*          etat3          0       x         etat3          0       1
*          etat3          1       x         etat4          0       1
*          etat4          x       x         etat0          1       0
*
*/
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

//Permet de vérifier que le bouton-poussoir connecter au PORTD2 est active
bool verificationPIND2()
{
    if (PIND & (1 << PIND2))
    {
        _delay_ms(10);
        return (PIND & (1 << PIND2));
    }
    return false;
}

//Permet de vérifier que le bouton-poussoir connecter au PORTD2 est active
bool verificationPIND3()
{
    if (PIND & (1 << PIND3))
    {
        _delay_ms(10);
        return (PIND & (1 << PIND3));
    }
    return false;
}

int main()
{
    DDRA = 0xff; //definie PORTA comme des sortie
    DDRD = 0x00; //definie PORTD comme des entrée
    enum Etat {etat0, etat1, etat2, etat3, etat4};

    Etat etat = etat0; //definie etat initial soit etat0

    while (true)
    {
        //Si PORTD3 active et que nous sommes etat0
        if (verificationPIND3() && etat == etat0)
        {
            //change pour etat1 et active del verte
            etat = etat1;
            PORTA = (1 << PORTA1);
        }
        //Si PORTD2 active et que nous sommes etat1
        else if (verificationPIND2() && etat == etat1)
        {
            //verifie que bouton-poussoir soit relacher avant de continuer
            while (verificationPIND2()){}
            //change d'état
            etat = etat2;
        } //Si PORTD2 active et que nous sommes etat2
        else if (verificationPIND2() && etat == etat2)
        {
            //verifie que bouton-poussoir soit relacher avant de continuer
            while (verificationPIND2()){}
            //change d'état
            etat = etat3;
        } //Si PORTD2 active et que nous sommes etat3
        else if (verificationPIND2() && etat == etat3)
        {
            //verifie que bouton-poussoir soit relacher avant de continuer
            while (verificationPIND2()){}
            //change d'état
            etat = etat4;
        }
        //Si etat4
        else if (etat == etat4)
        {
            //Change active PORTA0 Pour obtenir del rouge
            PORTA = (1 << PORTA0);
            //retour a etat 0
            etat = etat0;
            //eteint del apres un delai de 1s
            _delay_ms(1000);
            PORTA = 0;
        }
    }
}