#include <stdio.h>


int main( void ) {
	
	int lookuptable[2][8] = {
		{0b00000001,0b00000011,0b000000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111},
		{0b10000001,0b01000010,0b001000100,0b00101000,0b00010000,0b00111000,0b01111110,0b11111111}
	};
	
	for(;;) {
		for (int j = 0; j < 2; j++){
			for(int i = 0; i < 8; i++){
			
				printf("%d ", lookuptable[j][i]);
			}	
			
		}
		
		
	}

	return 1;
}