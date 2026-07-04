#include "Headers/WeekTweeB.h"


#include "SupportModules/Segment/Headers/SingleSegment.h"
#include "SupportModules/PinHandling/Headers/PinHandling.h"
// #define WEEK_TWO_ONE
// #define WEEK_TWO_TWO
#define WEEK_TWO_THREE

#include "Headers/Interuptions.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

bitshift = 0;

PATTERN_STRUCT pattern[] = {
	// Rondlopend effect (buitenring): a -> b -> c -> d -> e -> f -> a
	{SEG_A, 100},
	{SEG_B, 100},
	{SEG_C, 100},
	{SEG_D, 100},
	{SEG_E, 100},
	{SEG_F, 100},
	{0x00,  100},

	// Knipperend "8" effect
	{0b01111111, 200},
	{0x00,       200},
	{0b01111111, 200},
	{0x00,       200},
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void One_Interupt(){
	DDRD = 0xF0;

	EICRA |= 0x0B;
	EIMSK |= 0x03;
	
	sei();				

	while (1) {
		PORTD ^= (1<<7);
		_delay_ms( 500 );								
	}
}

void Two_Multiple_Interupts(){
	DDRD = 0xF0;

	EICRA |= 0x0B;
	EIMSK |= 0x03;

	sei();	
	
    for(;;){}
}

void Three_Segment_Display(){
	setPort(&DDRD,0x00);
	setPort(&DDRA,0xff);


	EICRA |= 0x07;	
	EIMSK |= 0x03;	
	
	sei();				

	for(;;) {	
		if(CheckPinState(&PIND,1) && CheckPinState(&PIND,2)){
			bitshift = 0;
			setDisplayNumber(&PORTA, bitshift);
		}						
	}
}

void Four_Segment_Display_Animation(){
	setPort(&DDRA,0xff);

	for(;;) {	
		int index = 0;

		for (int i = 0; i < sizeof(pattern)/sizeof(pattern[0]); i++)
		{
			setDisplay(&PORTA, pattern[index].data);
			wait(pattern[index].delay);
			index++;
		}
	}
}

void Five_LCD_Module(){
		init_4bits_mode();
		
		
		_delay_ms(10);
		
		lcd_clear();
		
		_delay_ms(10);
		
		lcd_write_string("spatie weg");
}