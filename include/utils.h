#include <Arduino.h>

#ifndef utils_h
#define utils_h

#define serial(label, value) Serial.print(label); Serial.print(value); Serial.print(" ")

void printByte(byte b)
{
  for(int i = 7; i >= 0; i--)
    Serial.print(bitRead(b,i));
}

int serialInput()
{
  static int input = 0;
  
    if (Serial.available() > 0) {
      input = Serial.parseInt();
    }
  return input;
}

#endif