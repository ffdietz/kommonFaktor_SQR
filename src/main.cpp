#include "global.h"
#include "menu.h"
#include "utils.h"

bool debug =  true;

void debugger()
{
  Serial.print("  indexSelector.menu ");        Serial.print(indexSelector.menu);
  Serial.print("  indexSelector.subMenu ");     Serial.print(indexSelector.subMenu);
  // Serial.print("  sequenceMode ");              Serial.print(sequencer.sequenceMode);
  // Serial.print("  sequencer.currentBytePosition ");   Serial.print(sequencer.currentBytePosition);
  Serial.print("  sequencer.getCurrentStep ");  Serial.print(sequencer.getCurrentPosition());
  Serial.print("  position ");  printByte(sequencer.getStatesAndPosition());
  // Serial.print("  sequencer.getStepsState ");   Serial.print(sequencer.getStepsState(), BIN);
  // Serial.print("  sequencer.internalClock ");   Serial.print(sequencer.internalClock());
  // Serial.print("  shiftRegister.output ");      Serial.print(stepRegister.output, BIN);
  // Serial.print("  stepPosition ");              Serial.print(stepPosition);
  // Serial.print("  steps ");                     Serial.print(sequencer.stepsLength);
  Serial.println();
}

void print() 
{
  // if(sequencer.paused) Menu::printPause();
  // if(screenHasChange)
    printMenu();

}

void updateMultiplexer(){
  if(sequencer.isStepChanged())
    mux.selector(sequencer.getStatesAndPosition());
}

void updateRegister()
{
  if(sequencer.isStepChanged()) {
    stepRegister.write(sequencer.getStatesAndPosition());
  }
}
void updateSequence() 
{
  sequencer.updateClock();
  if(sequencer.internalClock() && !sequencer.paused)
  {
    sequencer.changeStep();
  }
}
void updateVariables() 
{
  if(menuIsSetMode()) currentFunc();
}

void update() 
{
  updateVariables();
  updateSequence();
  updateMultiplexer();
  updateRegister();
}


void checkEncoder()
{
  if(encoder.newDataAvailable()){
    if(!setMenuMode) selectMenuIndex(encoder.getDirection());
    else currentFunc();
    clearMenu();
  };
}
void checkSetEncoder() 
{
  encoderSetButton.check();
  setMenuMode = encoderSetButton.active;
  clearMenu();
}
void checkRegister()
{
  byte currentActiveSteps = stepRegister.check(sequencer.getStatesAndPosition());
  sequencer.setStepsState(currentActiveSteps);
}
void checkPause() 
{
  pauseButton.check();
  if(pauseButton.active)  sequencer.pauseSequence();
  else  sequencer.playSequence();
}

void check() 
{
  checkPause();
  checkRegister();
  checkSetEncoder();
  checkEncoder();
}


bool running() 
{
  if(debug) debugger();
  check();
  update();
  print();
  

  return true;
}


void restart() 
{
  display.clear();
}


void setup() 
{
  if(debug){
    Serial.begin(9600);
    Serial.println("serial connected");
  }
  encoder.begin();
  stepRegister.begin();
  display.begin();
  mux.begin();

  menuInit();

  restart();

}


void loop() 
{
  while (
    running()
  );
}