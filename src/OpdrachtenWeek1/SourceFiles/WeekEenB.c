#include "SupportModules/PinHandling/PinHandling.h"
#include "OpdrachtenWeek1/WeekEenB.h"

#include <util/delay.h>
#include <stdbool.h>
#include <avr/io.h>


void Two_AlternateLedBlinks(){
	setPort(&DDRA,0xff);
	SetPin(&PORTA, 7, 1);

	for(;;){
		InvertPinState(&PORTA,7);
		InvertPinState(&PORTA,6);
		_delay_ms(500);
	}
    
}

void Three_BlinkWithButton(){
	setPort(&DDRD,0xff);
	setPort(&DDRC,0x00);
	
	for(;;){
		while (CheckPinState(&PINC,7)){
		InvertPinState(&PORTD,1);
		_delay_ms(500);
		}

		SetPin(&PORTD,1,0);
	}
}

void Four_Basic_LED_Pattern(){
	setPort(&DDRD,0xff);

	setPort(&PORTD,0xff);

	int bitshift = 0;
	
	for(;;) {
		_delay_ms(50);
		uint8_t bitmask = 0x01 << bitshift;

		setPort(&PORTD, bitmask);
		
		bitshift++;
		if (bitshift > 0x07) bitshift = 0x00;
		
	}
}

void Five_Lookup_LED_Pattern(){
	setPort(&DDRD,0xff);
	setPort(&PORTD,0xff);

	int lookuptable[24] = {
		0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111,
		0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,
		0b10000001,0b01000010,0b00100100,0b00011000,0b00011000,0b00111100,0b01111110,0b11111111
	};

		
	for(;;) {
		for (int i = 0; i < 24; i++){			
			_delay_ms(50);
			setPort(&PORTD,lookuptable[i]);		
		}	
	}
}

void Six_BlinkStates(){

    int previousStateButton = 0x00;

	setPort(&DDRA,0xff);
	setPort(&DDRC,0x00);	
	
	setPort(&PORTD,0x00);

	bool blinklong = false;
	
	for(;;) {
		int Reading = CheckPinState(&PINC,7);
		
		if (Reading & 0x01 && previousStateButton != Reading){
			if (blinklong) blinklong = false;
			else blinklong = true;
		}
			
		if (blinklong) _delay_ms(500);
		else _delay_ms(250);

		InvertPinState(&PORTA,1);
		
		previousStateButton = Reading;		
	}
}
