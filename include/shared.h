#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>
//Display
#include <SPI.H>
#include "PDQ_GFX.h"
#include "PDQ_ST7735_config.h"
#include "PDQ_ST7735.h"
#include "Fonts/FreeSans9pt7b.h"

#include "global.h"
#include "coordinates.h"
#include "configDraw.h"

//Properties of tft display
struct Display {
  static const uint8_t width = DISPLAY_WIDTH;
  static const uint8_t height = DISPLAY_HEIGHT;
  static const uint8_t padding  = PADDING;
  static const uint8_t fontHeight = FONT_HEIGHT;
  static const uint8_t rowHeight = FONT_HEIGHT + padding;
  static const uint8_t bgColor = ST7735_BLACK;
  
  static void drawBackground(PDQ_ST7735 * tft){
    tft->fillScreen(bgColor);
  }
};

struct InfoBarData {
  static const int16_t bgColor   = ST7735_BLACK;
  static const int16_t fontColor = ST7735_WHITE;
  static const char * titleLabel;
  static const char * stepsLabel;
  static const char * speedLabel;
  static const char * pauseLabel;
  static const char * stepPosLabel;

  // top left corner of screen
  static const Coordinates row0TitlePos;
  static const Coordinates row0PausePos;

    // top left corner of screen
  static const Coordinates row1LabelPos;
  static const Coordinates row1ValuePos;

      // top left corner of screen
  static const Coordinates row2LabelPos;
  static const Coordinates row2ValuePos;
  
        // top left corner of screen
  static const Coordinates row3LabelPos;
  static const Coordinates row3ValuePos;
};

//Classes
class TitleBar {
  public:
    // draw top bar label
    static void printLabel(PDQ_ST7735 * tft, Coordinates pos, const char * label) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::width, FONT_HEIGHT, ST7735_BLACK);
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // draw label
      tft->println(label);
    }

    // draw status message in top bar
    static void drawPause(PDQ_ST7735 * tft, Coordinates pos, const char * text) {

      tft->setCursor(pos.x, pos.y);
      tft->print(text);
    }

    // draw status message in top bar
    static void printPause(PDQ_ST7735 * tft, Coordinates pos, const char * text) {
        tft->setCursor(pos.x, pos.y);
        tft->print(text);
    }
};

class StepsBar {
  public:
    // draw top bar label
    static void printLabel(PDQ_ST7735 * tft, Coordinates pos, const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // draw label
      tft->println(label);
    }

    static void printValue(PDQ_ST7735 * tft, Coordinates pos, int16_t score) {
      // set cursor position and print score
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }

};

class SpeedBar {
  public:
    // draw speed label
    static void printLabel(PDQ_ST7735 * tft, Coordinates pos, 
      const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // print label
      tft->println(label);
    }

    // print speed value
    static void printValue(PDQ_ST7735 * tft, Coordinates pos, float score) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::width, FONT_HEIGHT, ST7735_BLACK);
      // set cursor position and print
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }

};

class StepPositionBar {
  public:
    // draw speed label
    static void printLabel(PDQ_ST7735 * tft, Coordinates pos, 
      const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // print label
      tft->println(label);
    }

    // print speed value
    static void printValue(PDQ_ST7735 * tft, Coordinates pos, uint8_t score) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::fontHeight*3, Display::fontHeight, ST7735_BLACK);
      // set cursor position and print
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }

};

class ScoreBar {
  public:
    // draw top bar label
    static void drawLabel(PDQ_ST7735 * tft, Coordinates pos, 
      const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // draw label
      tft->println(label);
    }

    // draw current game score
    static void drawScore(PDQ_ST7735 * tft, Coordinates pos, int16_t score) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::width, FONT_HEIGHT, ST7735_BLACK);

      // set cursor position and print score
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }

    // draw status message in top bar
    static void drawPause(PDQ_ST7735 * tft, Coordinates pos, const char * text) {
        tft->setCursor(pos.x, pos.y);
        tft->print(text);
    }
};

class LivesBar {
  public:
    // draw bottom bar label
    static void drawLabel(PDQ_ST7735 * tft, Coordinates pos, 
      const char * label) {
      // set cursor position
      tft->setCursor(pos.x, pos.y);
      // draw label
      tft->println(label);
    }
    
    // draw current game score
    static void drawLives(PDQ_ST7735 * tft, Coordinates pos, int16_t score) {
      // overwrite previous value
      tft->fillRect(pos.x, pos.y, Display::width, FONT_SCALE, ST7735_BLACK);

      // set cursor position and print score
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }
};

/* static */ const char * InfoBarData::titleLabel = "SEQUENCER";
/* static */ const char * InfoBarData::pauseLabel = "PAUSED";
/* static */ const char * InfoBarData::stepsLabel = "STEPS:";
/* static */ const char * InfoBarData::speedLabel = "BPM:";
/* static */ const char * InfoBarData::stepPosLabel = "STEP: ";

/* static */ const Coordinates InfoBarData::row0TitlePos = { Display::padding , Display::padding };
/* static */ const Coordinates InfoBarData::row0PausePos = { Display::width - Display::padding - 6*FONT_WIDTH ,  InfoBarData::row0TitlePos.y };

/* static */ const Coordinates InfoBarData::row1LabelPos = { InfoBarData::row0TitlePos.x , InfoBarData::row0TitlePos.y + Display::rowHeight };
/* static */ const Coordinates InfoBarData::row1ValuePos = { InfoBarData::row0TitlePos.x + 6*FONT_WIDTH, InfoBarData::row1LabelPos.y };

/* static */ const Coordinates InfoBarData::row2LabelPos = { InfoBarData::row0TitlePos.x , InfoBarData::row0TitlePos.y + Display::rowHeight * 2 };
/* static */ const Coordinates InfoBarData::row2ValuePos = { InfoBarData::row0TitlePos.x + 6*FONT_WIDTH,  InfoBarData::row2LabelPos.y};

/* static */ const Coordinates InfoBarData::row3LabelPos = { InfoBarData::row0TitlePos.x , InfoBarData::row0TitlePos.y + Display::rowHeight * 3 };
/* static */ const Coordinates InfoBarData::row3ValuePos = { InfoBarData::row0TitlePos.x + 6*FONT_WIDTH,  InfoBarData::row3LabelPos.y};

struct DrawLayout {

  static const int8_t mapWidth = X_BOUND; // map width in tiles
  static const int8_t mapHeight = Y_BOUND; // map height in tiles
  static const int8_t dotRadious = 5; 
  static const int8_t dotOffset = dotRadious*2 + 5; // where in the tile the dot is drawn

  static const int16_t bgColor  = ST7735_BLACK; // color of walls
  static const int16_t dotColor = ST7735_RED; // color of dot pickups

  static const int16_t mapStartX = Display::padding;
  static const int16_t mapStartY = Display::padding + Display::rowHeight * 5;

  // draw map foreground to tft screen
  static void clearScreen(PDQ_ST7735 * tft);

  static void drawLayout(PDQ_ST7735 * tft);

  // draw dot (small pickup) on tft screen
  static void drawDot(PDQ_ST7735 * tft, uint16_t x, uint16_t y);
  
  // draw power pellet (large pickup) on tft screen
  static void drawPowerPellet(PDQ_ST7735 * tft, uint16_t x, uint16_t y);
};

//Define functions of structure Drawmap
/* static */ void DrawLayout::drawDot(PDQ_ST7735 * tft, uint16_t x, uint16_t y) {
  // fill tile first

  // draw dot on top of rectangle
      tft->fillRect(x, y, dotRadious*2, dotRadious*2, dotColor);
  // tft->fillCircle(x + dotOffset, y + dotOffset, dotSize, dotColor);
  // tft->drawCircle(x, y , dotRadious*2, dotColor);
}

/* static  */void DrawLayout::drawLayout(PDQ_ST7735 * tft) {
  // fill background
  tft->fillRect(mapStartX, mapStartY, mapWidth, mapHeight, 
    bgColor);
  
    for (int8_t r = 0; r < 8; ++r) {
      drawDot(tft, mapStartX * 2 + r + dotOffset * r + 1 , mapStartY);
    }
};

/* static  */void DrawLayout::clearScreen(PDQ_ST7735 * tft) {
  // fill background
  tft->fillRect(0, 0, Display::width, Display::height, bgColor);
};

#endif
