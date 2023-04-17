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

//   DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
//   DDRD |= (1 << SHR_CLOCK);
//   DDRD |= (1 << SHR_DATA);
}

void ShiftReg::begin(){
  pinMode(SHIFT_REG_LATCH_STEP_CTRL, OUTPUT);   //latch
  pinMode(STEP_CTRL_INPUT, INPUT);  //Input from buttons

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(255);
    SPI.transfer(0);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}

void ShiftReg::read()
{
  for(int j = 0; j < 8; j++){
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
    SPI.transfer(output);
    SPI.transfer(check);
    digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
    
    if(digitalRead(STEP_CTRL_INPUT)== HIGH) 
    {
      output ^= (1 << j); // toggle bit in position j
    }
    
    Serial.print("  j ");     Serial.print(j);
    Serial.print("  output ");  Serial.print(output);
    Serial.println();

    check <<= 1;
  }
  check |= 1;

  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
  SPI.transfer(output);
  SPI.transfer(255);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);

}

void ShiftReg::out(int value)
{
  uint8_t result = 1 << value;  //convert value in power of 2
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
  SPI.transfer(result);
  SPI.transfer(255);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
}