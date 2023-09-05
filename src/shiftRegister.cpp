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

unsigned long previousMillis = 0;
const long interval = 20;
byte ShiftRegister::check(){
  output = 0;
  static byte prevState = LOW;
  byte currentState;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
  for (int j = 0; j < 8; j++){
    digitalWrite(REGISTER_LATCH_BTNS, LOW);
      shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, keepValueOutput);
      shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, shifter);
    digitalWrite(REGISTER_LATCH_BTNS, HIGH);

    currentState = digitalRead(BTNS_INPUT);
      // if (currentState == HIGH && prevState == LOW)

    if(currentState)
    {
      int a = (1 << j);
      output = output | a;
      // output ^= (1 << j); // toggle bit in position j
    }

    shifter <<= 1;
  }
  }
  shifter |= 1;
  prevState = currentState;


  return output;
}
