#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> 
#include "game.h"
#include "button.h"
#include "led.h"

int main(void){
	game_init();
	_delay_ms(3000);
	game_run();
	game_over();

	while(1){
		
	}
	
}