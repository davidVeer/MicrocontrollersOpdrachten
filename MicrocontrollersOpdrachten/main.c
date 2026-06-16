#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define F_CPU 8e6

int previousStateButton = 0x00;


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



int main( void ) {

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
			blink_ms(5000);
		}
		else{
			blink_ms(1250);
		}
		
		
		previousStateButton = Reading;		
	}
	return 1;
}