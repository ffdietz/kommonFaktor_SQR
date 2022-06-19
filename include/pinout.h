#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

#define SHR_LATCH 5  //to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 6  //to 74HC595 SH_CP [PIN 11]
#define SHR_DATA  7  //to 74HC595 DS    [PIN 14]

#define PIN_READ 4

/* 
Display 1'8'' pinout based in PDQ_ST7735 configuration 
[DISPLAY PIN] [ATMEGA328]
VCC           5V OR 3.3V
GND           GND
CS            10      // Could be any GPIO pin
RST           RESET
DC (A0)       9       // Could be any GPIO pin
SDA           11
SCK           13
LED           5V max.
*/

#endif