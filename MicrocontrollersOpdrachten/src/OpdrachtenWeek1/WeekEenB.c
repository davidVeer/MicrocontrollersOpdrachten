#include "..\SupportModules\LED\Headers\LED.h"
#include "Headers/WeekEenB.h"

#include <util/delay.h>
#include <stdbool.h>
#include <avr/io.h>

void blink_ms( int millis )
{	
	if (PORTD == 0x40){
		PORTD = 0x00;
	}
	else {
		PORTD = 0x40;
	}
	
		for(int i = 0 ; i< millis ; i++){
			_delay_ms(1);
		}
}

void Two_AlternateLedBlinks(){
    TurnLedOn(&PORTA,0);

    _delay_ms(1000);

    TurnLedOff(&PORTA,0);

    _delay_ms(1000);

    TurnLedOn(&PORTA,0);
}

void Three_BlinkWithButton(){
	DDRC = 0x00;
	
	DDRE = 0xff;
	PORTE = 0x00;
	
	for(;;) {
		if (((PINC >> 7) & 0x01) != 1) {
			PORTE = 0x00;
			continue;
		}
		
		_delay_ms(500);
		
		if(PORTE == 0b01000000){
			PORTE = 0b00100000;
		}
		else {
			PORTE = 0b01000000;
		}
	}
}

void Four_Basic_LED_Pattern(){
	DDRD = 0xff;
	
	PORTD = 0x00;
	int bitshift = 0;
	
	for(;;) {
		_delay_ms(500);
		
		PORTD = 0x01 << bitshift;
		
		bitshift++;
		if (bitshift > 7) bitshift = 0;
		
	}
}

void Five_Lookup_LED_Pattern(){
	DDRD = 0xff;
	
	int lookuptable[3][8] = {
		{0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111},
		{0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001},
		{0b10000001,0b01000010,0b00100100,0b00011000,0b00011000,0b00111100,0b01111110,0b11111111}
	};
	
	PORTD = 0x00;
		
	for(;;) {
		for (int j = 0; j < 3; j++){
			for(int i = 0; i < 8; i++){				
				_delay_ms(500);
				PORTD = lookuptable[j][i];
			}			
		}
			
			
	}
}

void Six_BlinkStates(){

    int previousStateButton = 0x00;

	DDRD = 0xff;
	DDRC = 0x00;	
	PORTD = 0x00;
	bool blinklong = false;
	
	for(;;) {
		int Reading = PINC;
		
		if (Reading & 0x01 && previousStateButton != Reading){
			if (blinklong) blinklong = false;
			else blinklong = true;
			}
			
		if (blinklong){
			blink_ms(500);
		}
		else{
			blink_ms(125);
		}
		
		
		previousStateButton = Reading;		
	}
}
