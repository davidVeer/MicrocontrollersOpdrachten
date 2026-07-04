#include "Headers/LED.h"
#include <util/delay.h>

void _wait_ms(int interval){
	for (int i = 0;i<interval;i++) _delay_ms(1);
}

void setPort(volatile uint8_t* *ddrReg, uint8_t bitmask){
    *ddrReg = bitmask;
}

void SetPin(volatile uint8_t* port, uint8_t pin, int pinState){
    if (pinState) *port |= (pinState<< pin);
    else *port &= (pinState<< pin);
}

void InvertPinState(volatile uint8_t* port,uint8_t pin){
    *port ^= (1<< pin);
}

int CheckPinState(volatile uint8_t* port,uint8_t pin){
    return (*port >> pin) & 0x01;
}
