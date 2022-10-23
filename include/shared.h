#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"
#include "coordinates.h"

struct MenuField
{
  uint8_t x;
  uint8_t y;
  const char *label;
};

struct MenuLayout
{
  static const MenuField title = {0, 0, " STEP SEQUENCER "};
  static const MenuField pause = {0, 0, "     PAUSE      "};
  static const MenuField bpm = {0, 1,   "BPM:"};
  static const MenuField step  = {10, 1, "STEP:"};
  static const MenuField stepStatesTitle = {0, 0, "ACTIVE STEPS"};
  static const MenuField clockOptionTitle = {0, 0, "CLOCK OPTIONS"};

  static void printPause(){
    menu.blink(MenuLayout::pause.label, MenuLayout::pause.x, MenuLayout::pause.y);
  }

  static void screen1(){
    menu.print(MenuLayout::title.label, MenuLayout::title.x, MenuLayout::title.y );

    menu.print(MenuLayout::step.label, MenuLayout::step.x, MenuLayout::step.y);
    menu.print(sequencer.getCurrentStep());

    menu.print(MenuLayout::bpm.label, MenuLayout::bpm.x, MenuLayout::bpm.y);
    menu.print(sequencer.speed);
  }

  static void screen2()
  {
    menu.print(MenuLayout::stepStatesTitle.label, MenuLayout::stepStatesTitle.x, MenuLayout::stepStatesTitle.y );
  }

  static void screen3(){
    menu.print(MenuLayout::clockOptionTitle.label, MenuLayout::clockOptionTitle.x, MenuLayout::clockOptionTitle.y );
  }
};

// const MenuField MenuLayout::title = {0, 0, " STEP SEQUENCER "};
// const MenuField MenuLayout::pause 
// const MenuField MenuLayout::bpm   
// const MenuField MenuLayout::step 
// const MenuField MenuLayout::stepStatesTitle  
// const MenuField MenuLayout::clockOptionTitle 


// void MenuLayout::screen3()
// {
//   menu.print(MenuLayout::stepStatesTitle.label, MenuLayout::stepStatesTitle.x, MenuLayout::stepStatesTitle.y );
// }

#endif

// struct Label
// {
//   static const char *title;
//   static const char *bpm;
//   static const char *pause;
//   static const char *step;
//   static const char *stepStateTitle;
//   static const char *clockOptionTitle;
//   static const char *localClear1;
//   static const char *localClear2;
//   static const char *localClear3;
//   static const char *localClear4;

//   static const Coordinates titlePos;
//   static const Coordinates bpmPos;
//   static const Coordinates pausePos;
//   static const Coordinates stepPos;
//   static const Coordinates stepStatesPos;
// };

// const char *Label::title
// const char *Label::bpm =
// const char *Label::pause
// const char *Label::step
// const char *Label::stepStateTitle
// const char *Label::clockOptionTitle
// const char *Label::localClear1 = " ";
// const char *Label::localClear2 = "  ";
// const char *Label::localClear3 = "   ";
// const char *Label::localClear4 = "    ";

// const Coordinates Label::bpmPos
// const Coordinates Label::pausePos
// const Coordinates Label::stepPos
// const Coordinates Label::stepStatesPos