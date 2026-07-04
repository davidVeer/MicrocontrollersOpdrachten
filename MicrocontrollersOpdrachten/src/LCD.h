#ifndef LCD_H_
#define LCD_H_

#define LCD_E 	6
#define LCD_RS	4

void _delay_ms(double __ms);
void lcd_setup(void);
void lcd_clear(void);
void lcd_write_string(const char *str);
void lcd_write_character(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_write_number(unsigned int number);

#endif /* LCD_H_ */