#include <Arduino.h>
#include <SPI.h>

#include "StepRegister.h"
#include "pinout.h"

StepRegister::StepRegister()
{
  pinMode(SHIFT_REG_LATCH_STEP_CTRL, OUTPUT);   //latch
  pinMode(STEP_CTRL_INPUT, INPUT);  //Input from buttons
}

void StepRegister::begin(){

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  SPI.begin();
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(0);
    SPI.transfer(0);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}

byte StepRegister::check(byte keepOutputValue)
{
  output = 0;
  static int prevState = LOW;
  static int currentState = LOW;
  
  for(int j = 0; j < 8; j++)
  {
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(keepOutputValue);
    SPI.transfer(shifter);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);

    currentState = digitalRead(STEP_CTRL_INPUT);

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
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
  SPI.transfer(value);
  SPI.transfer(0);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}

//  SETTING PINS
//  DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
//  DDRD |= (1 << SHR_CLOCK);
//  DDRD |= (1 << SHR_DATA);