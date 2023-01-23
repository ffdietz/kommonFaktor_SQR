#include <Arduino.h>
// #include <LiquidCrystal.h>

#include <ShiftedLCD.h>
#include <SPI.h>
#include "pinout.h"

#ifndef menu_h
#define menu_h

class Menu
{
public:
  Menu();
  LiquidCrystal *lcd;
  void begin();
  void clear();
  bool setMode = false;
  // uint8_t index;

  bool blinking = false;
  void blink(const char *data, uint8_t x, uint8_t y);
  void blink(const char *data);
  void blink(float data);
  void blink(int data);
  void print(const char *data, uint8_t x, uint8_t y);
  void print(const char *data);
  void print(float data);
  void print(int data);

private:
  bool blinkState = false;
  static const uint16_t blinkTime = 500;
  unsigned long lastBlink;
};

#endif


// // https:// github.com/VRomanov89/EEEnthusiast/blob/master/03.%20Arduino%20Tutorials/02.%20LCDMenuTutorial/LCDMenuProgramming/LCDMenuProgramming.ino
// // https:// forum.arduino.cc/t/menu-for-changing-values-difficulty-implementing/82652
