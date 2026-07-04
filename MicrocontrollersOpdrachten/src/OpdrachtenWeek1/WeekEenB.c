#include "..\SupportModules\LED\Headers\LED.h"
#include "Headers/WeekEenB.h"

#include <util/delay.h>

void Two_AlternateLedBlinks(){
    TurnLedOn(&PORTA,0);

    _delay_ms(1000);

    TurnLedOff(&PORTA,0);

    _delay_ms(1000);

    TurnLedOn(&PORTA,0);
}

void Three_BlinkWithButton(){

}

void Four_Basic_LED_Pattern(){

}

void Five_Lookup_LED_Pattern(){

}

void Six_BlinkStates(){

}
