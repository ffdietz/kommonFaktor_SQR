#include "global.h"
#include "menu.h"
#include "utils.h"

bool debug =  true;
bool updateDisplay = false;

void debugger()
{
  // serial("indexSelector.menu ", indexSelector.menu );
  // serial("indexSelector.subMenu ", indexSelector.subMenu );

  // serial("currentPosition", stepButtonPanel.currentState );
  // serial("sequencer.paused ", sequencer.paused ); 
  // serial("sequencer.isPaused() ", sequencer.isPaused() );
  // serial("getStatesAndPosition ", sequencer.getStatesAndPosition());
  // serial("sequencer.currentBytePosition ", sequencer.currentBytePosition );

  // Serial.print(" getStatesAndPosition ");
  //   printByte(sequencer.getStatesAndPosition());

  // Serial.println();
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
    int position = sequencer.getCurrentPosition();

    bool stepOn = bitRead(state, position);


    if (stepOn) {
      mux.unmute();
    }
    else mux.mute();

    mux.selector(sequencer.getCurrentPosition());
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
  
  checkRegister();

  return true;
}

void setup() 
{
  display.begin();
  encoder.begin();
  mux.begin();
  stepButtonPanel.begin();

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