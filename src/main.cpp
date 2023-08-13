#include "global.h"
#include "menu.h"
#include "utils.h"

bool debug =  true;
bool updateDisplay = false;

void debugger()
{
  // serial("", );
  // serial("indexSelector.menu ", indexSelector.menu );
  // serial("indexSelector.subMenu ", indexSelector.subMenu );
  // serial("pauseButton.active ", pauseButton.active );
  // serial("sequencer.paused ", sequencer.paused ); 
  serial("sequencer.paused ", sequencer.clockOutValue ); 
  // serial("sequencer.isPaused() ", sequencer.isPaused() );
  // serial("getStatesAndPosition ", sequencer.getStatesAndPosition());
  // serial("sequencer.currentBytePosition ", sequencer.currentBytePosition );
  // serial("lastState ", pauseButton.lastState);
  // serial("current ", pauseButton.currentState);
  // serial("trigged ", pauseButton.isTrigged);
  // serial("active ", pauseButton.active);
  // serial("analogRead ", analogRead(PAUSE_BUTTON));

  Serial.print("  getStatesAndPosition ");
    printByte(sequencer.getStatesAndPosition());

  Serial.println();
}

void print()
{
  menuPaused(pauseButton.active);
  menu();
}

void updateMultiplexer()
{
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
  if(sequencer.internalClock() && !pauseButton.active && !sequencer.paused)
  {
    sequencer.changeStep();
  }

  sequencer.clockOut();
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
  if(pauseButton.active){
    sequencer.pauseSequence();
  }
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
  display.begin();
  encoder.begin();
  mux.begin();
  stepRegister.begin();

  menuInit();

  if(debug){
    Serial.begin(9600);
    Serial.println("serial connected");
    debugger();
  }

}

void loop() 
{
  while (
    running()
  );
}