#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> 
#include "game.h"
#include "button.h"
#include "led.h"
#include "avr/interrupt.h"

int main(void){
	init_leds();
	game_init();
	button_init();
	_delay_ms(1000); // Time between start message and game

	while(1){
	game_run();
	_delay_ms(100);
	}

	return 1;
}

ISR(INT0_vect) {
	button_pressed();
}
