/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int bitshift = 0;
/******************************************************************
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

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


/******************************************************************
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
int main( void ) {
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input	
	DDRA = 0xFF;

	for(;;) {	
		int index = 0;

		// loop through the array
		for (int i = 0; i < sizeof(pattern)/sizeof(pattern[0]); i++)
		{
			// Write data to PORTA
			PORTA = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}
	return 1;
}
