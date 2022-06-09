#include <Arduino.h>

#define SHR_LATCH 5  //to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 6  //to 74HC595 SH_CP [PIN 11]
#define SHR_DATA  7  //to 74HC595 DS [PIN 14]

void shiftRegister_init()
{
//SETTING PINS AS OUTPUT
  DDRD |= (1 << SHR_LATCH);
  DDRD |= (1 << SHR_CLOCK);
  DDRD |= (1 << SHR_DATA);
}


void shiftRegister_out(uint8_t  data)
{
  shiftOut(SHR_DATA, SHR_CLOCK, MSBFIRST, 1 << data);  
  shiftOut(SHR_DATA, SHR_CLOCK, LSBFIRST, 1 << data);  
  PORTD &= ~(1 << SHR_LATCH);   //LATCH LOW
  PORTD |= (1 << SHR_LATCH );   //LATCH HIGH
}

void shiftRegister_test()
{
  for (uint8_t bit_shift = 0 ; bit_shift < 8 ; bit_shift++)
  {
    shiftRegister_out(bit_shift);
    delay(50);
  }


