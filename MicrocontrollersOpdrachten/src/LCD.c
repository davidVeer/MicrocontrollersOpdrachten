#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

void _delay_ms(double __ms);

// Clear the LCD and return the cursor to the home position
void lcd_clear(void) {
	lcd_write_command (0x01);						//Leeg display
	_delay_ms(2);
	lcd_write_command (0x02);						//Cursor terug naar start
}

// Set a specific bit in PORTA
void sbi_porta(int index){
	PORTA |= (1<<index);
}

// Clear a specific bit in PORTA
void cbi_porta(int index){
	PORTA &= ~(1<<index);
}

// Strobe the LCD enable pin to latch data
void lcd_strobe_lcd_e(void) { 
	sbi_porta(LCD_E);	// E high
	_delay_ms(1);
	cbi_porta(LCD_E);  	// E low
	_delay_ms(1);
}

// Initialize the LCD in 4-bit mode
void init_4bits_mode(void) {	
	// Init I/O
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;
	
	DDRD = 0xFF;
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;
	
	PORTC = 0x20;	// function for 4-bit 1 row
	lcd_strobe_lcd_e();

	PORTC = 0x20;   // function high nibble 4-bit 2 row
	lcd_strobe_lcd_e();
	PORTC = 0x80;	// function low nibble 4-bit 2 row
	lcd_strobe_lcd_e();

	PORTC = 0x00;   // function high nibble turn on visible blinking-block cursor
	lcd_strobe_lcd_e();
	PORTC = 0xF0;   // function low nibble turn on visible blinking-block cursor
	lcd_strobe_lcd_e();

	PORTC = 0x00;   // Entry mode set high nibble
	lcd_strobe_lcd_e();
	PORTC = 0x60;	// Entry mode set low nibble
	lcd_strobe_lcd_e();
	
	// return home
	lcd_write_command(0x02);
	lcd_strobe_lcd_e();
}

void lcd_write_command(unsigned char byte){
	
	//upper nibble
	PORTC = byte;
	cbi_porta(LCD_RS);
	lcd_strobe_lcd_e();
	
	//lower nibble
	PORTC = (byte<<4);
	cbi_porta(LCD_RS);
	lcd_strobe_lcd_e();

}

void lcd_write_string(const char *str) {
	
	for(;*str; str++){
		lcd_write_character(*str);
	}
}

void lcd_write_character(unsigned char byte){
	
	//upper nibble
	PORTC = byte;
	sbi_porta(LCD_RS);
	lcd_strobe_lcd_e();
	
	//lower nibble
	PORTC = (byte<<4);
	sbi_porta(LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_write_number(unsigned int number){
	char buffer[10];
	itoa(number, buffer, 10); // Convert number to string in base 10
	lcd_write_string(buffer);
}

// Initialize and clear the LCD
void lcd_setup(void) {
	init_4bits_mode();
	_delay_ms(5);
	lcd_clear();
	_delay_ms(5);
}
