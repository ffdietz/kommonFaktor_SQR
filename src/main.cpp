#include "global.h"
#include "shared.h"


void display() {
  if(sequencer.paused) {
    MenuPrint::printPause();
  }
  // else menu.blinking = false;

  switch(encoder.getData()) {
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
  }
    sequencer.changeStep();
}


void updateParameters() {
  updateSequence();
}


void checkSetEncoder() {
  encoderSetButton.check();
  if(encoderSetButton.active) sequencer.setModeOn();
  else sequencer.setModeOff();

  if(encoder.newDataAvailable()) 
  {
    encoder.getDirection();
  }
}


void checkPause() {
  pauseButton.check();
  if(pauseButton.active) {
    // menu.blinking = true;
    sequencer.pauseSequence();
  }
  else {
    menu.blinking = false;
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
  display();

  return true;
}


void restart() {
  menu.clear();
}


void setup() {
  Serial.begin(9600);
  encoder.begin();
  menu.begin();

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