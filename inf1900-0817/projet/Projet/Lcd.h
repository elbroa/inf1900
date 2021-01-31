/// Lcd
/// \file Lcd.h
/// \author Éloïse Brosseau (2011037)
/// \author David Anastacio (2056948)
/// \author Jérémy Perreault (1903274)
/// \date 8 décembre 2020

#ifndef LCD_H
#define LCD_H

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

enum Mode
{
    config,
    simu
};

void afficherMode(Mode mode);

#endif
