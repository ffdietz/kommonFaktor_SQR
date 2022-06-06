#include <SPI.h>
#include "Ucglib.h"

#define DSP_SCK  13
#define DSP_SDA  11
#define DSP_CD   10
#define DSP_RST  9
#define DSP_CS   8

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 128
// #define FONT_FAMILY ucg_font_ncenR14_tr
#define FONT_FAMILY ucg_font_helvR18_tr

Ucglib_ST7735_18x128x160_SWSPI ucg(DSP_SCK, DSP_SDA, DSP_CD, DSP_CS, DSP_RST);


void display_init()
{
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(FONT_FAMILY);
  ucg.setColor(255, 255, 255);
  ucg.setRotate90();
  ucg.clearScreen();
  // ucg.setRotate180();
  // ucg.setRotate270();
}

uint8_t z = 127;	// start value
uint8_t lcg_rnd(void) {
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return z;
}

void draw_box(void) {
  ucg_int_t x, y, w, h;
  ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
  x = lcg_rnd() & 31;
  y = lcg_rnd() & 31;
  w = lcg_rnd() & DISPLAY_WIDTH/4;
  w += DISPLAY_WIDTH/2;
  h = lcg_rnd() & DISPLAY_HEIGHT/4;
  h += DISPLAY_HEIGHT/2;
  ucg.drawFrame(x, y, w, h);
}

// void draw_text(void) {
//   ucg.setFont(ucg_font_ncenR14_tr);
//   //ucg.setColor(255, 255, 255);
//   ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
//   ucg.setPrintPos(0,20);
//   ucg.print("The quick brown");
//   ucg.setPrintPos(0,40);
//   ucg.print("fox jumps over");
//   ucg.setPrintPos(0,60);
//   ucg.print("the lazy dog");
// }

void display_update()
{
  ucg.setPrintPos(0,20);
  ucg.print("shift register");
  ucg.setPrintPos(0,50);
  ucg.print(millis());
  ucg.clearScreen();
}

// void show_result(const char *s, uint16_t fps)  
// {
//   ucg.clearScreen();
//   ucg.setFont(ucg_font_helvR18_tr);
//   ucg.setColor(255, 255, 255);
//   ucg.setPrintPos(0,25);
//   ucg.print(s);
//   ucg.setPrintPos(0,50);
//   ucg.print(s);
//   delay(20);
// }