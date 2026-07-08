#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> 
#include "button.h"

void button_init(){
    DDRD &= ~(1 << PD0); // Set PD0 as input
    PORTD |= (1 << PD0); // Enable pull-up resistor on PD0
    
    EICRA |= 0b00000010;    // Set INT0 and INT1 to trigger on falling edge
	EIMSK |= 0b00000001;    // Enable INT0 and INT1

	sei();
}

    // EICRA |= 0b00101010;    // Set INT0, INT1, and INT2 to trigger on falling edge
	// EIMSK |= 0b00000111;    // Enable INT0, INT1, and INT2
    // ISR( INT0_vect ) {  
    //     // Handle button press for INT0 (PG1)
    // }