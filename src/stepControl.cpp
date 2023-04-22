#include <Arduino.h>
#include <SPI.h>

#include "stepControl.h"
#include "pinout.h"

StepControl::StepControl()
{
  pinMode(SHIFT_REG_LATCH_STEP_CTRL, OUTPUT);   //latch
  pinMode(STEP_CTRL_INPUT, INPUT);  //Input from buttons
}

void StepControl::begin(){

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  SPI.begin();
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(0);
    SPI.transfer(255);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}

void StepControl::check()
{
  
  static int prevState = LOW;
  static int currentState = LOW;

  for(int j = 0; j < 8; j++)
  {
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(output);
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
  
  // write(output);
}

void StepControl::write(byte value)
{
  uint8_t result = 1 << value;  //convert value in power of 2
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
  SPI.transfer(result);
  SPI.transfer(255);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}


  //SETTING PINS
  // pinMode(SHR_STEP_BUTTONS_SCK, output);//clock
  // pinMode(SHR_STEP_BUTTONS_MOSI, output);//data
  // pinMode(SHIFT_REG_LATCH_STEP_CTRL, OUTPUT);//latch
  // pinMode(STEP_CTRL_INPUT, INPUT);//Input from buttons

//   DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
//   DDRD |= (1 << SHR_CLOCK);
//   DDRD |= (1 << SHR_DATA);