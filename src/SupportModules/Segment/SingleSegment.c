#include "Headers/SingleSegment.h"
#include "SupportModules/PinHandling/Headers/PinHandling.h"

const unsigned char Character_Register[16] = {
0b00111111, //0
0b00000110, //1
0b01011011, //2
0b01001111, //3
0b01100110, //4
0b01101101, //5
0b01111101, //6
0b00000111, //7
0b01111111, //8
0b01101111, //9
0b01110111, //a
0b01111100, //b
0b00111001, //c
0b01011110, //d
0b01111001, //e
0b01110001  //f
};

void setDisplayNumber(volatile uint8_t* port, int num){
	if(num > 15 || num < 0){
		setPort(port, Character_Register[14]);
		} else {
		setPort(port, Character_Register[num]);
	}
}

void setDisplay(volatile uint8_t* port, uint8_t bitmask){
    setPort(port,bitmask);
}