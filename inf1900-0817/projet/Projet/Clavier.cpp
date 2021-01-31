/// Implémentation du clavier
/// \file Clavier.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "Debug.h"
#include "Clavier.h"
#include <util/delay.h>

/// Détecte la touche du clavier qui a été appuyée.
/// \return     La touche appuyée.
uint8_t detecterTouche()
{
    uint8_t nbColonnes = 4;
    uint8_t nbRangees = 4;

    DEBUG_PRINT(('\0'));

    for (uint8_t colonne = 0; colonne < nbColonnes; colonne++)
    {
        for (uint8_t rangee = 0; rangee < nbRangees; rangee++)
        {
            PORTC = clavier[rangee][colonne];
            _delay_ms(1);
            if (PINC & (1 << PINC5))
            {
                return (colonne + nbColonnes * rangee);
            }
        }
    }

    return -1;
}

/// Retourne un état à partir de l'entrée du clavier.
/// \param touche   La touche appuyée.
/// \return         l'état définie.
Etats definirEtat(uint8_t touche)
{
    const uint8_t VALEUR_TOUCHE_UN = 1;
    const uint8_t VALEUR_TOUCHE_DEUX = 2;
    const uint8_t VALEUR_TOUCHE_TROIS = 3;
    const uint8_t VALEUR_TOUCHE_QUATRE = 4;
    const uint8_t VALEUR_TOUCHE_CINQ = 5;
    const uint8_t VALEUR_TOUCHE_SIX = 6;

    if (touche == VALEUR_TOUCHE_UN)
    {
        return option1;
    }

    if (touche == VALEUR_TOUCHE_DEUX)
    {
        return option2;
    }

    if (touche == VALEUR_TOUCHE_TROIS)
    {
        return option3;
    }

    if (touche == VALEUR_TOUCHE_QUATRE)
    {
        return option4;
    }

    if (touche == VALEUR_TOUCHE_CINQ)
    {
        return option5;
    }

    if (touche == VALEUR_TOUCHE_SIX)
    {
        return option6;
    }

    DEBUG_PRINT((char *)"\nL'option entree est invalide, veuillez reessayer \n");
    return init;
}

/// Affiche le message correspond à l'option choisi par l'utilisateur.
/// \param etat     L'etat correspondant à l'option choisi.
void afficherMessage(Etats etat)
{
    switch (etat)
    {
    case init:
        DEBUG_PRINT((char *)"\n\nVeuillez choisir parmi l'une des options suivantes :\n 1- Definir l'heure de depart \n 2- Definir l'etat d'un "
                            "dispositif \n 3- Afficher les actions programmees \n 4- Programmer une action \n 5- Supprimer une action "
                            "programmee \n 6- Demarrer la simulation \n");
        break;
    case option1:
        DEBUG_PRINT((char *)"\n\nEntrez lheure et les minutes de depart de la simulation. HHMM \n");
        break;

    case option2:
        DEBUG_PRINT((char *)"\n\nEntrez lidentifiant dun dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180) \n");
        break;

    case option3:
        DEBUG_PRINT((char *)"\n\nOption 3 \n");
        break;

    case option4:
        DEBUG_PRINT((char *)"\n\nEntrez une action a programmer. HHMM (A|B|C|D)(0|1) ou (E|F)(000-180) \n");
        break;

    case option5:
        DEBUG_PRINT((char *)"\n\nEntrez le numero dune action a supprimer. \n");
        break;

    case option6:
        DEBUG_PRINT((char *)"\n\nOption 6 \n");
        break;

    default:
        DEBUG_PRINT((char *)"\n\nL'option entree est invalide, veuillez reessayer \n");
        break;
    }
}
