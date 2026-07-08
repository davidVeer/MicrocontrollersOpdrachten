#include <avr/io.h>
#include <stdlib.h>   // voor itoa()
#include <util/delay.h>
#include "OpdrachtenWeek4/WeekVierB.h"


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

void adc_init_free_running(void){
    // B: Prescaler = 64 -> ADC-klok = 125 kHz (binnen 50-200 kHz bereik)
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1);

    // C: Referentiespanning = AVCC
    ADMUX |= (1 << REFS0);

    // D: Resultaat links uitgelijnd (8-bit lezen via ADCH)
    ADMUX |= (1 << ADLAR);

    // E: Kanaal ADC0 selecteren
    ADMUX &= ~((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));

    // F: Free-running mode aan
    ADCSRA |= (1 << ADFR);

    // G: ADC inschakelen
    ADCSRA |= (1 << ADEN);

    // H: Start de conversiecyclus (start automatisch continu door na elke conversie)
    ADCSRA |= (1 << ADSC);
}

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


void One_ADC(){
    adc_init_free_running();

    for(;;){
        // ADCH bevat continu de meest recente 8-bit ADC-waarde,
        // bijgewerkt door de hardware zonder verdere tussenkomst.
        unsigned char waarde = ADCH;

        // gebruik 'waarde' hier, bijv. weergeven op LCD of LED's
    }
}

void Two_ADC_10Bits(){
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

void Three_ADC_8bits(){
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

void Four_ADC_Temperature(){
    DDRA = 0xFF;   // PORTA volledig output -> LED's tonen ADCH
	PORTA = 0x00;

	init_4bits_mode();
	_delay_ms(10);
	lcd_clear();
	_delay_ms(10);

	adc_init_lm35();

	for(;;){
		unsigned char temperatuur = lm35_lees_temperatuur();

		// Waarde van ADCH tonen op de LED's van PORTA
		PORTA = temperatuur;

		// Temperatuur tonen op het LCD
		lcd_toon_temperatuur(temperatuur);

		_delay_ms(500); // wachtfunctie: bepaalt de meetfrequentie
	}
}
