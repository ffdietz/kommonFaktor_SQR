#include <Arduino.h>
#include <SPI.h> 
#include <avdweb_Switch.h>

// #define SHR_LATCH 5  //to 74HC595 ST_CP [PIN 12]
// #define SHR_CLOCK 6  //to 74HC595 SH_CP [PIN 11]
// #define SHR_DATA  7  //to 74HC595 DS    [PIN 14]
// #define PIN_READ  4  //ATMEGA PIN TO READ
#define SHR_LATCH 10  //to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 13  //to 74HC595 SH_CP [PIN 11]
#define SHR_DATA  11  //to 74HC595 DS    [PIN 14]
#define PIN_READ  2  //ATMEGA PIN TO READ

void shiftRegister_begin()
{ //SETTING PINS
  DDRD |= (1 << SHR_LATCH); //"OR 1" OPERATOR SET HIGH
  DDRD |= (1 << SHR_CLOCK);
  DDRD |= (1 << SHR_DATA);

  DDRD &= ~(1 << PIN_READ); //"AND INVERT 1" OPERATOR SET LOW
}

void shiftRegister_latching()
{
  PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
  PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
}

void shiftRegister_bit_out(uint8_t  data)
{
  shiftOut(SHR_DATA, SHR_CLOCK, MSBFIRST, data);
  shiftOut(SHR_DATA, SHR_CLOCK, MSBFIRST, data);
}

void shiftRegister_test(uint8_t velocity)
{
  shiftRegister_bit_out(1 << millis()/velocity % 8);
  shiftRegister_latching();
}

byte Input, Output, Check=1;
int j;
void pin_read()
{
  // for(j=0; j<50; j++) delayMicroseconds(1000);

  Check=1;

  for(j=0; j<8; j++)
  {
    SPI.transfer(Check);
    SPI.transfer(Output);
    digitalWrite(SHR_LATCH, HIGH);
    digitalWrite(SHR_LATCH, LOW);
    // delayMicroseconds(500);
    if(digitalRead(2)==HIGH) bitWrite(Output, j, 1);
    else bitWrite(Output, j, 0);

    Check = Check<<1;
  }

  SPI.transfer(255);
  SPI.transfer(Output);
  digitalWrite(SHR_LATCH, HIGH);
  digitalWrite(SHR_LATCH, LOW);
  Serial.println(Output);
}

void shiftRegister_read_begin()
{
  shiftRegister_begin();

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.begin();

  SPI.transfer(255);
  SPI.transfer(0);
  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);
  attachInterrupt(0, pin_read, RISING); 
}