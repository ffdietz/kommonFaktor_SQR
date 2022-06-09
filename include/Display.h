#include <SPI.h>
#include "Ucglib.h"

#define DSP_SCK  13
#define DSP_SDA  11
#define DSP_CD   10
#define DSP_RST  9
#define DSP_CS   8

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 128
#define FONT_FAMILY ucg_font_8x13_mr//ucg_font_9x15_mr//ucg_font_7x13_mr//ucg_font_8x13_mr//ucg_font_8x13_mr//
#define FONT_W 9
#define FONT_H 18 

Ucglib_ST7735_18x128x160_SWSPI ucg(DSP_SCK, DSP_SDA, DSP_CD, DSP_CS, DSP_RST);


void display_init()
{
  // ucg.setRotate90();
  // ucg.setRotate180();
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(FONT_FAMILY);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 0, 0, 0);			// use blue as background for SOLID mode
  ucg.clearScreen();
}

uint8_t z = 127;	// start value
uint32_t lcg_rnd(void) {
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return (uint32_t)z;
}


void display_update()
{

}


void text_template(uint8_t value)
{
  ucg.setRotate270();
  // ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  // ucg.setPrintPos(4,FONT_H);
  // ucg.print("REGISTER SEQUENCER");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setPrintPos(4,18);
  ucg.print(value);
  ucg.print("  ");  // extra spaces
  // text1();
  // text2(value);
}



void display_text_test(void) 
{
  // ucg.setRotate90();
  ucg.setRotate270();
  ucg.setFont(FONT_FAMILY);
  uint8_t rnd = lcg_rnd();
  ucg_int_t y = FONT_W;
  ucg_int_t h = FONT_H;

  // Using the "h" or "m" type of font in solid mode will almost work
  // however, if the number changes from 100 to 99, the last number 
  // will not be overwritten.
  // y += h;
  // ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  // ucg.setPrintPos(4,y);
  // ucg.setFont(ucg_font_helvB08_tr);
  // ucg.print("Value errors:");
  // ucg.setFontMode(UCG_FONT_MODE_SOLID);
  // ucg.setFont(ucg_font_helvB08_hr);
  // ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  // ucg.setColor(1, 0, 0, 0);			// use blue as background for SOLID mode
  // ucg.setPrintPos(80,y);
  // ucg.print(rnd);

  // Using the "h" or "m" type of font in solid mode will work fine, if
  // there are extra spaced after the string to overwrite the previous value.
  // As long as a "h" font is used, the number of spaces is not fixed.
  // This means, even two spaced my not be sufficent. Better use a monospace font.
  // y += h;
  // ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  // ucg.setPrintPos(4,y);
  // ucg.setFont(ucg_font_helvB08_tr);
  // ucg.print("Almost ok:");
  // ucg.setFontMode(UCG_FONT_MODE_SOLID);
  // ucg.setFont(ucg_font_helvB08_hr);
  // ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  // ucg.setColor(1, 0, 0, 0);			// use blue as background for SOLID mode
  // ucg.setPrintPos(80,y);
  // ucg.print(rnd);
  // ucg.print("  ");  // two extra spaces (not sufficient here)

  // The transparent font and mode can be used, if the previous content
  // is fully erased or overwritten
  // y += h;
  // ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  // ucg.setPrintPos(4,y);
  // ucg.setFont(ucg_font_helvB08_tr);
  // ucg.print("Manual erase:");  
  // ucg.setColor(0, 255, 40, 80);
  // ucg.setColor(1, 0, 255, 0);
  // ucg.setColor(2, 255, 0, 0);
  // ucg.setColor(3, 65, 255, 40);
  // ucg.drawGradientBox(80-2, y-10, 22, 12);  // red to green bar will erase the previous value
  // ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  // ucg.setFont(ucg_font_helvB08_tr);
  // ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  // ucg.setPrintPos(80,y);
  // ucg.print(rnd);

  // The is will use the solid font with the extra spaces to erase the previous value
  // A monospaced 8x8 pixel font is used (here: ucg_font_amstrad_cpc_8r).
  // y += h;
  // ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  // ucg.setPrintPos(4,y);
  // ucg.setFont(ucg_font_helvB08_tr);
  // ucg.print("8x8 font:");
  // ucg.setFontMode(UCG_FONT_MODE_SOLID);
  // ucg.setFont(ucg_font_amstrad_cpc_8r);
  // ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  // ucg.setColor(1, 0, 0, 0);			// use blue as background for SOLID mode
  // ucg.setPrintPos(80,y);
  // ucg.print(rnd);
  // ucg.print("  ");  // extra spaces

  // The is will use the solid font with the extra spaces to erase the previous value
  // Any monospaced font can be used (here: ucg_font_7x13_mr).
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  // ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("_mr font:");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  // ucg.setFont(ucg_font_7x13_mr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 0, 0, 0);			// use blue as background for SOLID mode
  ucg.setPrintPos(80,y);
  ucg.print(rnd);
  ucg.print("  ");  // extra spaces
}
