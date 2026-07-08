#ifndef INTERUPTIONS_H
#define INTERUPTIONS_H

#include <avr/interrupt.h>

#ifdef WEEK_THREE_ONE 
#include "OpdrachtenWeek3\WeekDrieB.h"
ISR(TIMER2_OVF_vect){
	count += 256; // TCNT2 loopt over na 255 -> 256 tellingen bijtellen
}

#endif

#ifdef WEEK_THREE_TWO 
#include "OpdrachtenWeek3\WeekDrieB.h"

ISR(TIMER2_COMP_vect){
	PORTD ^= BIT(7);

	if(OCR2 == OCR2_HIGH_15MS){
		OCR2 = OCR2_LOW_25MS;
	} else {
		OCR2 = OCR2_HIGH_15MS;
	}
}
#endif


#endif