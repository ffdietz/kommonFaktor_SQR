#include "global.h"
#include "shared.h"

void printStepPositionBar()
{
  menu.print(MenuLayout::step.label, MenuLayout::step.x, MenuLayout::step.y);
  menu.print(sequencer.getCurrentStep());
}


void printPause()
{
  menu.blink(MenuLayout::pause.label, MenuLayout::pause.x, MenuLayout::pause.y);
}


void printSpeedBar()
{
  menu.print(MenuLayout::bpm.label, MenuLayout::bpm.x, MenuLayout::bpm.y);
  menu.print(sequencer.speed);
}


void printTitleBar()
{
  menu.print(MenuLayout::title.label, MenuLayout::title.x, MenuLayout::title.y );
}


void printStaticData()
{
  printTitleBar();
}


void display()
{
  printStaticData();
  printStepPositionBar();
}


void updateSequence()
{
  if (!sequencer.paused && sequencer.internalClock())
  {
    sequencer.changeStep();
  }
}


void updateParameters()
{
  updateSequence();
}


void checkEncoder()
{
  encoderSet.check();

  if(encoderSet.activated)
  {
    // lcd.setCursor(0, 0);
    // lcd.print('E');
    menu.print(encoder.getData());
  }

  else
  {
    // lcd.setCursor(0, 0);
    // lcd.print('U');
  }
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


void update()
{
  updateParameters();
}


void check()
{
  checkPause();
  checkEncoder();
}


bool running()
{
  check();
  update();
  display();

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