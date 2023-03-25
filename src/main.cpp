#include "global.h"
#include "menu.h"

// encoder.getDirection() not working
// typo bug in shared.h printMenu()

void print() 
{
  printMenu();
  // if(sequencer.paused) Menu::printPause();

  // (encoder.newDataAvailable() && sequencer.setMode == false)
  // ? Menu::clear()
  // : Menu::selectScreen(encoder.getPosition());
}


void updateSequence() 
{
  if(sequencer.internalClock() && !sequencer.paused)
  {
    sequencer.changeStep();
  }
}


void updateVariables() 
{

}


void update() 
{
  if(sequencer.isSetMode()) updateVariables();
  updateSequence();
}


void checkEncoder()
{
  if(encoder.newDataAvailable())
  {
    selectMenuIndex(encoder.getDirection());
    clearMenu();
  };
}

void checkSetEncoder() 
{
  encoderSetButton.check();

  if(encoderSetButton.active)
  {
    sequencer.setModeOn();
  } 
  else
  {
    sequencer.setModeOff();
  }
}


void checkPause() 
{
  pauseButton.check();

  if(pauseButton.active)
    sequencer.pauseSequence();
  else
    sequencer.restartSequence();
}


void check() 
{
  checkPause();
  checkSetEncoder();
  checkEncoder();
}


bool running() {
  check();
  update();
  print();

  return true;
}


void restart() {
  display.clear();
}


void setup() {
  Serial.begin(9600);
  
  Serial.println("serial");
  Serial.println("connected");
  Serial.println("");

  encoder.begin();
  display.begin();

  restart();
}


void loop() {
  while (
    running()
  );
}

// STRUCTURE TO SHOW LABEL AND VALUES AND MODIFY BY ENCODER
// SEQUENCER DASHBOARD
// // PLAY/STOP
// // BMPs
// // CURRENT STEP
// // ACTIVE STEPS
// // CLOCK OPTION
// // SEQUENCE OPTION [IN TARGET DEVICE]

// CLOCK OPTIONS
// // INTERNAL CLOCK
// // EXTERNAL CLOCK
// // DIVIDED CLOCK
// // MULTIPLIED CLOCK

// SEQUENCE OPTIONS
// // LINEAR
// // RANDOM SEQUENCE
// // INVERT SEQUENCE
// // RANGE SEQUENCE
// // CUSTOM SEQUENCE