#include "led.h"

LED leds[] = {
    {&PORTA, 0},
    {&PORTA, 1},
    {&PORTA, 2},
};

const int LED_COUNT = sizeof(leds) / sizeof(leds[0]);

// Initialize the LEDs by setting their corresponding pins as output and turning them off
void init_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        // DDR-register ligt 1 adres voor het PORT-register
        *(leds[i].port - 1) |= (1 << leds[i].pin);   // pin als output
        *(leds[i].port) &= ~(1 << leds[i].pin);      // start uit
    }
}

// Turn on the LED connected to the specified port and pin
void TurnLedOn(volatile uint8_t* port, uint8_t pin) {
    *port |= (1 << pin);
}

// Turn off the LED connected to the specified port and pin
void TurnLedOff(volatile uint8_t* port, uint8_t pin) {
    *port &= ~(1 << pin);
}