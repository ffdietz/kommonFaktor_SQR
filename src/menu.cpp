#include <Arduino.h>
#include <ShiftedLCD.h>
#include <SPI.h>
// #include <LiquidCrystal.h>

#include "menu.h"
#include "pinout.h"

Menu::Menu()
{
  lcd = new LiquidCrystal(SHIFT_REG_LATCH_LCD);
}

void Menu::begin()
{
  lcd->begin(LCD_CHARS, LCD_LINES);
  lcd->clear();

  lastBlink = millis();
}

void Menu::clear()
{
  lcd->clear();
}

void Menu::print(float data)
{
  char result[5];                 // Buffer big enough for 7-character float
  dtostrf(data, 3, 1, result);    // Leave room for too large numbers ['C''D''E''.''F']
  lcd->print(result);
}

void Menu::print(int data)
{
  lcd->print(data);
}

void Menu::print(const char *data)
{
  lcd->print(data);
}

void Menu::print(const char *data, uint8_t x, uint8_t y)
{
  lcd->setCursor(x, y);
  lcd->print(data);
}

void Menu::blink(const char *data)
{
  char space[strlen(data)];           // create a char array with the size of data input
  memset(space, ' ', strlen(data));   // fill the array with ' ' (spaces) to cover the last print

  if (millis() - lastBlink > blinkTime)
  {
    blinkState = !blinkState;
    lastBlink = millis();
  }
  
  blinkState? lcd->print(data) : lcd->print(space);

}

void Menu::blink(const char *data, uint8_t x, uint8_t y)
{
  lcd->setCursor(x, y);
  blink(data);
}

void Menu::blink(int data)
{
  blink(data);
}

void Menu::blink(float data)
{
  char result[5];              // Buffer big enough for 7-character float
  dtostrf(data, 3, 1, result); // Leave room for too large numbers!
  blink(result);
}
