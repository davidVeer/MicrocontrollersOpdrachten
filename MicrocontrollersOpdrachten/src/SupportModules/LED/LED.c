#include "Headers/LED.h"

void TurnLedOn(volatile uint8_t* port, uint8_t pin){
    *(port -1) |= (1<< pin);

    *port |= (1<< pin); 
}

void TurnLedOff(volatile uint8_t* port, uint8_t pin){
    *(port -1) &= (1<< pin);

    *port &= (0<< pin); 
}