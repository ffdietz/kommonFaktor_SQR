#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>
//Display
#include <SPI.H>
#include "PDQ_GFX.h"
#include "PDQ_ST7735_config.h"
#include "PDQ_ST7735.h"

#include "global.h"
#include "coordinates.h"
#include "configDraw.h"

//Clock
//ShiftRegister
////ShiftRegisterShifter
////ShiftRegisterShowSequence
//SetSequenceButton

//Properties of tft display
struct Display {
  static const uint8_t width = 160;
  static const uint8_t height = 128;
  static const uint8_t padding = 3;
  static const uint8_t bgColor = ST7735_BLACK;
  
  static void drawBackground(PDQ_ST7735 * tft){
    tft->fillScreen(bgColor);
  }
};

struct InfoBarData {
  static const int16_t bgColor = ST7735_BLACK;
  static const int16_t fontColor = ST7735_WHITE;
  static const char * titleLabel;
  static const char * stepsLabel;
  static const char * speedLabel;
  static const char * pauseLabel;

  // top left corner of screen
  static const Coordinates topBarLabelPos;
  static const Coordinates topBarValuePos;
  static const Coordinates topBarPausePos;
  
  // bottom left corner of screen
  static const Coordinates bottomBarLabelPos;
  static const Coordinates bottomBarValuePos;
};

//Classes
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
      tft->fillRect(pos.x, pos.y, Display::width, FONT_H, ST7735_BLACK);

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
      tft->fillRect(pos.x, pos.y, Display::width, FONT_H, ST7735_BLACK);

      // set cursor position and print score
      tft->setCursor(pos.x, pos.y);
      tft->print(score);
    }
};

/* static */ const char * InfoBarData::titleLabel = "STEP SEQUENCER";
/* static */ const char * InfoBarData::stepsLabel = "STEPS";
/* static */ const char * InfoBarData::speedLabel = "BPM";
/* static */ const char * InfoBarData::pauseLabel = "PAUSED";

/* static */ const Coordinates InfoBarData::topBarLabelPos = { Display::padding, Display::padding };
/* static */ const Coordinates InfoBarData::topBarValuePos = { Display::width - 20, InfoBarData::topBarLabelPos.y};
/* static */ const Coordinates InfoBarData::topBarPausePos = { InfoBarData::topBarLabelPos.x + 3*Display::width/5, InfoBarData::topBarLabelPos.y};

/* static */ const Coordinates InfoBarData::bottomBarLabelPos =  { Display::padding, Display::height - Display::padding - 2*FONT_W };
/* static */ const Coordinates InfoBarData::bottomBarValuePos =  { InfoBarData::bottomBarLabelPos.x + Display::width/3, InfoBarData::bottomBarLabelPos.y};

struct DrawMap {
  static const int8_t mapWidth = DISPLAY_ROW; // map width in tiles
  static const int8_t mapHeight = DISPLAY_COL; // map height in tiles

  static const int8_t tileSize   = FONT_W; // size in pixels
  static const int8_t dotSize    = FONT_W; // 1/4 of tile size
  static const int8_t pelletSize = FONT_W/2; // 1/2 tile size

  static const int8_t dotOffset = 2; // where in the tile the dot is drawn
  static const int8_t pelletXOffset = 2; 
  static const int8_t pelletYOffset = 2; 
                                        
  static const int16_t bgColor    = ST7735_BLACK; // color of walls
  static const int16_t pathColor  = ST7735_BLACK; // color of paths, etc.
  static const int16_t dotColor   = ST7735_WHITE; // color of dot pickups
  static const int16_t pelletColor= ST7735_WHITE;

  // top left corner of the map (in pixels)
  static const int16_t mapStartX = Display::padding;
  static const int16_t mapStartY = Display::padding + DrawMap::tileSize*3;

  // draw map foreground to tft screen
  static void clearScreen(PDQ_ST7735 * tft);

  // draw path or non-playable area (same color)
  static void drawPath(PDQ_ST7735 * tft, uint16_t x, uint16_t y);
  
  // draw dot (small pickup) on tft screen
  static void drawDot(PDQ_ST7735 * tft, uint16_t x, uint16_t y);
  
  // draw power pellet (large pickup) on tft screen
  static void drawPowerPellet(PDQ_ST7735 * tft, uint16_t x, uint16_t y);

  // draw white "door" on ghost box
  static void drawGhostDoor(PDQ_ST7735 * tft, uint16_t x, uint16_t y);
};


//Define functions of structure Drawmap
/* static */ void DrawMap::drawDot(PDQ_ST7735 * tft, uint16_t x, uint16_t y) {
  // fill tile first

  // draw dot on top of rectangle
  tft->fillRect(x + dotOffset, y + dotOffset, 
    dotSize, dotSize, dotColor);

}

/* static  */void DrawMap::drawPowerPellet(PDQ_ST7735 * tft, uint16_t x, 
  uint16_t y) {
  // fill tile first

  // draw power pellet on top of rectangle
  tft->fillRect(x + pelletXOffset, y + pelletYOffset, 
    pelletSize, pelletSize, pelletColor);
}

/* static  */void DrawMap::clearScreen(PDQ_ST7735 * tft) {
  // fill background
  tft->fillRect(0, 0, Display::width, Display::height, 
    bgColor);
};


#endif
