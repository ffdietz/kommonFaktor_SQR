#include "global.h"

// TASKS
// clock input
// custom sequence from steps panel
// Encoder library with acceleration

bool debug =  true;

void debugger()
{
  // Serial.print(" external ");
  // Serial.print(clock.external());
  // Serial.print(" externalClockInput ");
  // Serial.print(clock.externalClockInput);

  Serial.println();
}

void print()
{
  menu.pause(pauseButton.singlePressActive);
  menu.print();
}

void updateMultiplexer()
{
  if(!menu.selectFunction) {
    byte state = sequencer.getStepsState();
    int position = sequencer.getCurrentPosition();

    bool stepOn = bitRead(state, position);

    if(stepOn) multiplexer.unmute();
    else        multiplexer.mute();

    multiplexer.selector(sequencer.getCurrentPosition());
  }
}
void updateSequence() 
{
  clock.update();
  if(clock.flag
    && !clock.paused
    && !pauseButton.singlePressActive ) {
    sequencer.changeStep();
  }
  clock.output();
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
    if(!menu.selectFunction) menu.selectMenuIndex(encoder.getDirection());
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
    menu.setFunction = true;
    menu.clear();
    print();
    menu.escape();
  } 
  else if(encoderSetButton.isSinglePushed)
  {
    menu.selectFunction = true;
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
void checkClock(){
  clock.check();
}

void checkPause() 
{
  pauseButton.check();
  if(pauseButton.isSinglePushed) 
    clock.pause();
  else 
    clock.play();
}
void check() 
{
  checkPause();
  checkClock();
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
  clock.begin();

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