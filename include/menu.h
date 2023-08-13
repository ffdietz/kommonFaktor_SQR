#ifndef MENU__H_
#define MENU__H_
#include "global.h"

typedef void (*funcPointer)(void);
//function pointer
funcPointer menuFunction;
bool setMenuFunction = false;
char * dataOut;

//Structure describes current menu and submenu state
struct menuIndexSelector
{
  uint8_t menu;
  uint8_t subMenu;
} indexSelector;

// Menu Labels
//menu 0
const char * MN000 = "MUX_SQR";
//menu 1
const char * MN100 = "BPM ";
//menu 2
const char * MN200 = "STEP ";
//menu 3
const char * MN300 = "SEQUENCE ";
//Submenus of menu 4
const char * MN301 = "LINEAR";
const char * MN302 = "INVERT";
const char * MN303 = "RANDOM";
const char * MN304 = "CUSTOM";
//menu 4
const char * MN400 = "STEPS ";
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
  MN301, MN302, MN303, MN304,
  MN501, MN502, MN503, MN504,
};

const uint8_t MENU_LENGTH[] =
{
  5, // items in menu 1
  1, // items in submenu 1
  1, // items in submenu 2
  1, // items in submenu 3
  1, // items in submenu 4
  1, // items in submenu 5
};

void fn101(void);
void fn201(void);
void fn301(void);
void fn401(void);
void fn501(void);

const funcPointer menuFn[] = {
  fn101, 
  fn201, 
  fn301, 
  fn401, 
  fn501, 
};

bool menuIsSetMode(){
  return setMenuFunction;
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
  if(setMenuFunction){
    indexSelector.subMenu = constrain(indexSelector.subMenu + variation, 
    1, 
    MENU_LENGTH[indexSelector.menu] - 1);
  }
  else {
    indexSelector.menu = constrain(indexSelector.menu + variation, 
    1, 
    MENU_LENGTH[0]);
  }

  menuFunction = *menuFn[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)];
}

void menu()
{
  if(!setMenuFunction){
    display.print(MENU[0], 0, 0);
    display.print(MENU[indexSelector.menu], 0, 1);
  } else {
    display.print(MENU[indexSelector.menu], 0, 0);
    display.print(SUBMENU[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)], 0, 1);
  };

  menuFunction();
}

void menuPaused(bool paused)
{
  if(paused) display.print("PAUSED", 10, 0);
  else display.print("      ", 10, 0);
}

void fn101() {
  if(setMenuFunction) {
    sequencer.setSpeed(encoder.getDirection());
    display.print(sequencer.getSpeed(), 0, 1);
  } else {
    display.print(sequencer.getSpeed());
  }
}

void fn201() {
  if(setMenuFunction) {
    sequencer.pauseSequence();
    sequencer.setManualStep(encoder.getDirection());

    display.print(sequencer.getCurrentPosition() + 1, 0, 1);

  } else {
    sequencer.playSequence();
    display.print(sequencer.getCurrentPosition() + 1);
  }
}

void fn301() {
  static int subMenu = 0;
  if(setMenuFunction) {
    subMenu += encoder.getDirection();
    // SUBMENU[] labels range
    subMenu = constrain(subMenu, 0, 3);

    sequencer.setSequenceMode(subMenu);
    display.print(SUBMENU[subMenu], 0, 1);
  }
}

void fn401() {
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
}

void fn501() {
  static int subMenu = 0;
  if(setMenuFunction) {
    subMenu += encoder.getDirection();
    // SUBMENU[] labels range
    subMenu = constrain(subMenu, 4, 7);

    // sequencer.setSequenceMode(subMenu);
    display.print(SUBMENU[subMenu], 0, 1);
  }
}

#endif

//https://scienceprog.com/how-to-write-an-lcd-menu-for-avr-in-c/