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
#include <avr/interrupt.h>
#define F_CPU 8000000
#include <util/delay.h>

enum Etat {etat0, etat1, etat2, etat3, etat4};
volatile Etat etat = etat0;

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR (INT0_vect) {
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    if(PIND & (1 << PIND2)){
        // changements d'états tels que ceux de la
        // semaine précédente
        switch (etat)
        {
        case etat0:
            etat = etat1;
            break;
        case etat1:
            break;
        case etat2:
            etat = etat1;
            break;
        case etat3:
            etat = etat4;
            break;
        case etat4:
            etat = etat3;
            break;
        }
    }
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

ISR (INT1_vect) {
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    if(PIND & (1 << PIND3)){
        // changements d'états tels que ceux de la
        // semaine précédente
        switch (etat)
        {
        case etat0:
            etat = etat2;
            break;
        case etat1:
            etat = etat3;
            break;
        case etat2:
            break;
        case etat3:
            etat = etat0;
            break;
        case etat4:
            break;
        }
    }
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff; //definie PORTA comme des sortie
    DDRD = 0x00; //definie PORTD comme des entrée
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) | (1 << INT1);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    //// Permet de faire un interuption lorsque le front est montant
    EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

int main(){
    initialisation();

    while(true)
    {
        switch (etat)
        {
            case etat0:
                PORTA = 0;
                break;
            case etat1:
                PORTA = (1 << PORTA0);
                break;
            case etat2:
                PORTA = (1 << PORTA1);
                break;
            case etat3:
                PORTA = (1 << PORTA1);
                break;
            case etat4:
                PORTA = (1 << PORTA0);
        }
    }
}