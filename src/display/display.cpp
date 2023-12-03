#include <Arduino.h>
#include "pinout.h"
#include "display.h"

#ifdef PROTOTYPE_BOARD
  #include <ShiftedLCD.h>
  #include <SPI.h>
#elif defined(METRIC_BOARD_V2)
  #include <LiquidCrystal.h>
#endif

// byte activedStep[] = {
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111
// };

// byte deactivedStep[] = {
//   B11111,
//   B10001,
//   B10001,
//   B10001,
//   B10001,
//   B10001,
//   B10001,
//   B11111
// };

byte pauseSymbol[] = {
    B11011,
    B11011,
    B11011,
    B11011,
    B11011,
    B00000,
    B00000,
    B00000
  };

Display::Display() 
{
  #ifdef PROTOTYPE_BOARD 
    lcd = new LiquidCrystal(SHIFT_REG_LATCH_LCD);
  #elif defined(METRIC_BOARD_V2) 
    lcd = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  #endif
}

void Display::begin() 
{
  lcd->begin(LCD_CHARS, LCD_LINES);

  // lcd->createChar(0, deactivedStep);
  // lcd->createChar(1, activedStep);
  lcd->createChar(2, pauseSymbol);

  lcd->clear();

}

void Display::clear(){
  lcd->clear();
}

void Display::pause(uint8_t x, uint8_t y){
  static uint32_t blinkInterval = 600;
  static uint32_t lastBlink = 0;
  static bool blink = false;

  if(millis() - lastBlink >= blinkInterval){
    blink = !blink;
    lastBlink = millis();
  }
  lcd->setCursor(x, y);
  blink? lcd->write(byte(2)) : lcd->print(" ");
}

void Display::print(const char * data) {
  lcd->print(data);
}

void Display::print(int data) {
  lcd->print(data);
}

void Display::print(float data) {
  // Buffer big enough for 000.0 lenght float
  char result[4];
  // Leave room for too large numbers ['000' '.' '0']
  dtostrf(data, 3, 1, result);
  lcd->print(result);
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
