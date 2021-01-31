/// Action
/// \file Action.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#ifndef ACTION_H
#define ACTION_H
#include <avr/io.h>

class Action
{
public:
    Action();
    Action(uint8_t heure, uint8_t minute, uint8_t dispositif, uint8_t configuration);

    uint8_t getHeure();
    uint8_t getMinute();
    uint8_t getDispositif();
    uint8_t getConfiguration();

private:
    uint8_t heure_;
    uint8_t minute_;
    uint8_t dispositif_;
    uint8_t configuration_;
};

#endif