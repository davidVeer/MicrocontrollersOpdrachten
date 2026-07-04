#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Headers/WeekDrieB.h"
#include "SupportModules/LCD/Headers/LCD.h"


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

void timer2Init(void){
	TCNT2 = 0;                 // teller start op 0
	OCR2  = OCR2_HIGH_15MS;    // eerste periode: 15 ms

	TCCR2 = (1<<WGM21) |                       // CTC-mode (reset TCNT2 bij compare match)
	        (1<<CS22) | (1<<CS21) | (1<<CS20); // prescaler 1024

	TIMSK |= (1<<OCIE2);       // Timer2 Compare Match interrupt enable

	sei();
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

void One_Counter(){
    unsigned int last_shown = 0xFFFF; // forceer eerste update

	init_4bits_mode();
		
	_delay_ms(10);
		
	lcd_clear();
		
	_delay_ms(10); // gives clear time to process 

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
}

void Two_Timer(){
    DDRD |= BIT(7);   // PORTD.7 als output
	PORTD &= ~BIT(7); // start laag

	timer2Init();

	for(;;){
		// alles gebeurt in de ISR, main blijft leeg
	}
}