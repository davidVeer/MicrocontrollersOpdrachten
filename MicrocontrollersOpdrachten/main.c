#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6

int main( void ) {

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

	return 1;
}