#ifndef MENU__H_
#define MENU__H_
#include "global.h"

typedef void (*funcPointer)(void);
//function pointer
funcPointer menuFunction;
bool setMenuMode = false;
char * dataOut;

//Structure describes current menu and submenu state
struct menuIndexSelector
{
  uint8_t menu;
  uint8_t subMenu;
} indexSelector;

// Menu Labels
//menu 0
const char * MN000 = "SQR_";
//menu 1
const char * MN100 = "BPM ";
const char*  MN101;
//menu 2
const char * MN200 = "POSITION ";
const char * MN201;
//menu 3
const char * MN300 = "STEPS ";
const char * MN301;
//menu 4
const char * MN400 = "SEQUENCE ";
//Submenus of menu 4
const char * MN401 = "LINEAR";
const char * MN402 = "INVERT";
const char * MN403 = "RANDOM";
const char * MN404 = "CUSTOM";
//menu 5
const char * MN500 = "CLOCK ";
//Submenus of menu 5
const char * MN501 = "INTERNAL";
const char * MN502 = "EXTERNAL";
const char * MN503 = "DIVIDED";
const char * MN504 = "MULTIPLIED";


const char* MENU[] = 
{
  MN000,
  MN100,
  MN200,
  MN300,
  MN400,
  MN500,
};

const char* SUBMENU[] = 
{
  MN101,
  MN201,
  MN301,
  MN401, MN402, MN403, MN404,
  MN501, MN502, MN503, MN504,
};

const uint8_t MENU_LENGTH[] =
{
  6, // items in menu 1
  1, // items in submenu 1
  1, // items in submenu 2
  1, // items in submenu 3
  3, // items in submenu 4
  3, // items in submenu 5
};

void fn101(void);
void fn201(void);
void fn301(void);
void fn401(void);
void fn402(void);
void fn403(void);
void fn404(void);
void fn501(void);
void fn502(void);
void fn503(void);
void fn504(void);

const funcPointer menuFn[] = {
  fn101, 
  fn201, 
  fn301, 
  fn401, fn402, fn403, fn404, 
  fn501, fn502, fn503, fn504, 
};

bool menuIsSetMode(){
  return setMenuMode;
}

void clearMenu()
{
  display.clear();
}

void menuInit()
{
  indexSelector.menu = 1;
  indexSelector.subMenu = 1;

  menuFunction = *menuFn[0];

  clearMenu();

}

int setMenuFnIndex(uint8_t menu, uint8_t submenu)
{
  uint8_t indexOutput = 0;
  for(byte i = 0 ; i < (menu - 1) ; i++ ) indexOutput += MENU_LENGTH[i + 1];
  indexOutput += submenu - 1;

  return indexOutput;
}

void selectMenuIndex(int variation)
{
  if(!setMenuMode){
    indexSelector.menu = constrain(indexSelector.menu + variation, 1, MENU_LENGTH[0] - 1);
  }
  else {
    indexSelector.subMenu = constrain(indexSelector.subMenu + variation, 1, MENU_LENGTH[indexSelector.menu]);
  }

  menuFunction = *menuFn[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)];
}

void menu()
{
  if(!setMenuMode){
    display.print(MENU[0], 0, 0);
    display.print(MENU[indexSelector.menu], 0, 1);
  } else {
    display.print(MENU[indexSelector.menu], 0, 0);
    display.print(SUBMENU[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)], 0, 1);
  };

  menuFunction();
}

void fn101() {
  if(setMenuMode) {
    sequencer.setSpeed(encoder.getDirection());
    display.print(sequencer.getSpeed(), 0, 1);
  } else {
    display.print(sequencer.getSpeed());
  }
}

void fn201() {
  if(setMenuMode) {
    sequencer.pauseSequence();
    sequencer.setManualStep(encoder.getDirection());

    display.print(sequencer.getCurrentPosition() + 1, 0, 1);

  } else {
    sequencer.playSequence();
    display.print(sequencer.getCurrentPosition() + 1);
  }
}

void fn301() {
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
}

void fn401() {
  static int subMenu = 0;
  if(setMenuMode) {
    subMenu += encoder.getDirection();
    subMenu = constrain(subMenu, 0, MENU_LENGTH[indexSelector.menu]);

    sequencer.setSequenceMode(subMenu);
    display.print(SUBMENU[setMenuFnIndex(indexSelector.menu, subMenu) + 1], 0, 1);
  }
}

void fn402() {
  display.print("402");
}

void fn403() {
  display.print("403");
}

void fn404() {
  display.print("404");
}

void fn501() {
  display.print("501");
}

void fn502() {
  display.print("502");
}

void fn503() {
  display.print("503");
}

void fn504() {
  display.print("504");
}

  // void printPause() {
  //   if(!display.blinking) display.print("                ", mainTitle.x, pause.y );
  //   display.blink(pause.label, pause.x, pause.y);
  //   display.blinking = true;
  // }

  // Serial.print("indexSelector.menu");
  // Serial.print(" ");
  // Serial.print(indexSelector.menu);
  // Serial.print("    ");
  // Serial.print("setMenuFnIndex");
  // Serial.print(" ");
  // Serial.println(setMenuFnIndex(indexSelector.menu,indexSelector.subMenu));

#endif

//https://scienceprog.com/how-to-write-an-lcd-menu-for-avr-in-c/