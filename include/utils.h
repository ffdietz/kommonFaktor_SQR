#include <Arduino.h>

#ifndef UTILS_H_
#define UTILS_H_

#define serial(label, value) Serial.print(label); Serial.print(value); Serial.print("  ");

// void printByte(byte b)
// {
//   for(int i = 7; i >= 0; i--)
//     Serial.print(bitRead(b,i));
// }

// int serialInput()
// {
//   static int input = 0;
  
//     if (Serial.available()) {
//       input = Serial.parseInt();
//       Serial.print("serial input: ");
//       Serial.println(input);
//     }

//     return input;
// }

#endif