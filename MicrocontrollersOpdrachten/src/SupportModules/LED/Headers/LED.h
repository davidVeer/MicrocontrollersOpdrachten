#ifndef LED_H
#define LED_H
#include <avr/io.h>

void TurnLedOn(volatile uint8_t* port, uint8_t pin);
void TurnLedOff(volatile uint8_t* port, uint8_t pin);

#endif