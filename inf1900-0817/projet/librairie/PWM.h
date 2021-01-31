#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#ifndef PWM_H
#define PWM_H

void ajustementPWM(uint8_t duree1, uint8_t duree2);

#endif