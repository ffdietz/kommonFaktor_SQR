#include <Arduino.h>

#ifndef utils_h
#define utils_h

void printByte(byte b)
{
  for(int i = 7; i >= 0; i--)
    Serial.print(bitRead(b,i));
  Serial.println();  
}

#endif