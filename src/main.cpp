#include "global.h"
#include "shared.h"

void displaySettings()
{
}

void printTitleBar()
{
  lcd.setCursor(0, 0);
  lcd.print(" STEP SEQUENCER ");
}

void printPause()
{
  lcd.setCursor(7, 1);
  lcd.print("  PAUSE  ");
}

void printSpeedBar()
{
  lcd.setCursor(7, 1);
  lcd.print("BPM:");
  lcd.print(sequencer.getSpeed());
}

void printStepPositionBar()
{
  lcd.setCursor(0, 1);
  lcd.print("STEP:");
  lcd.print(sequencer.getCurrentStep());
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

void checkEncoderEnable()
{
  encoderSet.check();

  if (encoderSet.activated)
  {
    lcd.setCursor(0, 0);
    lcd.print('E');
    lcd.print(encoder.getData());
  }

  else
  {
    lcd.setCursor(0, 0);
    lcd.print('U');
  }
}

void checkPause()
{
  pause.check();

  if (pause.activated)
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

void updateParameters()
{
  updateSequence();
}

bool running()
{
  checkPause();
  checkEncoderEnable();

  updateParameters();
  displayPrint();

  return true;
}

void restart()
{
  lcd.clear();
}

void setup()
{
  lcd.begin(LCD_CHARS, LCD_LINES);
  encoder.begin();

  restart();
}

void loop()
{
  while (running())
    ;
}

// STRUCTURE TO SHOW LABEL AND VALUES AND MODIFY BY ENCODER

// SEQUENCER DASHBOARD
// // PLAY/STOP
// // BMPs
// // CURRENT STEP
// // ACTIVE STEPS
// // SEQUENCE OPTION
// // CLOCK OPTION

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
