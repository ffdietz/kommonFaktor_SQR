#include "global.h"

//BPM
void fn101() {
  if(!clock.externalClockFlag){
    if(menu.selectFunction) {
      clock.setSpeedInBpm(encoder.getDirection());
      display.print(clock.getSpeed(), 0, 1);
      
      if(menu.setFunction) menu.escape();
    } else {
      display.print(clock.getSpeed());
      display.print("[INT]", 11, 1);
    }
  } else {
    if(menu.selectFunction){
      display.print("[EXT]", 0, 1);
    } else {
      display.print(clock.millisToBpm(clock.externalClockMillis));
      display.print("[EXT]", 11, 1);
    }
  }
}
// CURRENT STEP
void fn201() {
  if(menu.selectFunction) {
    clock.pause();
    // byte currentActiveSteps = stepButtonPanel.check();
    // if(currentActiveSteps){
    // sequencer.setManualStep(currentActiveSteps);
    // } else 
    sequencer.setManualStep(encoder.getDirection());

    multiplexer.unmute();
    multiplexer.selector(sequencer.getCurrentPosition());

    display.print(sequencer.getCurrentPosition() + 1, 0, 1);
    
    if(menu.setFunction) menu.escape();
  } else {
    clock.play();
    display.print(sequencer.getCurrentPosition() + 1);
  }
}
// SEQUENCE
void fn301() {
  static int subMenu = 0;
  if(menu.selectFunction) {
    subMenu += encoder.getDirection();
    // SUBMENU[] labels range
    subMenu = constrain(subMenu, 0, 3);

    display.print(menu.SUBMENU[subMenu], 0, 1);

    if(menu.setFunction){
      sequencer.setSequenceMode(subMenu);
      menu.escape();
    }
  } else {
    display.print(menu.SUBMENU[subMenu]);
  }
}
// CLOCK FACTOR
void fn401() {
  static int subMenu = 6;
  if(menu.selectFunction) {
    subMenu += encoder.getDirection();
    subMenu = constrain(subMenu, 0, 12);
    
    if(menu.setFunction){
      clock.setInternalFactor(subMenu);
      menu.escape();
    }
    
    display.print(menu.SUBMENU[4], 0, 1);
    display.print(" ");
    display.print(menu.FACTOR[subMenu]);
  } else {
    display.print(menu.FACTOR[subMenu], 13, 1);
  }
}
//RESET STEPS
void fn501() {
  static int subMenu = 0;
  if(menu.selectFunction) {
    subMenu += encoder.getDirection();
    subMenu = constrain(subMenu, 6, 8);
    if(menu.setFunction){
      if(subMenu == 6) sequencer.resetSequence(ALL_ON);
      if(subMenu == 7) sequencer.resetSequence(ALL_OFF);
      if(subMenu == 8) menu.escape();
      menu.escape();
    }
    display.print(menu.SUBMENU[subMenu], 0, 1);
  }
}


void fn502() {
  display.print(menu.SUBMENU[5], 0, 1);
  display.print("502");
}

// void fn501() {
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
//   display.lcd->write(byte(1));
// }