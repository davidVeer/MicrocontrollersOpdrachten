#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8e6


int main( void ) {

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
	return 1;
}