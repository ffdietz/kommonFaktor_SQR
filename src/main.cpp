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
  serial("stepRegister.check ", stepRegister.check() );
  // serial("pauseButton.active ", pauseButton.active );
  // serial("sequencer.paused ", sequencer.paused ); 
  // serial("sequencer.paused ", sequencer.clockOutState ); 
  // serial("sequencer.isPaused() ", sequencer.isPaused() );
  // serial("getStatesAndPosition ", sequencer.getStatesAndPosition());
  // serial("sequencer.currentBytePosition ", sequencer.currentBytePosition );
  // serial("lastState ", pauseButton.lastState);
  // serial("current ", pauseButton.currentState);
  // serial("trigged ", pauseButton.isTrigged);
  // serial("active ", pauseButton.active);
  // serial("analogRead ", analogRead(PAUSE_BUTTON));

  // Serial.print(" getStatesAndPosition ");
  //   printByte(sequencer.getStatesAndPosition());

  Serial.println();
}

void print()
{
  menuPaused(pauseButton.active);
  menu();
}

void updateMultiplexer()
{
  if(!setMenuFunction) {
    byte state = sequencer.getStepsState();
    uint8_t position = sequencer.getCurrentPosition();

    uint8_t stepOn = bitRead(state, position);

    if(stepOn) {
      mux.unmute();
      mux.selector(sequencer.getCurrentPosition());
    }
    else mux.mute();

  // if(muxOutput)  mux.unmute();
  // else  mux.mute();}
  }
}
// void updateRegister()
// {
//   if(sequencer.isStepChanged()) {
//     stepRegister.write(sequencer.getStatesAndPosition());
//   }
// }
void updateSequence() 
{
  sequencer.updateClock();
  if(sequencer.internalClock() && !pauseButton.active && !sequencer.paused) {
    sequencer.changeStep();
  }
  
  if(sequencer.isStepChanged()) sequencer.clockOutput();
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
  // only when serial.print stepregister works as expected
  // affects BPMs over 99
  stepRegister.keepOutputValue(sequencer.getStatesAndPosition());
  byte currentActiveSteps = stepRegister.check();
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
  display.begin();
  encoder.begin();
  mux.begin();
  stepRegister.begin();

  menuInit();

  if(debug){
    Serial.begin(115200);
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