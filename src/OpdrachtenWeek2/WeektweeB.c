#include "Headers/WeekTweeB.h"


#include "SupportModules/Segment/Headers/SingleSegment.h"
#include "SupportModules/Interupts/Headers/Interupts.h"
#include "SupportModules/PinHandling/Headers/PinHandling.h"
#include "SupportModules/LCD/Headers/LCD.h"

// #define WEEK_TWO_ONE
// #define WEEK_TWO_TWO
// #define WEEK_TWO_THREE
#include "Headers/Interuptions.h"

#include <avr/io.h>
#include <util/delay.h>


int bitshift = 0;

PATTERN_STRUCT pattern[] = {
	{SEG_A, 100},
	{SEG_B, 100},
	{SEG_C, 100},
	{SEG_D, 100},
	{SEG_E, 100},
	{SEG_F, 100},

	{0x00,  100},
	{0xff, 200},
	{0x00, 200},
	{0xff, 200},
	{0x00, 200},
};


void One_Interupt(){
	initInterupts(0b00001010,0b00000011);			
	SetPin(&DDRD, 6,1);

	for(;;){
		InvertPinState(&PORTD, 6);
		_delay_ms( 50 );								
	}
}

void Two_Multiple_Interupts(){
	initInterupts(0b00001010,0b00000011);	
	
    for(;;){}
}

void Three_Segment_Display(){
	initInterupts(0b00001010,0b00000011);			

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
		
		_delay_ms(100);
		
		lcd_clear();
		
		_delay_ms(100);
		
		lcd_write_string("spatie weg");
}