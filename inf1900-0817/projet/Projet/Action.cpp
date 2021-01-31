/// Implémentation de la classe Action.
/// \file Action.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "Action.h"
#include "Debug.h"

uint8_t heureInitiale = 24;
uint8_t minuteInitiale = 59;
uint8_t dispositifInitial = 10;
int8_t configurationInitiale = 0;

/// Crée le constructeur par défaut de la classe Action.
Action::Action()
{
    heure_ = heureInitiale;
    minute_ = minuteInitiale;
    dispositif_ = dispositifInitial;
    configuration_ = configurationInitiale;
}

/// Crée le constructeur par paramètres de la classe Action.
Action::Action(uint8_t heure, uint8_t minute, uint8_t dispositif, uint8_t configuration)
{
    heure_ = heure;
    minute_ = minute;
    dispositif_ = dispositif;
    configuration_ = configuration;
}

/// Retourne l'heure de l'action.
/// \return     L'heure de l'action.
uint8_t Action::getHeure()
{
    return heure_;
}

/// Retourne les minutes de l'action.
/// \return     Les minutes de l'action.
uint8_t Action::getMinute()
{
    return minute_;
}

/// Retourne le dispositif de l'action.
/// \return     Le dispositif de l'action.
uint8_t Action::getDispositif()
{
    return dispositif_;
}

/// Retourne la configuration de l'action.
/// \return     La configuration de l'action.
uint8_t Action::getConfiguration()
{
    return configuration_;
}