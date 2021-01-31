/// Fonction main qui gère l'ensemble des fonctionnalités
/// \file Main.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#define F_CPU 8000000UL

#include <util/delay.h>
#include "Clavier.h"
#include "Debug.h"
#include "Lcd.h"
#include "UART.h"
#include "Horloge.h"
#include "PorteLed.h"
#include "Servomoteur.h"
#include "Liste.h"
#include "Sonar.h"
#include <avr/interrupt.h>
#include "can.h"

volatile bool boutonPoussoir = false;
static const uint8_t CONVERSION_CHIFFRE_ASCII = 48;
static const uint8_t CONVERSION_LETTRE_ASCII = 65;
static const uint8_t CONVERSION_DIZAINE = 10;

/// Crée une interruption sur le bouton-poussoir.
ISR(INT1_vect)
{
    _delay_ms(30);
    boutonPoussoir = true;
    EIFR |= (1 << INTF0);
}

/// Effectue une action selon les informations sélectionnée.
/// \param action   L'action sélectionnée.
/// \param portes   Les différentes portes del.
void effectuerAction(Action action, PorteLed &portes)
{
    const uint8_t VALEUR_PORTE_D = 13;
    const int8_t VALEUR_PORTE_OUVERTE = 0;
    if (action.getDispositif() <= VALEUR_PORTE_D)
    {
        if (action.getConfiguration() == VALEUR_PORTE_OUVERTE)
            portes.changerEtatPorte(action.getDispositif() + CONVERSION_LETTRE_ASCII - CONVERSION_DIZAINE, ouverte);
        else
            portes.changerEtatPorte(action.getDispositif() + CONVERSION_LETTRE_ASCII - CONVERSION_DIZAINE, fermee);
    }
    else
    {
        const uint8_t VALEUR_SERVO_E = 14;
        if (action.getDispositif() == VALEUR_SERVO_E)
            servomoteurPWME(calculerDelai(action.getConfiguration()));
        else
            servomoteurPWMF(calculerDelai(action.getConfiguration()));
    }
}

/// Retourne l'heure sélectionnée au clavier.
/// \return     L'heure choisie selon la combinaison des deux touches appuyées.
uint8_t entrerHeure()
{
    uint8_t heure1;
    uint8_t heure1Max = 2;
    do
    {
        heure1 = detecterTouche();
    } while (heure1 > heure1Max);
    _delay_ms(250);

    DEBUG_PRINT(('\n'));
    DEBUG_PRINT((heure1 + CONVERSION_CHIFFRE_ASCII));

    uint8_t heure2;
    uint8_t heure2Max1 = 9;
    uint8_t heure2Max2 = 4;
    do
    {
        heure2 = detecterTouche();
    } while ((heure2 > heure2Max1 && heure1 < heure1Max) || (heure2 > heure2Max2 && heure1 == heure1Max));
    _delay_ms(250);

    DEBUG_PRINT((heure2 + CONVERSION_CHIFFRE_ASCII));
    uint8_t convHeure1 = 10;
    return (heure1 * convHeure1 + heure2);
}

/// Retourne les minutes sélectionnées au clavier.
/// \return     Les minutes choisies selon la combinaison des deux touches appuyées.
uint8_t entrerMinute()
{
    uint8_t minute1;
    uint8_t minute1Max = 5;
    do
    {
        minute1 = detecterTouche();
    } while (minute1 > minute1Max);
    _delay_ms(250);

    DEBUG_PRINT((minute1 + CONVERSION_CHIFFRE_ASCII));

    uint8_t minute2;
    uint8_t minute2Max = 9;
    do
    {
        minute2 = detecterTouche();
    } while (minute2 > minute2Max);
    _delay_ms(250);

    DEBUG_PRINT((minute2 + CONVERSION_CHIFFRE_ASCII));
    uint8_t convMinute1 = 10;
    return (minute1 * convMinute1 + minute2);
}

/// Retourne le dispositif sélectionné au clavier.
/// \return     Le dispositif choisi.
uint8_t entrerDispositif()
{
    uint8_t dispositif;
    const uint8_t VALEUR_MIN_DISPO = 10;
    uint8_t VALEUR_MAX_DISPO = 15;
    do
    {
        dispositif = detecterTouche();
    } while (dispositif < VALEUR_MIN_DISPO || dispositif > VALEUR_MAX_DISPO);
    _delay_ms(250);
    DEBUG_PRINT((dispositif + CONVERSION_LETTRE_ASCII - 10));
    return dispositif;
}

/// Retourne la configuration sélectionnée au clavier pour une porte DEL.
/// \return     La configuration choisie.
uint8_t entrerConfigPorte()
{
    uint8_t configuration;
    const uint8_t VALEUR_MAX_CONGIG_PORTES = 2;
    do
    {
        configuration = detecterTouche();
    } while (configuration > VALEUR_MAX_CONGIG_PORTES);
    _delay_ms(250);
    DEBUG_PRINT((configuration + CONVERSION_CHIFFRE_ASCII));
    return configuration;
}

/// Retourne la configuration sélectionnée au clavier pour un servomoteur.
/// \return     La configuration choisie.
uint8_t entrerConfigServo()
{
    uint8_t configuration1;
    uint8_t configuration2;
    uint8_t configuration3;
    const uint8_t VALEUR_TOUCHE_UN = 1;
    const uint8_t VALEUR_TOUCHE_A = 10;
    const int8_t VALEUR_TOUCHE_ZERO = 0;
    const uint8_t VALEUR_TOUCHE_HUIT = 8;
    do
    {
        configuration1 = detecterTouche();
    } while (configuration1 > VALEUR_TOUCHE_UN);
    _delay_ms(250);
    DEBUG_PRINT((configuration1 + CONVERSION_CHIFFRE_ASCII));
    do
    {
        configuration2 = detecterTouche();
    } while ((configuration2 > VALEUR_TOUCHE_A && configuration1 == VALEUR_TOUCHE_ZERO) 
    || (configuration2 > VALEUR_TOUCHE_HUIT && configuration1 == VALEUR_TOUCHE_UN));
    _delay_ms(250);
    DEBUG_PRINT((configuration2 + CONVERSION_CHIFFRE_ASCII));
    do
    {
        configuration3 = detecterTouche();
    } while (configuration3 > VALEUR_TOUCHE_A);
    _delay_ms(250);
    DEBUG_PRINT((configuration3 + CONVERSION_CHIFFRE_ASCII));
    uint8_t convConfig1 = 100;
    uint8_t convConfig2 = 10;
    return (configuration1 * convConfig1 + configuration2 * convConfig2 + configuration3);
}

/// Initialisation de l'interruption sur le bouton-poussoir.
void initialisationInt(void)
{
    cli();
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11) | (1 << ISC10);
    sei();
}

int main()
{
    DDRC = (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (0 << PORTC5);
    DDRD = (1 << PORTD0) | (1 << PORTD1) | (0 << PORTD2) | (0 << PORTD3) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
    DDRA = (1 << PORTA0) | (1 << PORTA1) | (1 << PORTA2) | (1 << PORTA3) | (1 << PORTA4) | (0 << PORTA5) | (0 << PORTA6) | (0 << PORTA7);

    initialisationInt();
    initialisationUART();
    DEBUG_PRINT(('\t'));

    PorteLed portes;
    Etats etat = init;
    Liste listeActions;
    can capteur;

    uint8_t heureInitiale = 0;
    uint8_t minuteInitiale = 0;
    uint8_t heureTemp = 0;
    uint8_t minuteTemp = 0;

    const uint8_t HEURE_MAX = 24;
    const uint8_t MINUTE_MAX = 60;
    const uint8_t VALEUR_TOUCHE_SIX = 6;
    const uint8_t VALEUR_TOUCHE_NEUF = 9;
    const uint8_t VALEUR_TOUCHE_D = 13;
    const uint8_t VALEUR_TOUCHE_E = 14;
    const int8_t VALEUR_TOUCHE_ZERO = 0;
    const uint8_t CONV_ID = 10;

    remiseHorlogeZero();

    while (true)
    {
        afficherMode(config);
        afficherMessage(etat);
        uint8_t touche = 255;
        while (touche > VALEUR_TOUCHE_SIX || touche == VALEUR_TOUCHE_ZERO)
        {
            touche = detecterTouche();
        }

        etat = definirEtat(touche);
        afficherMessage(etat);

        switch (etat)
        {
        case option1:
            DEBUG_PRINT((char *)"\n\nVous avez selectionne les chiffres suivant : \n");
            heureInitiale = entrerHeure();
            minuteInitiale = entrerMinute();
            changerHeureHorloge(heureInitiale, minuteInitiale);
            etat = init;
            break;

        case option2:
            DEBUG_PRINT((char *)"\n\nVous avez selectionne le dispositif : ");
            uint8_t dispositif;
            dispositif = entrerDispositif();
            DEBUG_PRINT((char *)"\n\nVous avez selectionne la configuration : ");
            uint8_t configuration;
            if (dispositif <= VALEUR_TOUCHE_D)
            {
                configuration = entrerConfigPorte();
                if (configuration == VALEUR_TOUCHE_ZERO)
                    portes.changerEtatPorte(dispositif + CONVERSION_LETTRE_ASCII - 10, ouverte);
                else
                    portes.changerEtatPorte(dispositif + CONVERSION_LETTRE_ASCII - 10, fermee);
            }
            else
            {
                configuration = entrerConfigServo();
                if (dispositif == VALEUR_TOUCHE_E)
                    servomoteurPWME(calculerDelai(configuration));
                else
                    servomoteurPWMF(calculerDelai(configuration));
            }
            etat = init;
            break;

        case option3:
            listeActions.afficherListe();
            etat = init;
            break;

        case option4:
            DEBUG_PRINT((char *)"\n\nNouvelle action programmee : \n");
            uint8_t heureP;
            heureP = entrerHeure();
            uint8_t minuteP;
            minuteP = entrerMinute();
            DEBUG_PRINT((32));
            uint8_t dispositifP;
            dispositifP = entrerDispositif();
            uint8_t configurationP;
            if (dispositifP <= VALEUR_TOUCHE_D)
                configurationP = entrerConfigPorte();
            else
                configurationP = entrerConfigServo();

            listeActions.ajouterElement(Action(heureP, minuteP, dispositifP, configurationP));
            etat = init;
            break;

        case option5:
            DEBUG_PRINT((char *)"\n\nIdentifiant : \n");
            uint8_t id1;
            do
            {
                id1 = detecterTouche();
            } while (id1 > VALEUR_TOUCHE_NEUF);
            _delay_ms(250);

            DEBUG_PRINT(('\n'));
            DEBUG_PRINT((id1 + CONVERSION_CHIFFRE_ASCII));

            uint8_t id2;
            do
            {
                id2 = detecterTouche();
            } while (id2 > VALEUR_TOUCHE_NEUF);
            _delay_ms(250);
            DEBUG_PRINT((id2 + CONVERSION_CHIFFRE_ASCII));
            uint8_t id; 
            id = id1 * CONV_ID + id2;
            listeActions.supprimerElement(id);
            etat = init;
            break;

        case option6:
            afficherMode(simu);

            boutonPoussoir = false;

            for (uint8_t heure = 0; heure < HEURE_MAX && !boutonPoussoir; heure++)
            {
                for (uint8_t minute = 0; minute < MINUTE_MAX && !boutonPoussoir; minute++)
                {
                    for (uint8_t action = 0; action < listeActions.getNbActions(); action++)
                    {
                        heureTemp = heureInitiale + heure;
                        minuteTemp = minuteInitiale + minute;
                        if (heureTemp > HEURE_MAX)
                        {
                            heureTemp -= HEURE_MAX;
                        }
                        if (minuteTemp > MINUTE_MAX)
                        {
                            minuteTemp -= MINUTE_MAX;
                        }
                        if (listeActions.actions_[action].getHeure() == heureTemp && listeActions.actions_[action].getMinute() == minuteTemp)
                        {
                            effectuerAction(listeActions.actions_[action], portes);
                        }
                    }

                    while (scruterSonar())
                    {
                    }

                    const uint8_t DELAI_MAX = 255;
                    uint8_t vitesse;
                    uint8_t minuterie;

                    vitesse = capteur.lecture(6) >> 2;
                    minuterie = DELAI_MAX - vitesse;

                    const uint16_t SEC_EN_MS = 1000;
                    const uint8_t H_EN_MIN = 60;
                    const uint8_t NB_DELAIS = 2;

                    for (uint8_t duree = 0; duree < minuterie; duree++)
                    {
                        const uint8_t conversionMinute = (SEC_EN_MS - (SEC_EN_MS / H_EN_MIN)) / DELAI_MAX;
                        _delay_ms(conversionMinute);
                    }

                    if (!boutonPoussoir)
                    {
                        const uint8_t conversionHeure = SEC_EN_MS / H_EN_MIN / NB_DELAIS;
                        PORTD = 0 << PORTD5;
                        _delay_ms(conversionHeure);
                        PORTD = 1 << PORTD5;
                        _delay_ms(conversionHeure);
                    }
                }
            }

            if (boutonPoussoir)
            {
                heureInitiale = heureTemp;
                minuteInitiale = minuteTemp;
            }

            boutonPoussoir = false;
            etat = init;
            break;

        default:
            break;
        }
    }
}
