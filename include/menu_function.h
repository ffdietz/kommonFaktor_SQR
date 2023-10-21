#include "global.h"

//BPM
void fn101() {
  if(menu.setMenuFunction) {
    sequencer.setSpeed(encoder.getDirection());
    display.print(sequencer.getSpeed(), 0, 1);
  } else {
    display.print(sequencer.getSpeed());
  }
}

// CURRENT STEP
void fn201() {
  if(menu.setMenuFunction) {
    sequencer.pauseSequence();
    sequencer.setManualStep(encoder.getDirection());

    multiplexer.unmute();
    multiplexer.selector(sequencer.getCurrentPosition());

    display.print(sequencer.getCurrentPosition() + 1, 0, 1);

  } else {
    sequencer.playSequence();
    display.print(sequencer.getCurrentPosition() + 1);
  }
}
// SEQUENCE
void fn301() {
  static int subMenu = 0;
  static int subSubMenu = 0;
  static bool switchFunctionActive = false;

if (menu.setMenuFunction) {
    if (!switchFunctionActive) {
      subMenu += encoder.getDirection();
      subMenu = constrain(subMenu, 0, 4);

      if (subMenu == 4) {
        switchFunctionActive = true;
        subSubMenu += encoder.getDirection();
        subSubMenu = constrain(subSubMenu, 1, 2);
        if (subSubMenu == 1) {
          sequencer.resetSequence(ALL_ON);
          display.print("RESET_ON", 0, 1);
        } else if (subSubMenu == 2) {
          sequencer.resetSequence(ALL_OFF);
          display.print("RESET_OFF", 0, 1);
        }
      } else {
        sequencer.setSequenceMode(subMenu);
        display.print(menu.SUBMENU[subMenu], 0, 1);
      }
    } else {
      if (encoderSetButton.doublePressLatch) {
        switchFunctionActive = false;
        encoderSetButton.doublePressLatch = false;
        menu.clear();
      }
    }
  }
}
// CLOCK
void fn401() {
  static int subMenu = 6;
  if(menu.setMenuFunction) {
    subMenu += encoder.getDirection();
    subMenu = constrain(subMenu, 0, 12);
    sequencer.setInternalClockFactor(subMenu);

    display.print(menu.SUBMENU[4], 0, 1);
    display.print(" ");
    display.print(menu.FACTOR[subMenu]);
  }
}

void fn501() {
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
  display.lcd->write(byte(1));
}

void fn502() {
  static int subMenu = 0;
  if(menu.setMenuFunction) {
    subMenu += encoder.getDirection();
    // SUBMENU[] labels range
    subMenu = constrain(subMenu, 6, 7);

    // sequencer.setSequenceMode(subMenu);
    display.print(menu.SUBMENU[5], 0, 1);
    display.print(menu.SUBMENU[subMenu]);
  }
}
