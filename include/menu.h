#ifndef MENU__H_
#define MENU__H_
#include "global.h"

typedef void (*FnPr)(void);
//function pointer
FnPr FPr;
//Structure describes current menu and submenu state
struct menuIndexSelector
{
  uint8_t menu;
  uint8_t subMenu;
} indexSelector;

  // Menu Labels
  //menu 0
  const char * MN000 = "STEP SEQUENCER";
  //menu 1
  const char * MN100 = "BPM:";
  //menu 2
  const char * MN200 = "CURRENT STEP:";
  //menu 3
  const char * MN300 = "ACTIVE STEPS:";
  //menu 4
  const char * MN400 = "CLOCK:";
  //Submenus of menu 4
  const char * MN401 = "INTERNAL";
  const char * MN402 = "EXTERNAL";
  const char * MN403 = "DIVIDED";
  const char * MN404 = "MULTIPLIED";
  //menu 5
  const char * MN500 = "SEQUENCE:";
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
    MN401, MN402, MN403, MN404,
    MN501, MN502, MN503, MN504,
  };

  const uint8_t MENU_LENGTH[] =
  {
    6, // items in menu 1
    0, // items in submenu 1
    0, // items in submenu 2
    0, // items in submenu 3
    4, // items in submenu 4
    3, // items in submenu 5
  };

  void fn200(void);
  void fn300(void);
  void fn400(void);
  void fn500(void);
  void fn501(void);
  void fn502(void);
  void fn503(void);
  void fn504(void);
  void fn600(void);
  void fn601(void);
  void fn602(void);
  void fn603(void);
  void fn604(void);

  const FnPr MenuFn[] = 
  {
    fn200, 
    fn300, 
    fn400, 
    fn500, fn501, fn502, fn503, fn504, 
    fn600, fn601, fn602, fn603, fn604, 
  };

  void selectMenuIndex(int variation)
  {
    if(indexSelector.menu < MENU_LENGTH[0])
    { 
      indexSelector.menu += variation;
      indexSelector.subMenu = 1;
    }
    else indexSelector.menu = 1;
  }

  uint8_t setMenuFnIndex(uint8_t menu, uint8_t submenu)
  {
    uint8_t indexOutput = 0;

    for(uint8_t i = 0 ; i < menu - 1 ; i++ )
    {
      indexOutput += MENU_LENGTH[i + 1];
    }

    indexOutput = indexOutput + submenu - 1;

    return indexOutput;
  }

  void clearMenu()
  {
    display.clear();
  }

  void printMenu()
  { 
    display.print(MENU[0], 0, 0);
    display.print(MENU[indexSelector.menu - 1], 0, 1);
    // display.print(SUBMENU[setMenuFnIndex(indexSelector.menu, indexSelector.subMenu)], 0, 1);

    Serial.print("indexSelector.menu");
    Serial.print(" ");
    Serial.print(indexSelector.menu);
    Serial.print(" ");
    Serial.print("setMenuFnIndex");
    Serial.print(" ");
    Serial.println(setMenuFnIndex(indexSelector.menu, indexSelector.subMenu));

  }



    // static void printIsSetMode() {
    //   if(!display.blinking) display.print("                ", 0, 1 );
    //   display.blink("SET MODE", 0, 1);
    //   display.blinking = true;
    // }

    // void printPause() {
    //   if(!display.blinking) display.print("                ", mainTitle.x, pause.y );
    //   display.blink(pause.label, pause.x, pause.y);
    //   display.blinking = true;
    // }

    // void screen1() {
    //   if(!display.blinking) display.print(mainTitle.label, mainTitle.x, mainTitle.y );

    //   display.print(bpm.label, bpm.x, bpm.y);
    //   display.setMode ? display.blink(sequencer.getSpeed()) : display.print(sequencer.getSpeed());

    //   display.print(step.label, step.x, step.y);
    //   display.print(sequencer.getCurrentStep());
    // }

#endif

//https://scienceprog.com/how-to-write-an-lcd-menu-for-avr-in-c/