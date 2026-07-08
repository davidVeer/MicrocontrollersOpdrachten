#include <avr/io.h>
#include <util/delay.h>
#include "SupportModules/LCD/LCD.h"
#include <stdlib.h>
#include "SupportModules/PinHandling/PinHandling.h"

void lcd_clear() {
	lcd_write_command (0x01);						//Leeg display
	_delay_ms(2);
	lcd_write_command (0x02);						//Cursor terug naar start
}

void lcd_strobe_lcd_e(void) {
	SetPin(&PORTA,LCD_E,1);	// E high
	_delay_ms(1);
	SetPin(&PORTA,LCD_E,0); // E low
	_delay_ms(1);
	
}

void init_4bits_mode(void) {
	
	// PORTC output mode and all low (also E and RS pin)
	
	// Init I/O
	
	setPort(&DDRC,0xff);
	setPort(&PORTC,0xFF);


	setPort(&DDRD,0xff);
	setPort(&DDRA,0xff);

	setPort(&PORTC,0x00);
	setPort(&PORTA,0x00);
	
	setPort(&PORTC,0x20);	// function for 4-bit 1 row
	lcd_strobe_lcd_e();

	setPort(&PORTC,0x20);   // function high nibble 4-bit 2 row
	lcd_strobe_lcd_e();
	setPort(&PORTC,0x80);	// function low nibble 4-bit 2 row
	lcd_strobe_lcd_e();

	setPort(&PORTC,0x00);   // function high nibble turn on visible blinking-block cursor
	lcd_strobe_lcd_e();
	setPort(&PORTC,0xF0);   // function low nibble turn on visible blinking-block cursor
	lcd_strobe_lcd_e();

	setPort(&PORTC,0x00);   // Entry mode set high nibble
	lcd_strobe_lcd_e();
	setPort(&PORTC,0x60);	// Entry mode set low nibble
	lcd_strobe_lcd_e();
	
	// return home
	lcd_write_command(0x02);
	lcd_strobe_lcd_e();
}

void lcd_write_command(unsigned char byte){
	
	//upper nibble
	setPort(&PORTC,byte);
	SetPin(&PORTA,LCD_RS,0);
	lcd_strobe_lcd_e();
	
	//lower nibble
	setPort(&PORTC,(byte<<4));
	SetPin(&PORTA,LCD_RS,0);
	lcd_strobe_lcd_e();

}

void lcd_write_string(const char *str) {
	
	for(;*str; str++){
		lcd_write_character(*str);
	}
}


void lcd_write_character(unsigned char byte){
	
	//upper nibble
	setPort(&PORTC,byte);
	SetPin(&PORTA,LCD_RS,1);
	lcd_strobe_lcd_e();
	
	//lower nibble
	setPort(&PORTC,(byte<<4));
	SetPin(&PORTA,LCD_RS,1);
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
