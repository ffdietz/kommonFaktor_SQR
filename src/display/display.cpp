#include <Arduino.h>
#include "pinout.h"
#include "display.h"

#ifdef PROTOTYPE_BOARD_PINOUT
  #include <ShiftedLCD.h>
  #include <SPI.h>
#elif defined(METRIC_BOARD_PINOUT)
  #include <LiquidCrystal.h>
#endif

byte activedStep[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte deactivedStep[] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111
};

Display::Display() 
{
  #ifdef PROTOTYPE_BOARD_PINOUT 
    lcd = new LiquidCrystal(SHIFT_REG_LATCH_LCD);
  #elif defined(METRIC_BOARD_PINOUT) 
    lcd = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  #endif
}

void Display::begin() 
{
  lcd->begin(LCD_CHARS, LCD_LINES);

  lcd->createChar(0, deactivedStep);
  lcd->createChar(1, activedStep);

  lcd->clear();

}

void Display::clear() 
{
  lcd->clear();
}

void Display::print(const char * data) {
  lcd->print(data);
}

void Display::print(float data) {
  char result[4];                 // Buffer big enough for 000.0 lenght float
  dtostrf(data, 3, 1, result);    // Leave room for too large numbers ['000' '.' '0']
  lcd->print(result);
}

void Display::print(int data) 
{
  lcd->print(data);
}

void Display::print(const char * data, uint8_t x, uint8_t y) {
  lcd->setCursor(x, y);
  lcd->print(data);
}

void Display::print(float data, uint8_t x, uint8_t y) {
  lcd->setCursor(x, y);
  print(data);
}

void Display::print(int data, uint8_t x, uint8_t y) {
  lcd->setCursor(x, y);
  print(data);
}

// void Display::blink(const char * data) {

//   char space[strlen(data)];           // create a char array with the size of data input
//   memset(space, ' ', strlen(data));   // fill the array with ' ' (spaces) to cover the last print

//   if (millis() - lastBlink > blinkTime){
//     blinkState = !blinkState;
//     lastBlink = millis();
//   }

//   blinkState ? lcd->print(data) : lcd->print(space);

// }

// void Display::blink(const char * data, uint8_t x, uint8_t y) {
//   lcd->setCursor(x, y);
//   blink(data);
// }

// void Display::blink(int data) {
//   blink(data);
// }

// void Display::blink(float data) {
//   char result[4];              // Buffer big enough for 000.00 format
//   dtostrf(data, 3, 1, result); // Leave room for too large numbers!
//   blink(result);
// }
