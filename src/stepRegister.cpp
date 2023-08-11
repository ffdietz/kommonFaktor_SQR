#include <Arduino.h>
#include <SPI.h>

#include "pinout.h"
#include "stepRegister.h"

StepRegister::StepRegister()
{
  pinMode(REGISTER_LATCH_BTNS, OUTPUT);   //latch
  pinMode(BTNS_INPUT, INPUT);  //Input from buttons
}

void StepRegister::begin(){

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  SPI.begin();
    digitalWrite(REGISTER_LATCH_BTNS, LOW);
    SPI.transfer(0);
    SPI.transfer(0);
    digitalWrite(REGISTER_LATCH_BTNS, HIGH);
}

void StepRegister::keepOutputValue(byte value){
  keepValueOutput = value;
}

byte StepRegister::check()
{
  output = 0;
  static int prevState = LOW;
  static int currentState = LOW;
  
  for(int j = 0; j < 8; j++)
  {
    digitalWrite(REGISTER_LATCH_BTNS, LOW);
    SPI.transfer(keepValueOutput);
    SPI.transfer(shifter);
    digitalWrite(REGISTER_LATCH_BTNS, HIGH);

    currentState = digitalRead(BTNS_INPUT);

    if(currentState == HIGH && prevState == LOW)
    {
      output ^= (1 << j);   // toggle bit in position j
    }
    shifter <<= 1;
  }
  shifter |= 1;
  prevState = currentState;
  
  return output;
}

void StepRegister::write(byte value)
{
  digitalWrite(REGISTER_LATCH_BTNS, LOW);
  SPI.transfer(value);
  SPI.transfer(0);
  digitalWrite(REGISTER_LATCH_BTNS, HIGH);
}