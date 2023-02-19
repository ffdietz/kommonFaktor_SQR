#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"
#include "coordinates.h"

struct MenuField {
  unsigned int x;
  unsigned int y;
  const char * label;
};

struct MenuLabel {
  static constexpr MenuField mainTitle = {0, 0, "STEP SEQUENCER"};
  static constexpr MenuField stepStatesTitle = {0, 0, "ACTIVE STEPS"};
  static constexpr MenuField clockOptionTitle = {0, 0, "CLOCK OPTIONS"};
  static constexpr MenuField pause = {0, 0, "PAUSE"};
  static constexpr MenuField bpm = {0, 1, "BPM:"};
  static constexpr MenuField step = {10, 1, "STEP:"};
};

class MenuPrint {
  public:
    static void clear(){
      display.clear();
    }

    static void printPause() {
      if(!display.blinking) display.print("                ", MenuLabel::pause.x, MenuLabel::pause.y );
      display.blink(MenuLabel::pause.label, MenuLabel::pause.x, MenuLabel::pause.y);
      display.blinking = true;
    }

    static void screen1() {
      if(!display.blinking) display.print(MenuLabel::mainTitle.label, MenuLabel::mainTitle.x, MenuLabel::mainTitle.y );

      display.print(MenuLabel::bpm.label, MenuLabel::bpm.x, MenuLabel::bpm.y);
      display.print(sequencer.getSpeed());

      display.print(MenuLabel::step.label, MenuLabel::step.x, MenuLabel::step.y);
      display.print(sequencer.getCurrentStep());

    }

  static void screen2() {
    if(!display.blinking) display.print(MenuLabel::stepStatesTitle.label, MenuLabel::stepStatesTitle.x, MenuLabel::stepStatesTitle.y );
    
    display.print("    screen 2    ", 0, 1);
  }

  static void screen3() {
    if(!display.blinking) display.print(MenuLabel::clockOptionTitle.label, MenuLabel::clockOptionTitle.x, MenuLabel::clockOptionTitle.y );
  
    display.print("    screen 3    ", 0, 1);
  }

};

#endif