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
  const uint8_t MN000[] = "STEP SEQUENCER\0";
  //menu 1
  const uint8_t MN100[] = "BPM:\0";
  //menu 2
  const uint8_t MN200[] = "CURRENT STEP:\0";
  //menu 3
  const uint8_t MN300[] = "ACTIVE STEPS:\0";
  //menu 4
  const uint8_t MN400[] = "CLOCK:\0";
  //Submenus of menu 4
  const uint8_t MN401[] = "INTERNAL\0";
  const uint8_t MN402[] = "EXTERNAL\0";
  const uint8_t MN403[] = "DIVIDED\0";
  const uint8_t MN404[] = "MULTIPLIED\0";
  //menu 5
  const uint8_t MN500[] = "SEQUENCE:\0";
  //Submenus of menu 5
  const uint8_t MN501[] = "LINEAR\0";
  const uint8_t MN502[] = "INVERT\0";
  const uint8_t MN503[] = "RANDOM\0";
  const uint8_t MN504[] = "CUSTOM\0";


  const uint8_t *MENU[] = 
  {
    MN000,
    MN100,
    MN200,
    MN300,
    MN400,
    MN500,
  };

  const uint8_t *SUBMENU[] = 
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

  uint8_t setMenuFnIndex(uint8_t menu, uint8_t submenu)
  {
    uint8_t indexOutput = 0;

    for(uint8_t i = 0 ; i < (menu - 1) ; i++ )
      indexOutput += MENU_LENGTH[i + 1];

    return indexOutput;
  }

  void clearMenu()
  {
    display.clear();
  }

  void printMenu()
  { 
    display.print(MENU[indexSelector.menu], 0, 0);
    // display.lcd->setCursor(10,0);
    // display.lcd->print(encoder.getPosition());
    // display.print(indexSelector.subMenu, 0, 10);
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