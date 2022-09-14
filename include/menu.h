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
  void print(const char *data, uint8_t x, uint8_t y);
  void print(const char *data);
  void print(float data);
  void print(int data);
  void printBlink(const char *data, uint8_t x, uint8_t y);
  void clear();
  uint8_t index;

private:
};

#endif

// // LCD Menu Logic
// const int numOfScreens = 10;
// int parameters[numOfScreens];

// String screens[numOfScreens][2] =
// {
//   {"BPM",   " VOLTS"},
//   {"STEPS",   " AMPS"},
//   {"MOTOR RATED HP",  " HP"},
//   {"OVERLOAD TEMP.",  " DEGC"},
//   {"ACCEL TIME",      " SECS"},
//   {"RESTART TIME",    " MINS"},
//   {"ANALOG CURR.",    " mA"},
//   {"INPUT TEMP.",     " DEGC"},
//   {"RUN TIME",        " HOURS"},
//   {"START TIMES",     " TIMES"}
// };

// void printScreen(int currentScreen)
// {
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print(screens[currentScreen][0]);
//   lcd.setCursor(0, 1);
//   lcd.print(parameters[currentScreen]);
//   lcd.print(screens[currentScreen][1]);
// }

// void menuBegin()
// {
//   lcd.begin(LCD_CHARS, LCD_LINES);
//   lcd.clear();

//   delay(500);
// }

// // https:// github.com/VRomanov89/EEEnthusiast/blob/master/03.%20Arduino%20Tutorials/02.%20LCDMenuTutorial/LCDMenuProgramming/LCDMenuProgramming.ino
// // https:// forum.arduino.cc/t/menu-for-changing-values-difficulty-implementing/82652
