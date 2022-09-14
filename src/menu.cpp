#include <Arduino.h>
#include <LiquidCrystal.h>

#include "menu.h"
#include "pinout.h"

Menu::Menu()
{
  lcd = new LiquidCrystal(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
}

void Menu::begin()
{
  lcd->begin(LCD_CHARS, LCD_LINES);
  lcd->clear();
}

void Menu::clear()
{
  lcd->clear();
}

void Menu::print(const char *data)
{
  lcd->print(data);
}

void Menu::print(const char *data, uint8_t x, uint8_t y)
{
  lcd->setCursor(x, y);
  print(data);
}

void Menu::print(float data)
{
  lcd->print(data);
}

void Menu::print(int data)
{
  lcd->print(data);
}

void Menu::blink(const char *data)
{
  //create a char array with the size of data input
  char space[strlen(data)];

  //fill the array with ' ' (spaces) to cover the last print 
  memset(space, ' ', strlen(data));

  if (millis() - lastBlink > blinkTime)
  {
    blinkState = !blinkState;
    lastBlink = millis();
  }
  
  blinkState ? lcd->print(data) : lcd->print(space);
}

void Menu::blink(const char *data, uint8_t x, uint8_t y)
{
  lcd->setCursor(x, y);
  blink(data);
}