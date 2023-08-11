#include "global.h"
#include "menu.h"
#include "utils.h"

bool debug =  true;
bool updateDisplay = false;

void debugger()
{
  Serial.print("  indexSelector.menu ");        Serial.print(indexSelector.menu);
  Serial.print("  indexSelector.subMenu ");     Serial.print(indexSelector.subMenu);
  // Serial.print("  sequencer.getCurrentStep ");     Serial.print(sequencer.getCurrentPosition());
  // Serial.print("  encoderSetButton ");          Serial.print(encoderSetButton.isTrigged);
  Serial.print("  getStatesAndPosition ");        printByte(sequencer.getStatesAndPosition());
  // Serial.print("  sequenceMode ");              Serial.print(sequencer.sequenceMode);
  // Serial.print("  sequencer.currentBytePosition ");   Serial.print(sequencer.currentBytePosition);
  Serial.println();
}

void print()
{
  menu();
}

void updateMultiplexer(){
  if(sequencer.isStepChanged())
    mux.selector(sequencer.getCurrentPosition());
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
  if(menuIsSetMode()) menuFunction();
}
void update() 
{
  updateVariables();
  updateSequence();
  // updateRegister();
  updateMultiplexer();
}

void checkEncoder()
{
  if(encoder.newDataAvailable()){
    if(!setMenuMode) selectMenuIndex(encoder.getDirection());
    else menuFunction();
    clearMenu();
    print();
  };
}
void checkSetEncoder() 
{
  encoderSetButton.check();
  if(encoderSetButton.isTrigged)
  {
    setMenuMode = encoderSetButton.active;
    clearMenu();
    print();
  }
}
void checkRegister()
{
  // wrong logic in getStepStates + currentPosition to setStepsState
  // check is saving 0 in all states when no input
  // only when serial.print stepregister works as expected
  stepRegister.keepOutputValue(sequencer.getStatesAndPosition());
  byte currentActiveSteps = stepRegister.check();
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

void setup() 
{
  if(debug){
    Serial.begin(9600);
    Serial.println("serial connected");
  }
  display.begin();
  encoder.begin();
  mux.begin();
  stepRegister.begin();

  menuInit();

}

void loop() 
{
  while (
    running()
  );
}