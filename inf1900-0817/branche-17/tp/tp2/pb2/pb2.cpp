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
*          etat0          0       0         etat0         0       0
*          etat0          0       1         etat2         0       1
*          etat0          1       0         etat1         1       0
*          etat1          x       0         etat1         1       0
*          etat1          x       1         etat3         0       1
*          etat2          0       x         etat2         0       1
*          etat2          1       x         etat1         1       0
*          etat3          0       0         etat3         0       1
*          etat3          1       0         etat4         1       0
*          etat3          0       1         etat0         0       0
*          etat4          0       x         etat4         1       0
*          etat4          1       x         etat3         0       1
*/
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

//Permet de vérifier que le bouton-poussoir connecter au PORTD2 est active
bool verificationPIND2()
{
    if (PIND & (1 << PIND2)){
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
        //En fonction de l'etat dans lequel on se trouve change d'etat
        //en fonction de l'entree
        switch (etat)
        {
        case etat0:
            //Si etat0 et Boutton-poussoir connecter au PORTD2
            //affiche couleur rouge et passe a etat1
            if (verificationPIND2())
            {
                etat = etat1;
                PORTA = (1 << PORTA0);
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND2()){}
            }
            //Si boutton-poussoir connecter au PORTD3 affiche couleur vert
            //et passe a etat2
            else if (verificationPIND3())
            {
                etat = etat2;
                PORTA = (1 << PORTA1);
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND3()){}
            }
            break;
        case etat1:
            //si etat1 et que bouton-poussoir connecter au PORTD3 affiche
            //couleur vert et passe a etat3
            if (verificationPIND3())
            {
                etat = etat3;
                PORTA = (1 << PORTA1);
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND3()){}
            }
            break;
        case etat2:
            //si etat2 et que bouton-poussoir connecter au PORTD2 affiche
            //couleur rouge et passe a etat1
            if (verificationPIND2())
            {
                etat = etat1;
                PORTA = (1 << PORTA0);
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND2()){}
            }
            break;
        case etat3:
            //si etat3 et que bouton-poussoir connecter au PORTD3 DEl
            //s'eteint et passe a etat0
            if (verificationPIND3())
            {
                PORTA = 0;
                etat = etat0;
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND3()){}
            }
            //Si boutton-poussoir connecter au PORTD2 affiche la couleur rouge
            //et passe a l'etat4
            else if (verificationPIND2())
            {
                etat = etat4;
                PORTA = (1 << PORTA0);
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND2()){}
            }
            break;
        case etat4:
            //si etat4 et que bouton-poussoir connecter au PORTD2 affiche
            //la couleur verte et passe a etat3
            if (verificationPIND2())
            {
                etat = etat3;
                PORTA = (1 << PORTA1);
                //verifie que bouton-poussoir soit relacher avant de continuer
                while (verificationPIND2()){}
            }
            break;
        default:
            break;
        }
    }
}