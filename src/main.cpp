#include "global.h"
#include "shared.h"


void print() {
  if(sequencer.paused) Menu::printPause();

  encoder.newDataAvailable() && !sequencer.isSetMode()
  ? Menu::clear()
  : Menu::selectScreen(encoder.getPosition());

}

void updateVariables() {
  if(sequencer.isSetMode()){
    sequencer.setSpeed(encoder.getDirection() * 0.1);
  }
}

void updateSequence() {
  if (sequencer.internalClock() && !sequencer.paused ){
    sequencer.changeStep();
  }
}


void updateParameters() {
  updateVariables();
  updateSequence();
}


void checkSetEncoder() {
  encoderSetButton.check();
  if(encoderSetButton.active) sequencer.setModeOn();
  else sequencer.setModeOff();
}


void checkPause() {
  pauseButton.check();
  if(pauseButton.active) {
    sequencer.pauseSequence();
  }
  else {
    display.blinking = false;
    sequencer.restartSequence();
  }
}


void update() {
  updateParameters();
}


void check() {
  checkPause();
  checkSetEncoder();
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