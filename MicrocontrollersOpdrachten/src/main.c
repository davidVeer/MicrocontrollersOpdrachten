#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>   // voor itoa()
#include "OpdrachtenWeek1/Headers/WeekEenB.h"

// Pas dit aan naar het kanaal waarop de LM35 daadwerkelijk is aangesloten
#define LM35_ADC_KANAAL 0

void adc_init_lm35(void){
	// Prescaler = 64 -> ADC-klok = 8MHz/64 = 125kHz (binnen 50-200kHz bereik)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);

	// Interne 2,56V referentie: REFS1 = 1, REFS0 = 1
	ADMUX |= (1 << REFS1) | (1 << REFS0);

	// 8-bit resultaat: links uitgelijnd, alleen ADCH nodig
	ADMUX |= (1 << ADLAR);

	// Kanaal selecteren (LM35_ADC_KANAAL, bijv. kanaal 0)
	ADMUX = (ADMUX & 0xE0) | (LM35_ADC_KANAAL & 0x1F);

	// ADC inschakelen (single conversion: ADFR blijft uit)
	ADCSRA |= (1 << ADEN);
}

// Start één conversie, wacht tot hij klaar is, geeft de 8-bit ADC-waarde
// terug. Dankzij de rekenkern hierboven is dit direct de temperatuur in °C.
unsigned char lm35_lees_temperatuur(void){
	ADCSRA |= (1 << ADSC);              // start conversie

	while(ADCSRA & (1 << ADSC)){        // wacht tot conversie klaar is
		// niets doen
	}

	return ADCH;                        // 8-bit resultaat = temperatuur in °C
}

// Toont de temperatuur als getal + eenheid op het LCD.
void lcd_toon_temperatuur(unsigned char temp_c){
	char buffer[8];

	lcd_write_command(0x02); // cursor terug naar begin (home)
	lcd_write_string("Temp: ");

	itoa(temp_c, buffer, 10);
	lcd_write_string(buffer);
	lcd_write_string(" C   "); // spaties overschrijven oude, langere waarden
}

int main(void){
	Two_AlternateLedBlinks();
}