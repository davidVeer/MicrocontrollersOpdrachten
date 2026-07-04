#ifndef INTERUPTIONS_H
#define INTERUPTIONS_H

#include <avr/interrupt.h>

#ifdef WEEK_TWO_ONE 

ISR( INT0_vect ) {
    PORTD |= (1<<5);		
}

ISR( INT1_vect ) {
    PORTD &= ~(1<<5);		
}
#endif

#ifdef WEEK_TWO_TWO 
ISR( INT0_vect ) {
		PORTA = 1<< bitshift;
   		bitshift++;
   		if (bitshift > 7) bitshift = 0;
}

#endif

#ifdef WEEK_TWO_THREE 
ISR( INT0_vect ) {
   	bitshift++;
   	setDisplayNumber(&PORTA, bitshift);
}

ISR( INT1_vect ) {
	bitshift--;
	setDisplayNumber(&PORTA, bitshift);
}

#endif

#endif