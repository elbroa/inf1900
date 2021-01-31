#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#ifndef BOUTON_H
#define BOUTON_H

bool isPressedD2();
bool isPressedD3();

#endif