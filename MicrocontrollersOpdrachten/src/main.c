#define F_CPU 8000000UL
#include <avr/io.h>

// ---------------------------------------------------------------------
// ADC init: kanaal 1, 10-bit (ADLAR=0), Vref=AVCC, prescaler 64 (125kHz),
// free-running mode.
// ---------------------------------------------------------------------
void adc_init_free_running_ch1(void){
	// Prescaler = 64 -> ADC-klok = 8MHz/64 = 125kHz (binnen 50-200kHz bereik)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);

	// Referentiespanning = AVCC
	ADMUX |= (1 << REFS0);

	// ADLAR blijft 0 -> 10-bit resultaat rechts uitgelijnd (ADCL + ADCH samen)

	// Kanaal 1 selecteren: MUX4:0 = 00001
	ADMUX &= ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1));
	ADMUX |=  (1<<MUX0);

	// Free-running mode aan
	ADCSRA |= (1 << ADFR);

	// ADC inschakelen
	ADCSRA |= (1 << ADEN);

	// Start de (continue) conversiecyclus
	ADCSRA |= (1 << ADSC);
}

// Leest de actuele 10-bit ADC-waarde (0-1023).
// ADC is de avr-libc macro die ADCL en ADCH samenvoegt tot één 16-bit waarde.
// Belangrijk: bij 10-bit gebruik (ADLAR=0) altijd eerst ADCL, dan ADCH laten lezen -
// de ADC-macro/registeraccess van avr-libc doet dit al in de juiste volgorde.
unsigned int adc_read(void){
	return ADC;
}

// Zet een 10-bit waarde (0-1023) om naar een bargraph-patroon van 0-16 LED's,
// en verdeelt dat patroon over PORTA (LED 0-7, laag) en PORTB (LED 8-15, hoog).
void toon_bargraph(unsigned int adc_waarde){
	// Schaal 0-1023 naar 0-16: delen door 64 (1024/16 = 64)
	unsigned int aantal_leds_aan = adc_waarde >> 6;   // 0 t/m 16

	// Bitmask met de laagste 'aantal_leds_aan' bits op 1.
	// Voorbeeld: aantal_leds_aan=3 -> 0b0000000000000111
	unsigned int patroon;
	if(aantal_leds_aan >= 16){
		patroon = 0xFFFF;              // alle 16 LED's aan (Vin = Vref)
	} else {
		patroon = (1 << aantal_leds_aan) - 1;
	}

	PORTA = (unsigned char)(patroon & 0xFF);         // LED 0-7
	PORTB = (unsigned char)((patroon >> 8) & 0xFF);  // LED 8-15
}

int main(void){
	DDRA = 0xFF;   // PORTA volledig output (LED's)
	DDRB = 0xFF;   // PORTB volledig output (LED's)
	PORTA = 0x00;  // start: alle LED's uit
	PORTB = 0x00;

	adc_init_free_running_ch1();

	for(;;){
		unsigned int waarde = adc_read();
		toon_bargraph(waarde);
	}
}