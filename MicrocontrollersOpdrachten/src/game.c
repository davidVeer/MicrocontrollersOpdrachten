#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "game.h"
#include "LCD.h"
#include "led.h"
#include "button.h"
#include <stdbool.h>

int score = 0; 
volatile uint8_t current_position; // Current position of the active LED;
bool restart = false;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );
	}
}

void spawn_new_led(void) {
    // Generate time between LED's
    wait(rand() % 10 * 100);

    // Turn on the new LED
    current_position = LED_COUNT;
    TurnLedOn(leds[0].port, leds[0].pin);
}

// Initialize the game by setting up the LCD and LEDs
void game_init(void) {
    lcd_setup();
    init_leds();
    lcd_write_string("Starting Game...");
}   

// Main game loop
void game_run(void) {
        game_display_score();
        spawn_new_led();

        for(int i = 1; i < LED_COUNT; i++){
            _delay_ms(400);
		    TurnLedOn(leds[i].port, leds[i].pin);
            current_position++;
		}
        _delay_ms(500); // Time to press 

        if(!restart){
            game_over();
        } 

        restart=false;
        score++;
        for(int i = LED_COUNT; i >= 0; i--){
            _delay_ms(100);
		    TurnLedOff(leds[i].port, leds[i].pin);
		}
}

// Display the game over message on the LCD
void game_over(void) {
    lcd_clear();
    lcd_write_string("Game Over!!");
    // TODO: Print the final score on second line

    while(1){
        // Blink all LEDs to indicate game over
        for(int i = 0; i < LED_COUNT; i++){
            TurnLedOn(leds[i].port, leds[i].pin);
        }
        _delay_ms(100);
        for(int i = 0; i < LED_COUNT; i++){
            TurnLedOff(leds[i].port, leds[i].pin);
        }
        _delay_ms(100);
    }
}

// Display the current score on the LCD
void game_display_score(void) {
    // Display the score on the LCD
    lcd_clear();
    lcd_write_string("Score: ");
    lcd_write_number(score);
}

void button_pressed(){
    // if (current_position == 5){
        restart=true;
    // } else{
    //     restart = false;
    // }
}
