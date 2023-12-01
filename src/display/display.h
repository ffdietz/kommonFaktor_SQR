#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <Arduino.h>
#include "pinout.h"

#ifdef PROTOTYPE_BOARD
  #include <ShiftedLCD.h>
  #include <SPI.h>
#elif defined(METRIC_BOARD_V2)
  #include <LiquidCrystal.h>
#endif

class Display
{
public:
  Display();
  LiquidCrystal *lcd;
  void begin();
  void clear();
  void pause(uint8_t x, uint8_t y);
  
  void print(const char * data);
  void print(const char * data, uint8_t x, uint8_t y);
  void print(float data);
  void print(float data, uint8_t x, uint8_t y);
  void print(int data);
  void print(int data, uint8_t x, uint8_t y);
};

#endif


// // https:// github.com/VRomanov89/EEEnthusiast/blob/master/03.%20Arduino%20Tutorials/02.%20LCDMenuTutorial/LCDMenuProgramming/LCDMenuProgramming.ino
// // https:// forum.arduino.cc/t/menu-for-changing-values-difficulty-implementing/82652
