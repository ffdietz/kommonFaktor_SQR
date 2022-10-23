#include <Arduino.h>
#include <LiquidCrystal.h>
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
  uint8_t index;

  void print(int data);
  void print(float data);
  void print(const char *data);
  void print(const char *data, uint8_t x, uint8_t y);
  void blink(int data);
  void blink(float data);
  void blink(const char *data);
  void blink(const char *data, uint8_t x, uint8_t y);

private:
  bool blinkState = false;
  static const uint16_t blinkTime = 500;
  unsigned long lastBlink;
};

#endif


// // https:// github.com/VRomanov89/EEEnthusiast/blob/master/03.%20Arduino%20Tutorials/02.%20LCDMenuTutorial/LCDMenuProgramming/LCDMenuProgramming.ino
// // https:// forum.arduino.cc/t/menu-for-changing-values-difficulty-implementing/82652
