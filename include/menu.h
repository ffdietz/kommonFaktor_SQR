#include <Arduino.h>
#include <LiquidCrystal.h>
#include "pinout.h"


LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// LCD Menu Logic
const int numOfScreens = 10;
int parameters[numOfScreens];

String screens[numOfScreens][2] =
{
  {"MOTOR VOLTAGE",   " VOLTS"},
  {"MOTOR CURRENT",   " AMPS"},
  {"MOTOR RATED HP",  " HP"},
  {"OVERLOAD TEMP.",  " DEGC"},
  {"ACCEL TIME",      " SECS"},
  {"RESTART TIME",    " MINS"},
  {"ANALOG CURR.",    " mA"},
  {"INPUT TEMP.",     " DEGC"},
  {"RUN TIME",        " HOURS"},
  {"START TIMES",     " TIMES"}
};

void printScreen(int currentScreen)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(screens[currentScreen][0]);
  lcd.setCursor(0, 1);
  lcd.print(parameters[currentScreen]);
  lcd.print(screens[currentScreen][1]);
}

void menuRun()
{

}

void menuBegin()
{
  lcd.begin(LCD_CHARS, LCD_LINES);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" STEP SEQUENCER ");
  delay(500);
}

// https:// github.com/VRomanov89/EEEnthusiast/blob/master/03.%20Arduino%20Tutorials/02.%20LCDMenuTutorial/LCDMenuProgramming/LCDMenuProgramming.ino
// https:// forum.arduino.cc/t/menu-for-changing-values-difficulty-implementing/82652