#include "global.h"
#include "utils.h"

//BPM
void fn101() {
  if(clock.isExternalClock){
    if(menu.selectFunction){
      display.print("[EXT]", 0, 1);
    } else {
      display.print(clock.millisToBpm(clock.externalClockMillis));
      display.print("[EXT]", 11, 1);
    }
  } else {
    if(menu.selectFunction){
      clock.setSpeedInBpm(encoder.getDirection());
      display.print(clock.getSpeed(), 0, 1);
      
      if(menu.setFunction) menu.escape();
    } else {
      display.print(clock.getSpeed());
      display.print("[INT]", 11, 1);
    }
  }
}
// CURRENT STEP
void fn201() {
  if(menu.selectFunction) {
    clock.pause();
    stepButtonPanel.locked();
    stepButtonPanel.check();

    uint8_t position = stepButtonPanel.isKeyPressed ?
      stepButtonPanel.keyPressed : sequencer.getPosition();

    sequencer.setPosition(position);
    sequencer.setPositionVariation(encoder.getDirection());

    multiplexer.unmute();
    multiplexer.selector(sequencer.getPosition());
    
    stepButtonPanel.output(1 << position);
    display.print(sequencer.getPosition() + 1, 0, 1);
    
    if(menu.setFunction){
      stepButtonPanel.unlocked();
      menu.escape();
    }
  } else {
    clock.play();
    display.print(sequencer.getPosition() + 1);
  }
}
// SEQUENCE
void fn301() {
  static byte subMenu = 0;
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
  static byte subMenu = 6;
  if(menu.selectFunction) {
    subMenu += encoder.getDirection();
    // SUBMENU[] labels range
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
  static byte subMenu = 0;
  if(menu.selectFunction) {
    subMenu += encoder.getDirection();
    // SUBMENU[] labels range
    subMenu = constrain(subMenu, 4, 6);
    if(menu.setFunction){
      if(subMenu == 6) sequencer.resetSequence(ALL_ON);
      if(subMenu == 7) sequencer.resetSequence(ALL_OFF);
      if(subMenu == 8) menu.escape();
      menu.escape();
    }
    display.print(menu.SUBMENU[subMenu], 0, 1);
  }
}
//CUSTOM SEQUENCE
void fn601() {
  static byte index = 0;
  byte step = 0;
  if(menu.selectFunction){
    stepButtonPanel.locked();
    stepButtonPanel.check();

    index += encoder.getDirection();
    index = index % 8;

    if(stepButtonPanel.isKeyPressed){
      step = stepButtonPanel.keyPressed;
      sequencer.setStep(index, step);
    }

    for(byte i = 0 ; i < 8 ; i++)
    if(index == i)
      display.blink(sequencer.getStep(i) + 1, i * 2, 1);
    else 
      display.print(sequencer.getStep(i) + 1, i * 2, 1);
    
    if(menu.setFunction){
      stepButtonPanel.unlocked();
      menu.escape();
    }
  }
}

void fn6011(){
  display.print("GENERATE", 0, 1);
}

void fn6012(){
  display.print("SAVE", 0, 1);
}

void fn6013(){
  display.print("LOAD", 0, 1);
}