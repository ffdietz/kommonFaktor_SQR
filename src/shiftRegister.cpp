#include <Arduino.h>
#include <SPI.h>
#include "pinout.h"
#include "shiftRegister.h"

ShiftReg::ShiftReg()
{
  //SETTING PINS
  // pinMode(SHR_STEP_BUTTONS_SCK, output);//clock
  // pinMode(SHR_STEP_BUTTONS_MOSI, output);//data
  // pinMode(SHIFT_REG_LATCH_STEP_CTRL, OUTPUT);//latch
  // pinMode(STEP_CTRL_INPUT, INPUT);//Input from buttons

//   attachInterrupt(0, pin_read, RISING); 
  
//   DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
//   DDRD |= (1 << SHR_CLOCK);
//   DDRD |= (1 << SHR_DATA);
}

void ShiftReg::begin(){
  // pinMode(13, OUTPUT);//clock
  // pinMode(11, OUTPUT);//data
  pinMode(SHIFT_REG_LATCH_STEP_CTRL, OUTPUT);//latch
  pinMode(STEP_CTRL_INPUT, INPUT);//Input from buttons

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(255);
    SPI.transfer(0);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
//  attachInterrupt(0, pin_read, RISING); 
}

void ShiftReg::read()
{
  check = 1;
  for(j = 0; j < 8; j++)
  {
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(output);
    SPI.transfer(check);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);

    if(digitalRead(STEP_CTRL_INPUT) == HIGH)
    {
      if(bitRead(output, j) == 1) 
        bitWrite(output, j, 0);
      else 
        bitWrite(output, j, 1);
    }
    
    check = check << 1;
  }

}

void ShiftReg::out(int value)
{
  uint8_t result = 1 << value; 
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
  SPI.transfer(result);
  SPI.transfer(255);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}