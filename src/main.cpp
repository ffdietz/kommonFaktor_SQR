#include "global.h"
#include "menu.h"

bool debug =  true;

void debugger()
{
  
  Serial.print("  sequenceMode ");  Serial.print(sequencer.sequenceMode);
  Serial.print("  indexSelector.menu ");  Serial.print(indexSelector.menu);
  Serial.print("  indexSelector.subMenu ");  Serial.print(indexSelector.subMenu);
  // Serial.print("  sequencer.getCurrentStep ");  Serial.print(sequencer.getCurrentPosition());
  // Serial.print("  sequencer.stepsLength ");  Serial.print(sequencer.stepsLength);
  // Serial.print("  sequencer.internalClock ");   Serial.print(sequencer.internalClock());
  // Serial.print("  shiftRegister.output ");      Serial.print(stepControl.output, BIN);
  // Serial.print("  sequencer.currentStep ");     Serial.print(sequencer.stepPosition);
  // Serial.print("  steps ");                     Serial.print(sequencer.stepsLength);
  
  Serial.println();
}

void print() 
{
  // if(sequencer.paused) Menu::printPause();
    printMenu();

}

void updateRegister()
{
  if(sequencer.isStepChanged()) stepControl.write(sequencer.getCurrentPosition());
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
  stepControl.check();
}
void checkPause() 
{
  pauseButton.check();
  if(pauseButton.active)
    sequencer.pauseSequence();
  else
    sequencer.playSequence();
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
  check();
  update();
  print();

  if(debug) debugger();

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
  stepControl.begin();
  display.begin();

  menuInit();


  restart();
}


void loop() 
{
  while (
    running()
  );
}