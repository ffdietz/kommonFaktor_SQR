#include "global.h"
#include "utils.h"

bool debug =  true;

void debugger()
{
  // serial(" externalMillis ", clock.externalClockMillis);
  // serial(" externalFlag ", clock.externalClockFlag);
  // serial(" single ", encoderSetButton.singlePressActive);

  // Serial.println();
}

void print()
{
  menu.pause(pauseButton.singlePressActive);
  menu.print();
  menu.functionSelected();
}

void updateMultiplexer()
{
  if(!menu.selectFunction) {
    byte state = sequencer.getStepsState();
    int position = sequencer.getCurrentPosition();

    bool stepOn = bitRead(state, position);

    if(stepOn) 
      multiplexer.unmute();
    else
      multiplexer.mute();

    multiplexer.selector(sequencer.getCurrentPosition());
  }
}
void updateSequence() 
{
  clock.update();
  if(
    clock.flag
    && !clock.paused
    && !pauseButton.singlePressActive 
  ) {
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
    if(!menu.selectFunction) 
      menu.selectMenuIndex(encoder.getDirection());
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
    menu.print();
    menu.functionSelected();
    menu.escape();
  } 
  if(encoderSetButton.isSinglePushed)
  {
    menu.selectFunction = true;
    menu.clear();
    menu.print();
    menu.functionSelected();
  }
}
void checkRegister()
{
  stepButtonPanel.keepOutput(sequencer.getStepsAndPosition());
  byte activeSteps = stepButtonPanel.check();
  sequencer.setStepsState(activeSteps);

}
void checkClock()
{
  clock.check();
}
void checkPause() 
{
  pauseButton.check();
  if(pauseButton.singlePressActive) 
    clock.pause();
  else 
    clock.play();
}
void check() 
{
  checkPause();
  checkSetEncoder();
  checkEncoder();
  checkClock();
  checkRegister();
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
  clock.begin();
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