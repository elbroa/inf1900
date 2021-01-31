/// Implémentation de l'écran lcd
/// \file Lcd.cpp
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#include "Lcd.h"

#define LCD_DDR DDRB   // Data Direction Register AVR occupé par l'aff.
#define LCD_PORT PORTB // Port AVR occupé par l'afficheur

/// Affiche le mode donné sur l'écran lcd.
/// \param mode     Le mode
void afficherMode(Mode mode)
{
    // Création de l'objet (l'afficheur est connecté sur le port LCD_PORT)
    LCM disp(&LCD_DDR, &LCD_PORT);
    switch (mode)
    {
    case config:
        disp.clear();
        disp.write("Mode : ");
        disp.write("Configuration", LCM_FW_HALF_CH);
        break;
    case simu:
        disp.clear();
        disp.write("Mode : ");
        disp.write("Simulation", LCM_FW_HALF_CH);
        break;
    default:
        disp.clear();
        disp.write("Erreur : ");
        disp.write("Entree invalide", LCM_FW_HALF_CH);
        break;
    }
}
