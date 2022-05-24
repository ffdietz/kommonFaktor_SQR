#include <Arduino.h>
//  Name    : shiftOutCode, Hello World
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis

int latchPin  = 2; //Pin connected to ST_CP of 74HC595
int clockPin  = 3;  //Pin connected to SH_CP of 74HC595
int dataPin   = 4;   //Pin connected to DS of 74HC595

void shiftRegister_init() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void shiftRegister_test(boolean state) {
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    if(!state){
      shiftOut(dataPin, clockPin, MSBFIRST, 255);
      shiftOut(dataPin, clockPin, MSBFIRST, 255);
    }
    else {
      shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
      shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);  
    }
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    // delay(100);
  }
}