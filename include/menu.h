#ifndef MENU__H_
#define MENU__H_
#include "global.h"

typedef void (*FunctionPr)(void);
//function pointer
FunctionPr CurrentFunc;
bool setMode = false;

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
  const char * MN101 = "";
  //menu 2
  const char * MN200 = "CURRENT STEP ";
  const char * MN201 = "";
  //menu 3
  const char * MN300 = "ACTIVE STEPS ";
  const char * MN301 = "";
  //menu 4
  const char * MN400 = "CLOCK ";
  //Submenus of menu 4
  const char * MN401 = "INTERNAL";
  const char * MN402 = "EXTERNAL";
  const char * MN403 = "DIVIDED";
  const char * MN404 = "MULTIPLIED";
  //menu 5
  const char * MN500 = "SEQUENCE ";
  //Submenus of menu 5
  const char * MN501 = "LINEAR";
  const char * MN502 = "INVERT";
  const char * MN503 = "RANDOM";
  const char * MN504 = "CUSTOM";


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
    4, // items in submenu 4
    4, // items in submenu 5
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

  const FunctionPr MenuFn[] = 
  {
    fn101, 
    fn201, 
    fn301, 
    fn401, fn402, fn403, &fn404, 
    fn501, fn502, fn503, fn504, 
  };

  void menuSetModeOn(){
    setMode = true;
  }

  void menuSetModeOff(){
    setMode = false;
  }

  void clearMenu()
  {
    display.clear();
  }

    uint8_t setMenuFnIndex(uint8_t menu, uint8_t submenu)
  {
    uint8_t indexOutput = 0;
    for(uint8_t i = 0 ; i < (menu - 1) ; i++ ) 
      indexOutput += MENU_LENGTH[i + 1];
    indexOutput = indexOutput + submenu - 1;

    return indexOutput;
  }

  void selectMenuIndex(int variation)
  {
    if(!setMode){
      indexSelector.menu = constrain(indexSelector.menu + variation, 1, MENU_LENGTH[0] - 1);
      indexSelector.subMenu = 1;
    }
    else {
      indexSelector.subMenu = constrain(indexSelector.subMenu + variation, 1, MENU_LENGTH[indexSelector.menu]);
    }
    
    CurrentFunc = *MenuFn[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)];
  }

  void menuInit()
  {
    indexSelector.menu = 1;
    indexSelector.subMenu = 1;
    clearMenu();
    display.print(MENU[0], 0, 0);
    display.print(SUBMENU[0], 0, 1);

    CurrentFunc = *MenuFn[0];

  }

  void printMenu()
  { 
    if(!setMode){
      display.print(MENU[0], 0, 0);
      display.print(MENU[indexSelector.menu], 0, 1);
    } else {
      display.print(MENU[indexSelector.menu], 0, 0);
      display.print(SUBMENU[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)], 0, 1);
    };

    Serial.print("indexSelector.menu ");
    Serial.print(indexSelector.menu);
    Serial.print("    ");
    Serial.print("setMenuFnIndex ");
    Serial.println(setMenuFnIndex(indexSelector.menu,indexSelector.subMenu));

  }

  void fn101() {
    sequencer.setSpeed(encoder.getDirection());
    display.print(sequencer.getSpeed());
  }

  void fn201() {
    display.print("201");
  }

  void fn301() {
    display.print("301");
  }

  void fn401() {
    display.print("401");
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