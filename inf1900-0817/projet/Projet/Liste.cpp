/// Implémentation de la classe Liste
/// \file Liste.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "Liste.h"

/// Crée le constructeur par défaut de la classe Liste.
Liste::Liste()
{
    capacite_ = INITIAL_LENGTH;
    nbActions_ = 0;
}

/// Trie la liste des actions selon l'heure et les minutes auxquels elles doivent s'effectuer.
void Liste::trierListe()
{
    Action temp;
    for (int i = 0; i < nbActions_ - 1; i++)
    {
        for (int j = i; j < nbActions_; j++)
        {
            if (actions_[i].getHeure() > actions_[j].getHeure())
            {
                temp = actions_[i];
                actions_[i] = actions_[j];
                actions_[j] = temp;
            }
            else if (actions_[i].getHeure() == actions_[j].getHeure())
            {
                if (actions_[i].getMinute() > actions_[j].getMinute())
                {
                    temp = actions_[i];
                    actions_[i] = actions_[j];
                    actions_[j] = temp;
                }
            }
        }
    }
}

/// Affiche la liste des actions.
void Liste::afficherListe()
{
    if (nbActions_ == 0)
    {
        DEBUG_PRINT((char *)"\nAucune action programme.\n");
    }
    else
    {
        uint8_t conversionChiffreASCII = 48;
        uint8_t conversionLettreASCII = 65;
        uint8_t conversionCentaine = 100;
        uint8_t conversionDizaine = 10;
        DEBUG_PRINT((char *)"\n ");
        for (uint8_t id = 0; id < nbActions_; id++)
        {
            DEBUG_PRINT((char *)"\n ");

            //Affichage de l'ID
            uint8_t idMin = 9;
            if (id > idMin)
            {
                uint8_t id1;
                uint8_t id2;
                id1 = id / 10;
                id2 = id % 10;
                DEBUG_PRINT((id1 + conversionChiffreASCII));
                DEBUG_PRINT((id2 + conversionChiffreASCII));
            }
            else
            {
                DEBUG_PRINT((char *)"0 ");
                DEBUG_PRINT((id + conversionChiffreASCII));
            }
            DEBUG_PRINT((char *)" -  ");

            //Affichage de l'heure
            uint8_t heure1;
            uint8_t heure2;
            heure1 = actions_[id].getHeure() / conversionDizaine;
            heure2 = actions_[id].getHeure() % conversionDizaine;
            DEBUG_PRINT((heure1 + conversionChiffreASCII));
            DEBUG_PRINT((heure2 + conversionChiffreASCII));
            DEBUG_PRINT((char *)": ");

            //Affichage des minutes
            uint8_t minute1;
            uint8_t minute2;
            minute1 = actions_[id].getMinute() / conversionDizaine;
            minute2 = actions_[id].getMinute() % conversionDizaine;
            DEBUG_PRINT((minute1 + conversionChiffreASCII));
            DEBUG_PRINT((minute2 + conversionChiffreASCII));
            DEBUG_PRINT((char *)" -  ");

            //Affichage du dispositif
            const uint8_t VALEUR_TOUCHE_E = 14;
            const int8_t VALEUR_TOUCHE_ZERO = 0;
            if (actions_[id].getDispositif() < VALEUR_TOUCHE_E)
            {
                uint8_t dispositif;
                uint8_t configuration;
                dispositif = actions_[id].getDispositif();
                configuration = actions_[id].getConfiguration();
                if (configuration == VALEUR_TOUCHE_ZERO)
                    DEBUG_PRINT((char *)"ouvrir porte  ");
                else
                    DEBUG_PRINT((char *)"fermer porte  ");
                DEBUG_PRINT((dispositif + conversionLettreASCII - conversionDizaine));
            }
            else
            {
                uint8_t dispositif;
                dispositif = actions_[id].getDispositif();
                uint8_t configuration1;
                uint8_t configuration2;
                uint8_t configuration3;
                configuration1 = actions_[id].getConfiguration() / conversionCentaine;
                configuration2 = (actions_[id].getConfiguration() - configuration1 * conversionCentaine) / conversionDizaine;
                configuration3 = actions_[id].getConfiguration() - configuration1 * conversionCentaine - configuration2 * conversionDizaine;
                DEBUG_PRINT((char *)"orienter servomoteur  ");
                DEBUG_PRINT((dispositif + conversionLettreASCII - conversionDizaine));
                DEBUG_PRINT((char *)" a  ");
                DEBUG_PRINT((configuration1 + conversionChiffreASCII));
                DEBUG_PRINT((configuration2 + conversionChiffreASCII));
                DEBUG_PRINT((configuration3 + conversionChiffreASCII));
                DEBUG_PRINT((char *)" degres\n");
            }
        }
    }
}

/// Ajoute une action à la liste d'actions.
/// \param action   L'action a ajouter.
void Liste::ajouterElement(Action action)
{
    if (nbActions_ < capacite_)
    {
        actions_[nbActions_] = action;
        nbActions_++;
        trierListe();
        DEBUG_PRINT((char *)"\n\nAction ajoutee avec succes. ");
    }
    else
        DEBUG_PRINT((char *)"\n\nLimite d'actions atteinte. Veuillez en supprimer.");
}

/// Supprime l'action selon son id.
/// \param id   Le id de l'action.
void Liste::supprimerElement(uint8_t id)
{
    if (id <= nbActions_ - 1)
    {
        actions_[id] = Action();
        this->trierListe();
        nbActions_--;
        DEBUG_PRINT((char *)"\n\nAction supprimee avec succes.");
    }
    else
        DEBUG_PRINT((char *)"\n\nErreur : action inexistante.");
}

/// Retourn le nombre d'actions de la liste.
/// \return     Le nombre d'actions.
uint8_t Liste::getNbActions()
{
    return nbActions_;
}
