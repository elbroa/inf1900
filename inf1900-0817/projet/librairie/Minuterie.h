#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#ifndef MINUTERIE_H
#define MINUTERIE_H

void partirMinuterie(uint16_t duree);

#endif