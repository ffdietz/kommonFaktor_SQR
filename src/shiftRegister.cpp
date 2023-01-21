#include <Arduino.h>
#include "pinout.h"
#include "shiftRegister.h"


ShiftRegister::ShiftRegister()
{
  //SETTING PINS
  // pinMode(SHR_STEP_BUTTONS_SCK, output);//clock
  // pinMode(SHR_STEP_BUTTONS_MOSI, output);//data
  pinMode(SHIFT_REG_LATCH_STEP_CTRL, output);//latch
  pinMode(A5, INPUT);//Input from buttons

  // attachInterrupt(0, pin_read, RISING); 
  
  // DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
  // DDRD |= (1 << SHR_CLOCK);
  // DDRD |= (1 << SHR_DATA);
}

void ShiftRegister::begin(){
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
  SPI.transfer(0);
  SPI.transfer(0);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
}

void ShiftRegister::pinRead()
{
  // for(int j=0; j<50; j++) delayMicroseconds(1000);
  check=1;
  // for(int j=0; j<8; j++)
  // {
  //   SPI.transfer(check);
  //   SPI.transfer(output);
  //   digitalWrite(SHR_STEP_BUTTONS_LATCH, HIGH);
  //   digitalWrite(SHR_STEP_BUTTONS_LATCH, LOW);
  //   // delayMicroseconds(500);
  //   if(digitalRead(A5) == HIGH)
  //     bitWrite(output, j, 1);
  //   else 
  //     bitWrite(output, j, 0);
  //   check = check<<1;
  // }
    
  SPI.transfer(255);
  SPI.transfer(output);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, HIGH);
  digitalWrite(SHIFT_REG_LATCH_STEP_CTRL, LOW);
 
  // Serial.println(output);
}

// };

// void ShiftRegister::clearRegister()
// {
//     /*Clear the registers*/
//   PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
//     this->bitPrint(0);
//     this->bitPrint(0);
//   PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
// }

// void ShiftRegister::bitPrint(byte  data)
// {
//   shiftOut(SHR_DATA, SHR_CLOCK, MSBFIRST, data);
// }

// void ShiftRegister::bitLatch()
// {
//   PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
//   PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
// }

// void ShiftRegister::update()
// {
//   PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
//     this->bitPrint(shifter);
//     this->bitPrint(position_out);
//   PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
// }

// uint8_t ShiftRegister::getPosition()
// {
//   return position - 1;
// }

// void ShiftRegister::setPositionOut()
// {
//   position_out ^= (1 << (position - 1)); // XOR to toggle the bit 
// }

// void ShiftRegister::bitShifter()
// {
//   this->shifter = (1 << this->position );
//   this->position++; 

//   if(this->position > 8) 
//   {
//     this->position = 1;
//     this->shifter = 1;
//   }
// }


// byte Input, Output, Check = 1;
// void pin_read()
// {
//   // for(int j=0; j<50; j++) delayMicroseconds(1000);
//   Check=1;

//   for(int j=0; j<8; j++)
//   {
//     shiftRegister_bit_out(Check);
//     shiftRegister_bit_out(Output);
//     digitalWrite(SHR_LATCH, HIGH);
//     digitalWrite(SHR_LATCH, LOW);
//     delayMicroseconds(500);
    
//     if(digitalRead(2)==HIGH) bitWrite(Output, j, 1);
//     else bitWrite(Output, j, 0);

//     Check = Check<<1;
//   }

//   shiftRegister_bit_out(255);
//   shiftRegister_bit_out(Output);
//   digitalWrite(SHR_LATCH, HIGH);
//   digitalWrite(SHR_LATCH, LOW);

//   // Serial.println(Output);
// }