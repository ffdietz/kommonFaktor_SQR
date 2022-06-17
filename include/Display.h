#include <SPI.h>
#include "Ucglib.h"

#define DSP_SCK  13
#define DSP_SDA  11
#define DSP_CD   10
#define DSP_RST  9
#define DSP_CS   8

#define DISPLAY_WIDTH   160
#define DISPLAY_HEIGHT  128
#define FONT_FAMILY     ucg_font_8x13_mr  //ucg_font_9x15_mr//ucg_font_7x13_mr//ucg_font_8x13_mr//ucg_font_8x13_mr//
#define FONT_W 9
#define FONT_H 18 

Ucglib_ST7735_18x128x160_SWSPI ucg(DSP_SCK, DSP_SDA, DSP_CD, DSP_CS, DSP_RST);


void display_init()
{
  // ucg.setRotate90();
  // ucg.setRotate180();
  // ucg.setRotate270();
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(FONT_FAMILY);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 0, 0, 0);	      	// use blue as background for SOLID mode
  ucg.clearScreen();
}

// uint8_t z = 127;	// start value
// uint32_t lcg_rnd(void) {
//   z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
//   return (uint32_t)z;
// }

void text_template(uint8_t value)
{
  ucg.setRotate90();
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,FONT_H);
  ucg.print("sequencer");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setPrintPos(4,FONT_H * 2);
  ucg.print(value);
  ucg.print("  ");  // extra spaces
  // text1();
  // text2(value);
}


// void display_text_test(void) 
// {
//   ucg.setRotate90();
//   ucg.setFont(FONT_FAMILY);
//   uint8_t rnd = lcg_rnd();
//   ucg_int_t y = FONT_W;

//   ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
//   ucg.setPrintPos(4,y);
//   ucg.print("_mr font:");
//   ucg.setFontMode(UCG_FONT_MODE_SOLID);
//   ucg.setPrintPos(80,y);
//   ucg.print(rnd);
//   ucg.print("  ");  // extra spaces
// }
