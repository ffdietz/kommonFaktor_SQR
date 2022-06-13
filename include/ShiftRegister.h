#include <Arduino.h>
#include <SPI.h> 

#define SHR_LATCH 5  //to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 6  //to 74HC595 SH_CP [PIN 11]
#define SHR_DATA  7  //to 74HC595 DS    [PIN 14]
#define PIN_READ  4  //ATMEGA PIN TO READ

void shiftRegister_bit_out(byte  data)
{
  shiftOut(SHR_DATA, SHR_CLOCK, MSBFIRST, data);
}

void shiftRegister_begin()
{ //SETTING PINS
  DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
  DDRD |= (1 << SHR_CLOCK);
  DDRD |= (1 << SHR_DATA);

  DDRD &= ~(1 << PIN_READ); //"AND INVERT 1" OPERATOR SET LOW

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

void shiftRegister_test(uint8_t velocity)
{
  shiftRegister_bit_out(1 << millis()/velocity % 8);
  shiftRegister_latching();
}

byte Input, Output, Check = 1;
void pin_read()
{
  // for(int j=0; j<50; j++) delayMicroseconds(1000);
  Check=1;

  for(int j=0; j<8; j++)
  {
    shiftRegister_bit_out(Check);
    shiftRegister_bit_out(Output);
    digitalWrite(SHR_LATCH, HIGH);
    digitalWrite(SHR_LATCH, LOW);
    delayMicroseconds(500);
    
    if(digitalRead(2)==HIGH) bitWrite(Output, j, 1);
    else bitWrite(Output, j, 0);

    Check = Check<<1;
  }

  shiftRegister_bit_out(255);
  shiftRegister_bit_out(Output);
  digitalWrite(SHR_LATCH, HIGH);
  digitalWrite(SHR_LATCH, LOW);

  // Serial.println(Output);
}


uint8_t position = 1;
uint8_t shifter = 1;
void ShiftRegister_update()
{
    if(position > 8) 
    {
      position = 1;
      shifter = 1;
    }

    PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
      shiftRegister_bit_out(shifter);
      shiftRegister_bit_out(position);
    PORTD |= (1 << SHR_LATCH );   //LATCH HIGH

    shifter = (1 << position );
    position++; 

  if(digitalRead(4))   Serial.println(position-1);

}

uint8_t Shiftregister_position()
{
  return position - 1;
}