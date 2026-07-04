#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "game.h"
#include "LCD.h"
#include "led.h"

int score = 0; // Global variable to keep track of the score
void _delay_ms(double __ms);
bool GameIsRunning = true;

// Initialize the game by setting up the LCD and LEDs
void game_init(void) {
    lcd_setup();
    init_leds();
    lcd_write_string("Starting Game...");
}   

// Main game loop
void game_run(void) {
    while (GameIsRunning) {
        game_display_score();

        for(int i = 0; i < LED_COUNT; i++){
		    TurnLedOn(leds[i].port, leds[i].pin);
		    _delay_ms(200);
            TurnLedOff(leds[i].port, leds[i].pin);
		}

        score++;
        if (score > 10) { // Example condition to end the game
            GameIsRunning = false;
        }
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
