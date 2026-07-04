#ifndef WEEK_TWEE_B
#define WEEK_TWEE_B

int bitshift;

#define SEG_A 0b00000001
#define SEG_B 0b00000010
#define SEG_C 0b00000100
#define SEG_D 0b00001000
#define SEG_E 0b00010000
#define SEG_F 0b00100000
#define SEG_G 0b01000000

typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

void One_Interupt();
void Two_Multiple_Interupts();
void Three_Segment_Display();
void Four_Segment_Display_Animation();
void Five_LCD_Module();

#endif