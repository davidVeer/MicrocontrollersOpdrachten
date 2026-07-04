#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)  (1 << (x))

// Prescaler 1024 -> tellingen per ms = F_CPU / 1024 / 1000 = 7.8125
// 15 ms -> OCR2 = 15 * 7.8125 ≈ 117
// 25 ms -> OCR2 = 25 * 7.8125 ≈ 195
// Beide waarden passen ruim binnen het 8-bit bereik van OCR2 (max 255).
#define OCR2_HIGH_15MS   117
#define OCR2_LOW_25MS    195

void timer2Init(void){
	TCNT2 = 0;                 // teller start op 0
	OCR2  = OCR2_HIGH_15MS;    // eerste periode: 15 ms

	TCCR2 = (1<<WGM21) |                       // CTC-mode (reset TCNT2 bij compare match)
	        (1<<CS22) | (1<<CS21) | (1<<CS20); // prescaler 1024

	TIMSK |= (1<<OCIE2);       // Timer2 Compare Match interrupt enable

	sei();
}

// Toggelt PORTD.7 bij elke compare match en wisselt de compare-waarde
// zodat de hoog- en laag-tijd afwisselend 15ms en 25ms zijn.
ISR(TIMER2_COMP_vect){
	PORTD ^= BIT(7);

	if(OCR2 == OCR2_HIGH_15MS){
		OCR2 = OCR2_LOW_25MS;
	} else {
		OCR2 = OCR2_HIGH_15MS;
	}
}

int main(void){
	DDRD |= BIT(7);   // PORTD.7 als output
	PORTD &= ~BIT(7); // start laag

	timer2Init();

	for(;;){
		// alles gebeurt in de ISR, main blijft leeg
	}
}