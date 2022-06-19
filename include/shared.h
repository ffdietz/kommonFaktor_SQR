#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>
//Display
#include <SPI.H>
#include "PDQ_GFX.h"
#include "PDQ_ST7735_config.h"
#include "PDQ_ST7735.h"

#include "coordinates.h"

//Clock
//ShiftRegister
////ShiftRegisterShifter
////ShiftRegisterShowSequence
//SetSequenceButton

//Properties of tft display
struct Display {
  static const uint8_t width = 160;
  static const uint8_t height = 128;
  static const uint8_t padding = 5;
  static const uint8_t bgColor = ST7735_BLACK;
  
  static void drawBackground(PDQ_ST7735 * tft){
    tft->fillScreen(bgColor);
  }
};

struct InfoBarData {
  static const int16_t bgColor = ST7735_BLACK;
  static const int16_t fontColor = ST7735_WHITE;
  static const char * scoreLabel;
  static const char * livesLabel;
  static const char * pauseLabel;

  // top left corner of screen
  static const Coordinates topBarLabelPos;
  static const Coordinates topBarValuePos;
  static const Coordinates topBarPausePos;
  
  // bottom left corner of screen
  static const Coordinates bottomBarLabelPos;
  static const Coordinates bottomBarValuePos;
};

/* static */ const char * InfoBarData::scoreLabel = "SCORE";
/* static */ const char * InfoBarData::livesLabel = "LIVES";
/* static */ const char * InfoBarData::pauseLabel = "PAUSED";

#endif