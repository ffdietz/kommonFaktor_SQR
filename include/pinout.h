#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

#define SHR_LATCH 5 // to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 6 // to 74HC595 SH_CP [PIN 11]
#define SHR_DATA 7  // to 74HC595 DS    [PIN 14]

#define ENCODER_A 2
#define ENCODER_B 3

#define ENCODER_MIN 0
#define ENCODER_MAX 10

#define ENCODER_SET A1
#define PAUSE_BUTTON A0

#define LCD_RS 11
#define LCD_RW 10
#define LCD_EN 9

#define LCD_D4 5
#define LCD_D5 6
#define LCD_D6 7
#define LCD_D7 8

#define LCD_CHARS 16
#define LCD_LINES 2

#define FRAME_DELAY 10

/*
Display 1'8'' pinout based in PDQ_ST7735 configuration
[DISPLAY PIN] [ATMEGA328]
VCC           5V OR 3.3V
GND           GND
CS            9       // Could be any GPIO pin
RST           RESET
DC (A0)       10      // Could be any GPIO pin
SDA           11
SCK           13
LED           5V max.
*/

#endif