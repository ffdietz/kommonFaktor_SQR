#include "global.h"
#include "menu.h"
#include "utils.h"

bool debug =  true;
bool updateDisplay = false;

void debugger()
{
  // serial("getStatesAndPosition ", sequencer.getStatesAndPosition());
  // serial("stepButtonPanel.check ", stepButtonPanel.check());
  // Serial.print(" getStatesAndPosition "); printByte(sequencer.getStatesAndPosition());

  // Serial.println();
}

void print()
{
  menuPaused(pauseButton.active);
  menu();

  if(sequencer.isStepChanged()) sequencer.clockOutput();
}

void updateMultiplexer()
{
  if(!setMenuFunction) {
    byte state = sequencer.getStepsState();
    int position = sequencer.getCurrentPosition();

    bool stepOn = bitRead(state, position);

    if (stepOn) mux.unmute();
    else        mux.mute();

    mux.selector(sequencer.getCurrentPosition());
  }
}
void updateSequence() 
{
  sequencer.updateClock();
  if(sequencer.internalClock() && !pauseButton.active && !sequencer.paused) {
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
  updateMultiplexer();
}

void checkEncoder()
{
  if(encoder.newDataAvailable()){
    if(!setMenuFunction) selectMenuIndex(encoder.getDirection());
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
    setMenuFunction = encoderSetButton.active;
    clearMenu();
    print();
  }
}
void checkRegister()
{
  stepButtonPanel.keepOutputValue(sequencer.getStatesAndPosition());
  byte currentActiveSteps = stepButtonPanel.check();
  sequencer.setStepsState(currentActiveSteps);

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
  if(debug) debugger();
  check();
  update();
  print();
  
  return true;
}

void setup() 
{
  sequencer.begin();
  stepButtonPanel.begin();
  display.begin();
  encoder.begin();
  mux.begin();

  menuInit();

  check();
  update();

  if(debug){
    Serial.begin(115200);
    Serial.println("serial connected");
  }

}

void loop() 
{
  while (
    running()
  );
}