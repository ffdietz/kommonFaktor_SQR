#include "global.h"
#include "shared.h"

void displaySettings()
{
}

void printTitleBar()
{
  menu.print(" STEP SEQUENCER ", 0, 0);
}

void printPause()
{
  menu.print("  PAUSE  ", 7, 1);
}

void printSpeedBar()
{
  menu.print("BPM:", 7, 1);
  menu.print(sequencer.speed);
}

void printStepPositionBar()
{
  menu.print("STEP:", 0, 1);
  menu.print(sequencer.getCurrentStep());
}

void printStaticData()
{
  printTitleBar();
}

void updateSequence()
{
  if (!sequencer.paused && sequencer.internalClock())
  {
    sequencer.changeStep();
  }
}

void displayPrint()
{
  printStaticData();
  printStepPositionBar();
}

void updateParameters()
{
  updateSequence();
}

void checkEncoder()
{
  // encoderSet.check();

  // if(encoderSet.activated)
  // {
  //   lcd.setCursor(0, 0);
  //   lcd.print('E');
  //   lcd.print(encoder.getData());
  // }

  // else
  // {
  //   lcd.setCursor(0, 0);
  //   lcd.print('U');
  // }
}

void checkPause()
{
  pause.check();

  if(pause.activated)
  {
    sequencer.pauseSequence();
    printPause();
  }

  else
  {
    sequencer.restartSequence();
    printSpeedBar();
  }
}

bool running()
{
  checkPause();
  
  checkEncoder();

  updateParameters();
  
  displayPrint();


  return true;
}

void restart()
{
  menu.clear();
}

void setup()
{
  encoder.begin();
  menu.begin();

  restart();
}

void loop()
{
  while (running());
}

// STRUCTURE TO SHOW LABEL AND VALUES AND MODIFY BY ENCODER

// SEQUENCER DASHBOARD
// // PLAY/STOP
// // BMPs
// // CURRENT STEP
// // ACTIVE STEPS
// // CLOCK OPTION
// // SEQUENCE OPTION [IN TARGET DEVICE]

// SEQUENCE OPTIONS
// // LINEAR
// // RANDOM SEQUENCE
// // INVERT SEQUENCE
// // RANGE SEQUENCE
// // CUSTOM SEQUENCE

// CLOCK OPTIONS
// // INTERNAL CLOCK
// // EXTERNAL CLOCK
// // DIVIDED CLOCK
// // MULTIPLIED CLOCK
