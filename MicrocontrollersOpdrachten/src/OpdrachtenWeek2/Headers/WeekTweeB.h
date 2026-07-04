#ifndef WEEK_TWEE_B
#define WEEK_TWEE_B

const unsigned char Characters[16];
int bitshift;
typedef struct {
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

void One_Interupt();
void Two_Multiple_Interupts();
void Three_Segment_Display();
void Four_Segment_Display_Animation();
void Five_LCD_Module();
void setDisplay(int num);

#endif