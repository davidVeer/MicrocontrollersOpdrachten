#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"

volatile unsigned int count = 0;

void init_tc2_counter(void){
	// T2-pin (PD7) als input met pull-up, dit is de externe klokbron voor TC2
	DDRD &= ~(1 << PD7);
	PORTD |= (1 << PD7);

	TCNT2 = 0;                              // teller starten op 0

	// Counter mode: externe klok op T2, tellen op stijgende flank
	TCCR2 = (1 << CS22) | (1 << CS21) | (1 << CS20);

	TIMSK |= (1 << TOIE2);                  // overflow interrupt aan (voor >255 toetsdrukken)

	sei();
}

ISR(TIMER2_OVF_vect){
	count += 256; // TCNT2 loopt over na 255 -> 256 tellingen bijtellen
}

unsigned int get_total_count(void){
	unsigned int total;
	unsigned char tcnt_snapshot;

	cli();
	tcnt_snapshot = TCNT2;
	total = count + tcnt_snapshot;
	sei();

	return total;
}

int main( void ) {
	unsigned int last_shown = 0xFFFF; // forceer eerste update

	init_4bits_mode();
		
	_delay_ms(10);
		
	lcd_clear();
		
	_delay_ms(10); // gives clear time to process 
		
	lcd_write_string("Druk teller:");

	init_tc2_counter();

	for(;;) {	
		unsigned int current = get_total_count();

			if(current != last_shown){
			lcd_write_command(0x02); // cursor terug naar begin regel (home)
			lcd_write_string("Druk teller:");
			lcd_write_number(current);
			last_shown = current;
			}
		
	}
	return 1;
}
