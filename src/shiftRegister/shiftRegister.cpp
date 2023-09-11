#include <Arduino.h>
#include "pinout.h"
#include "shiftRegister.h"

ShiftRegister::ShiftRegister() 
{
  pinMode(REGISTER_MOSI, OUTPUT);
  pinMode(REGISTER_SCK, OUTPUT);
  pinMode(REGISTER_LATCH_BTNS, OUTPUT);

  pinMode(BTNS_INPUT, INPUT);
}

void ShiftRegister::begin(){
  digitalWrite(REGISTER_LATCH_BTNS, LOW);
    shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, 0);
    shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, 0);
  digitalWrite(REGISTER_LATCH_BTNS, HIGH);
}

void ShiftRegister::write(byte value){
  digitalWrite(REGISTER_LATCH_BTNS, LOW);
    shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, value);
    shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, 0);
  digitalWrite(REGISTER_LATCH_BTNS, HIGH);
}

void ShiftRegister::keepOutputValue(byte value){
  keepValueOutput = value;
}

byte ShiftRegister::check(){
  // static uint8_t prevOut = 0;
  static uint8_t currentState;
  static uint8_t prevState = LOW;
  static uint32_t lastChange = 0;
  const  uint32_t debounceDelay = 8;

  output = 0;

  for (int j = 0; j < 8; j++){
    digitalWrite(REGISTER_LATCH_BTNS, LOW);
      shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, keepValueOutput);
      shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, shifter);
    digitalWrite(REGISTER_LATCH_BTNS, HIGH);

    currentState = digitalRead(BTNS_INPUT);

    if(currentState == HIGH && prevState == LOW) {
      if(millis() - lastChange >= debounceDelay ) {
        output ^= (1 << j);
      }
      lastChange = millis();
    }
    prevState = currentState;
    shifter <<= 1;
  }
  shifter |= 1;

  // prevOut = output;

  return output;
}

// byte ShiftRegister::check(){
//   output = 0;
//   int currentState;

//   for (int j = 0; j < 8; j++){
//     digitalWrite(REGISTER_LATCH_BTNS, LOW);
//       shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, keepValueOutput);
//       shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, shifter);
//     digitalWrite(REGISTER_LATCH_BTNS, HIGH);

//     currentState = digitalRead(BTNS_INPUT);

//     if(currentState){
//       output ^= (1 << j); // toggle bit in position j
//     }
//     shifter <<= 1;
//   }

//   shifter |= 1;

//   return output;
// }

