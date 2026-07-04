#include "Headers/WeekTweeB.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char Characters[16] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
};

int bitshift = 0;

#define SEG_A 0b00000001
#define SEG_B 0b00000010
#define SEG_C 0b00000100
#define SEG_D 0b00001000
#define SEG_E 0b00010000
#define SEG_F 0b00100000
#define SEG_G 0b01000000

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

void setDisplay(int num){
	if(num > 15 || num < 0){
		PORTA = Characters[14];
		} else {
		PORTA = Characters[num];
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
	DDRD = 0xF0;
	DDRA = 0xFF;


	EICRA |= 0x07;	
	EIMSK |= 0x03;	
	
	sei();				

	for(;;) {	
		if(PIND == 0b11111111){
			bitshift = 0;
			setDisplay(bitshift);
		}						
	}
}

void Four_Segment_Display_Animation(){
	DDRD = 0xF0;
	DDRA = 0xFF;

	for(;;) {	
		int index = 0;

		for (int i = 0; i < sizeof(pattern)/sizeof(pattern[0]); i++)
		{
			PORTA = pattern[index].data;
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