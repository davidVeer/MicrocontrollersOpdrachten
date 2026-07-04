#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// ---------------------------------------------------------------------
// ADC init: kanaal 3, 8-bit resultaat (ADLAR=1), Vref=AVCC,
// prescaler 64 (125kHz). GEEN free-running: elke conversie moet
// handmatig gestart worden door ADSC te zetten.
// ---------------------------------------------------------------------
void adc_init_single_conversion_ch3(void){
	// Prescaler = 64 -> ADC-klok = 8MHz/64 = 125kHz (binnen 50-200kHz bereik)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);

	// Referentiespanning = AVCC
	ADMUX |= (1 << REFS0);

	// 8-bit resultaat: links uitgelijnd, alleen ADCH nodig
	ADMUX |= (1 << ADLAR);

	// Kanaal 3 selecteren: MUX4:0 = 00011
	ADMUX &= ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2));
	ADMUX |=  (1<<MUX1) | (1<<MUX0);

	// LET OP: ADFR wordt NIET gezet -> single conversion mode (op aanvraag)

	// ADC inschakelen (nog geen conversie starten)
	ADCSRA |= (1 << ADEN);
}

// Start één conversie, wacht tot hij klaar is, en geeft de 8-bit uitkomst terug.
unsigned char adc_read_ch3_8bit(void){
	// Start de conversie
	ADCSRA |= (1 << ADSC);

	// Wacht tot de conversie klaar is: ADSC wordt door hardware
	// automatisch weer op 0 gezet zodra de conversie voltooid is
	while(ADCSRA & (1 << ADSC)){
		// niets doen, gewoon wachten
	}

	// 8-bit resultaat staat door ADLAR=1 direct in ADCH
	return ADCH;
}

int main(void){
	DDRA = 0xFF;   // PORTA volledig output (bijv. om resultaat te tonen op LED's)
	PORTA = 0x00;

	adc_init_single_conversion_ch3();

	for(;;){
		// Eén conversie op aanvraag uitvoeren en resultaat ophalen
		unsigned char waarde = adc_read_ch3_8bit();

		// Gebruik de waarde, bijv. tonen op LED's van PORTA
		PORTA = waarde;

		// Wachtfunctie: bepaalt hoe vaak je "op aanvraag" een nieuwe meting doet
		_delay_ms(500);
	}
}