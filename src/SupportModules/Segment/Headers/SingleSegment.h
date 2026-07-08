#ifndef SINGLE_SEGMENT_H
#define SINGLE_SEGMENT_H
#include <avr/io.h>


void setDisplayNumber(volatile uint8_t* port, int num);
void setDisplay(volatile uint8_t* port, uint8_t bitmask);

#endif