#include <Arduino.h>

#include "pinout.h"

#ifndef display_h
#define display_h

#ifdef PROTOTYPE_BOARD_PINOUT
  #include <ShiftedLCD.h>
  #include <SPI.h>
#elif defined(METRIC_BOARD_PINOUT)
  #include <LiquidCrystal.h>
#endif

class Display
{
public:
  Display();
  LiquidCrystal *lcd;
  void begin();
  void clear();
  void clearLine(uint8_t x, uint8_t y);
  void clearField();

  void print(const char * data);
  void print(const char * data, uint8_t x, uint8_t y);
  void print(float data);
  void print(float data, uint8_t x, uint8_t y);
  void print(int data);
  void print(int data, uint8_t x, uint8_t y);

  // void blink(const char * data, uint8_t x, uint8_t y);
  // void blink(const char * data);
  // void blink(float data);
  // void blink(int data);

private:
  bool blinkState = false;
  static const uint16_t blinkTime = 500;
  unsigned long lastBlink;
};

#endif


// // https:// github.com/VRomanov89/EEEnthusiast/blob/master/03.%20Arduino%20Tutorials/02.%20LCDMenuTutorial/LCDMenuProgramming/LCDMenuProgramming.ino
// // https:// forum.arduino.cc/t/menu-for-changing-values-difficulty-implementing/82652
