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
  if(sequencer.isSetMode()) CurrentFunc();
}


void update() 
{
  updateVariables();
  updateSequence();
}


void checkEncoder()
{
  if(encoder.newDataAvailable()){
    if(!sequencer.isSetMode()) selectMenuIndex(encoder.getDirection());
    clearMenu();
  };
}

void checkSetEncoder() 
{
  if(encoderSetButton.check()){
    if(encoderSetButton.active){
      sequencer.setModeOn();
      menuSetModeOn();
    } 
    else {
      sequencer.setModeOff();
      menuSetModeOff();
    }
    clearMenu();
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

  menuInit();

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