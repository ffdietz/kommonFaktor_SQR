#include "pinout.h"
#include "shiftRegister.h"

ShiftRegister::ShiftRegister() 
{
  pinMode(REGISTER_MOSI, OUTPUT);
  pinMode(REGISTER_SCK, OUTPUT);
  pinMode(REGISTER_LATCH, OUTPUT);

  pinMode(STEPS_INPUT, INPUT);
}

void ShiftRegister::begin(){
  digitalWrite(REGISTER_LATCH, LOW);
    shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, 0);
    shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, 0);
  digitalWrite(REGISTER_LATCH, HIGH);
}

void ShiftRegister::output(byte value){
  outputState = value;
}

byte ShiftRegister::check(){
  const  uint32_t debounceDelay = 8;
  static uint8_t prevState = LOW;
  static uint32_t lastChange = 0;
  uint8_t currentState;
  uint8_t output = 0;
  uint8_t shifter = 1 << 0;

  for (uint8_t j = 0; j < 8; j++){
    digitalWrite(REGISTER_LATCH, LOW);
      shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, outputState);
      shiftOut(REGISTER_MOSI, REGISTER_SCK, MSBFIRST, shifter);
    digitalWrite(REGISTER_LATCH, HIGH);

    currentState = digitalRead(STEPS_INPUT);

    if(currentState == HIGH && prevState == LOW){
      if(millis() - lastChange >= debounceDelay ){
        isKeyPressed = true;
        keyPressed = j;
        output ^= (1 << keyPressed);
      } else isKeyPressed = false;
      lastChange = millis();
    }

    prevState = currentState;
    shifter <<= 1;
  }
  return output;
}

bool ShiftRegister::locked(){
  return lock = true;
}
bool ShiftRegister::unlocked(){
  return lock = false;
}

