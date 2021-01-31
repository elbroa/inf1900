/// PorteLed
/// \file PorteLed.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include <avr/io.h>
#include <util/delay.h>

enum EtatPorte { ouverte, fermee};

class PorteLed{
public:
    PorteLed();
    void changerEtatPorte(char porte, EtatPorte etat);
    void afficherPorte(uint8_t etat);
    void afficherPorteModifiee(EtatPorte etat, uint8_t indice);

private:
    EtatPorte porteA;
    EtatPorte porteB;
    EtatPorte porteC;
    EtatPorte porteD;
};
