#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6


int main( void ) {

	DDRD = 0xff;
	
	PORTD = 0x00;
	int bitshift = 0;
	
	for(;;) {
		_delay_ms(500);
		
		PORTD = 0x01 << bitshift;
		
		bitshift++;
		if (bitshift > 7) bitshift = 0;
		
	}

	return 1;
}