#define F_CPU 8000000UL
#include <avr/io.h>

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

int main(void){
    adc_init_free_running();

    for(;;){
        // ADCH bevat continu de meest recente 8-bit ADC-waarde,
        // bijgewerkt door de hardware zonder verdere tussenkomst.
        unsigned char waarde = ADCH;

        // gebruik 'waarde' hier, bijv. weergeven op LCD of LED's
    }
}