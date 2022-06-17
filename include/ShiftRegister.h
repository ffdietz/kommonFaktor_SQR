#include <Arduino.h>
#include <SPI.h> 

// #include "DebounceInput.h"

// DebouncedInput Button;

#define SHR_LATCH 5  //to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 6  //to 74HC595 SH_CP [PIN 11]
#define SHR_DATA  7  //to 74HC595 DS    [PIN 14]
// #define PIN_READ  4  //ATMEGA PIN TO READ

byte position = 1;
byte shifter  = 1;
byte position_out = 0;

void shiftRegister_bit_out(byte  data)
{
  shiftOut(SHR_DATA, SHR_CLOCK, MSBFIRST, data);
}

void shiftRegister_begin()
{ 
  //SETTING PINS
  DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
  DDRD |= (1 << SHR_CLOCK);
  DDRD |= (1 << SHR_DATA);

  // DDRD &= ~(1 << PIN_READ); //"AND INVERT 1" OPERATOR SET LOW

  PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
    shiftRegister_bit_out(0);
    shiftRegister_bit_out(0);
  PORTD |= (1 << SHR_LATCH );   //LATCH HIGH

}

void shiftRegister_latching()
{
  PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
  PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
}

void shiftRegister_update()
{
  PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
    shiftRegister_bit_out(shifter);
    shiftRegister_bit_out(position_out);
  PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
}

uint8_t shiftRegister_position()
{
  return position - 1;
}

void shiftRegister_set_position()
{
  position_out ^= (1 << (position - 1)); // XOR to toggle the bit 
}


void shiftRegister_shifter()
{
  shifter = (1 << position );
  position++; 

  if(position > 8) 
  {
    position = 1;
    shifter = 1;
  }
}

void shiftRegister_serial_print()
{
  // Serial.print(" button.read: ");
  // Serial.print(Button.read());
  // Serial.print(" position: ");
  // Serial.print(position);
  Serial.print(" shifter: ");
  Serial.print(shifter);
  // Serial.print(" position_out: ");
  // Serial.println(position_out, BIN);
  Serial.println();
}


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