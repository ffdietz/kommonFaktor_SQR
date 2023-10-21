#include "global.h"

// IMPROVEMENTS
///// menu class
// Switch library for set button double press
// funcion ALL_ON ALL_OFF
// custom sequence from steps panel
// Encoder library

bool debug =  true;

void debugger()
{
  Serial.print(" isSinglePushed ");
  Serial.print(encoderSetButton.isSinglePushed);
  Serial.print(" isDoublePushed ");
  Serial.print(encoderSetButton.isDoublePushed);
  Serial.print(" singleLatch ");
  Serial.print(encoderSetButton.singlePressLatch);
  Serial.print(" doubleLatch ");
  Serial.print(encoderSetButton.doublePressLatch);
  Serial.println();
}

void print()
{
  menu.pause(pauseButton.singlePressLatch);
  menu.print();
  
  sequencer.clockOutput();
}

void updateMultiplexer()
{
  if(!menu.setMenuFunction) {
    byte state = sequencer.getStepsState();
    int position = sequencer.getCurrentPosition();

    bool stepOn = bitRead(state, position);

    if (stepOn) multiplexer.unmute();
    else        multiplexer.mute();

    multiplexer.selector(sequencer.getCurrentPosition());
  }
}
void updateSequence() 
{
  sequencer.updateClock();
  if(sequencer.internalClock() && !pauseButton.singlePressLatch && !sequencer.paused) {
    sequencer.changeStep();
  }
}
void updateVariables() 
{
  if(menu.isSetMode()) menu.menuFunction();
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
    if(!menu.setMenuFunction) menu.selectMenuIndex(encoder.getDirection());
    else menu.menuFunction();
    
    menu.clear();
    print();
  };
}
void checkSetEncoder() 
{
  encoderSetButton.check();
  if(encoderSetButton.isSinglePushed)
  {
    menu.setMenuFunction = encoderSetButton.singlePressLatch;
    menu.clear();
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
  if(pauseButton.isSinglePushed) 
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
  display.begin();
  encoder.begin();
  multiplexer.begin();
  stepButtonPanel.begin();

  menu.begin();

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