#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include "game.h"
#include "LCD.h"

int score = 0; // Global variable to keep track of the score
void _delay_ms(double __ms);
bool GameIsRunning = true;

void game_init(void) {
    lcd_setup();
    lcd_write_string("Starting Game...");
}   

void game_run(void) {
    // Main game loop

    while (GameIsRunning) {
        // Game logic and input handling

        game_display_score();
        score++; // Testing purpose only
        _delay_ms(1000); 

        if (score == 5) { // Example condition to end the game
            GameIsRunning = false;
        }
    }
}

void game_over(void) {
    lcd_clear();
    lcd_write_string("Game Over!!");
    // TODO: Print the final score on second line
}

void game_display_score(void) {
    // Display the score on the LCD
    lcd_clear();
    lcd_write_string("Score: ");
    lcd_write_number(score);
}
