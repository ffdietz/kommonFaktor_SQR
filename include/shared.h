#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"
#include "coordinates.h"

struct MenuField {
  unsigned int x;
  unsigned int y;
  const char *label;
};

struct MenuData {
  static constexpr MenuField title = {0, 0, "STEP SEQUENCER"};
  static constexpr MenuField pause = {0, 0, "PAUSE"};
  static constexpr MenuField bpm = {0, 1, "BPM:"};
  static constexpr MenuField step = {10, 1, "STEP:"};
  static constexpr MenuField stepStatesTitle = {0, 0, "ACTIVE STEPS"};
  static constexpr MenuField clockOptionTitle = {0, 0, "CLOCK OPTIONS"};
};

class MenuPrint {
  public:
    static void printPause() {
    if(!menu.blinking) menu.print("                ", MenuData::pause.x, MenuData::pause.y );

    menu.blinking = true;
    menu.blink(MenuData::pause.label, MenuData::pause.x, MenuData::pause.y);
  }

  static void screen1() {
    if(!menu.blinking) menu.print(MenuData::title.label, MenuData::title.x, MenuData::title.y );

    menu.print(MenuData::bpm.label, MenuData::bpm.x, MenuData::bpm.y);
    menu.print(sequencer.getSpeed());

    menu.print(MenuData::step.label, MenuData::step.x, MenuData::step.y);
    menu.print(sequencer.getCurrentStep());

  }

  static void screen2() {
    if(!menu.blinking) 
        menu.print(MenuData::stepStatesTitle.label, MenuData::stepStatesTitle.x, MenuData::stepStatesTitle.y );
  }

  static void screen3() {
    if(!menu.blinking) 
      menu.print(MenuData::clockOptionTitle.label, MenuData::clockOptionTitle.x, MenuData::clockOptionTitle.y );
  }

};

#endif