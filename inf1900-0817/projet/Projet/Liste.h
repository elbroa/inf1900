/// Liste des actions
/// \file Liste.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#ifndef LISTE_H
#define LISTE_H
#include "Action.h"
#include "Debug.h"

const int INITIAL_LENGTH = 20;

class Liste 
{
public:
    Liste();

    void trierListe();
    void afficherListe();
    void ajouterElement(Action action);
    void supprimerElement(uint8_t id);

    uint8_t getNbActions();

    Action actions_[INITIAL_LENGTH];

private:
    uint8_t capacite_;
    uint8_t nbActions_;
};

#endif