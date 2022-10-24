#include "global.h"
#include "shared.h"


void display()
{
  if(pauseButton.activated) MenuLayout::printPause();

  else{
    if (encoder.newDataAvailable()) menu.clear();

    switch(encoder.getData()){
      case 0:
        MenuLayout::screen1();
        break;

      case 1:
        MenuLayout::screen2();
        break;

      case 2:
        MenuLayout::screen3();
        break;
    }
  }
}


void updateSequence()
{
  if (!sequencer.paused && sequencer.internalClock()){
    sequencer.changeStep();
  }
}


void updateParameters()
{
  updateSequence();
}


void checkSetEncoder() 
{
  encoderSetButton.check();
  if(encoderSetButton.activated) menu.editMode = true;
  else menu.editMode = false;
}


void checkPause()
{
  pauseButton.check();

  if(pauseButton.activated) sequencer.pauseSequence();
  else sequencer.restartSequence();
}


void update()
{
  updateParameters();
}


void check()
{
  checkPause();
  checkSetEncoder();
}


bool running()
{
  check();
  update();
  display();

  Serial.println(menu.editMode);

  return true;
}


void restart()
{
  menu.clear();
}


void setup()
{
  Serial.begin(9600);
  encoder.begin();
  menu.begin();

  restart();
}


void loop()
{
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