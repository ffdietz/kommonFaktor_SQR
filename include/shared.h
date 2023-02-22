#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"

struct MenuField {
  unsigned int x;
  unsigned int y;
  const char * label;
};

class Menu {
  public:
    static constexpr MenuField bpm = {0, 1, "BPM:"};
    static constexpr MenuField clockOptionTitle = {0, 0, "CLOCK OPTIONS"};
    static constexpr MenuField mainTitle = {0, 0, "STEP SEQUENCER"};
    static constexpr MenuField pause = {0, 0, "PAUSE"};
    static constexpr MenuField step = {10, 1, "STEP:"};
    static constexpr MenuField stepStatesTitle = {0, 0, "ACTIVE STEPS"};

    static void clear(){
      display.clear();
    }

    static void selectScreen(uint8_t index) {
      switch(index % 4){
        case 0:
          screen1();
          break;

        case 1:
          screen2();
          break;

        case 2:
          screen3();
          break;
      }
    }

    static void printIsSetMode() {
      if(!display.blinking) display.print("                ", 0, 1 );
      display.blink("SET MODE", 0, 1);
      display.blinking = true;
    }

    static void printPause() {
      if(!display.blinking) display.print("                ", mainTitle.x, pause.y );
      display.blink(pause.label, pause.x, pause.y);
      display.blinking = true;
    }

    static void screen1() {
      if(!display.blinking) display.print(mainTitle.label, mainTitle.x, mainTitle.y );

      display.print(bpm.label, bpm.x, bpm.y);
      display.print(sequencer.getSpeed());

      display.print(step.label, step.x, step.y);
      display.print(sequencer.getCurrentStep());

    }

    static void screen2() {
      if(!display.blinking) display.print(stepStatesTitle.label, stepStatesTitle.x, stepStatesTitle.y );
      
      display.print("0 0 0 0 0 0 0 0", 0, 1);
    }

    static void screen3() {
      if(!display.blinking) display.print(clockOptionTitle.label, clockOptionTitle.x, clockOptionTitle.y );
    
      display.print("    screen 3    ", 0, 1);
    }

};

#endif