#ifndef LED_H
#define LED_H
#include <avr/io.h>

// Define a structure to represent an LED with its associated port and pin
typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
} LED;

extern LED leds[];
extern const int LED_COUNT;

void init_leds(void);
void TurnLedOn(volatile uint8_t* port, uint8_t pin);
void TurnLedOff(volatile uint8_t* port, uint8_t pin);

#endif