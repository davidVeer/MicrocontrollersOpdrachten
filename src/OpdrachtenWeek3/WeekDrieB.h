#ifndef WEEK_DRIE_B
#define WEEK_DRIE_B

volatile unsigned int count;
#define BIT(x)  (1 << (x))
#define OCR2_HIGH_15MS   500
#define OCR2_LOW_25MS    1000

void One_Counter();
void Two_Timer();

#endif