#ifndef LED_H
#define LED_H
#include <avr/io.h>

void setPort(volatile uint8_t* *ddrReg, uint8_t bitmask);
void SetPin(volatile uint8_t* port, uint8_t pin, int pinState);
void InvertPinState(volatile uint8_t* port,uint8_t pin);
int CheckPinState(volatile uint8_t* port,uint8_t pin);
void BlinkPin(volatile uint8_t* port,uint8_t pin,int interval_millis);

#endif