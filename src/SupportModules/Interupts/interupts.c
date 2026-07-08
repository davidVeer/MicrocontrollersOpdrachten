#include "Headers/Interupts.h"
#include "SupportModules/PinHandling/Headers/PinHandling.h"
#include <avr/interrupt.h>

void initInterupts(int EICRA_Settings_mask, int EIMSK_Settings_mask){
 	setPort(&DDRD,0xf0);
    setPort(&DDRE,0xf0);

	EICRA |= EICRA_Settings_mask;	
	EIMSK |= EIMSK_Settings_mask;	
	
	sei();   
}
		