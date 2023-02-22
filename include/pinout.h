#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

#define SHIFT_REG_SCK 13   // to 74HC595 SH_CP [PIN 11]
#define SHIFT_REG_MOSI 11  // to 74HC595 DS    [PIN 14]
#define SHIFT_REG_LATCH_LCD 10  // to 74HC595 ST_CP [PIN 12]
#define SHIFT_REG_LATCH_STEP_CTRL 5 // to 74HC595 ST_CP [PIN 12]

#define ENCODER_A   3
#define ENCODER_B   2
#define ENCODER_SET 4
#define CLOCK_IN    12
#define CLOCK_OUT   9
#define PAUSE_BUTTON    A0
#define STEP_CTRL_INPUT A1 

#define LCD_CHARS 16
#define LCD_LINES 2

#define ENCODER_MIN -1000
#define ENCODER_MAX 1000

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