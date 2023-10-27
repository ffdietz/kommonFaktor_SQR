#include "global.h"

// TASKS
// (done) menu class
// (done) Switch library for set button double press
// (done) funcion ALL_ON ALL_OFF
// (done) improve menu class to submenu and subsubmenu vector
// (done)improve scape when double press

// clock input
// custom sequence from steps panel
// Encoder library

bool debug =  true;

void debugger()
{
  Serial.print("menu ");
  Serial.print(menu.indexSelector.menu);
  Serial.print(" submenu ");
  Serial.print(menu.indexSelector.subMenu);
  Serial.print(" menuFn ");
  Serial.print(menu.setFunction);
  Serial.print(" single ");
  Serial.print(encoderSetButton.isSinglePushed);
  Serial.print(" double ");
  Serial.print(encoderSetButton.isDoublePushed);

  Serial.println();
}

void print()
{
  menu.pause(pauseButton.singlePressActive);
  menu.print();
  
  sequencer.clockOutput();
}

void updateMultiplexer()
{
  if(!menu.setFunction) {
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
  if(sequencer.internalClock() && !pauseButton.singlePressActive && !sequencer.paused) {
    sequencer.changeStep();
  }
}
void updateVariables() 
{
  if(menu.isSetMode()) menu.functionSelected();
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
    if(!menu.setFunction) menu.selectMenuIndex(encoder.getDirection());
    else menu.functionSelected();
    
    menu.clear();
    print();
  };
}
void checkSetEncoder() 
{
  encoderSetButton.check();
  if(encoderSetButton.isDoublePushed)
  {
    menu.selectFunction = true;
    menu.clear();
    print();
    menu.escape();
  } 
  else if(encoderSetButton.isSinglePushed)
  {
    menu.setFunction = true;
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