#include "global.h"
#include "shared.h"


void displayPrint() {
  if(sequencer.paused) MenuPrint::printPause();

  if(encoder.newDataAvailable()) MenuPrint::clear();

  switch(encoder.getPosition()){
    case 0:
      MenuPrint::screen1();
      break;

    case 1:
      MenuPrint::screen2();
      break;

    case 2:
      MenuPrint::screen3();
      break;
  }
}


void updateSequence() {
  if (!sequencer.paused && sequencer.internalClock()){
    sequencer.changeStep();
  }
}


void updateParameters() {
  updateSequence();
}


void checkSetEncoder() {
  encoderSetButton.check();

  if(encoderSetButton.active) sequencer.setModeOn();
  else sequencer.setModeOff();

  // if(encoder.newDataAvailable()) 
  // {
  //   encoder.getDirection();
  // }
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
  displayPrint();

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