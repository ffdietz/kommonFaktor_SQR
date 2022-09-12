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

void printStepsBar()
{
  Serial.print("STEPS:");
  Serial.print(sequencer.getStepsQuantity());
  Serial.print(" ");
  // StepsBar::printLabel(&tft, InfoBarData::row1LabelPos, InfoBarData::stepsLabel);
  // StepsBar::printValue(&tft, InfoBarData::row1ValuePos, sequencer.getSteps());
}

void printSpeedBar()
{
  lcd.setCursor(7,1);
  lcd.print("BPM:");
  lcd.print(sequencer.getSpeed());
  // SpeedBar::printLabel(&tft, InfoBarData::row2LabelPos, InfoBarData::speedLabel);
  // SpeedBar::printValue(&tft, InfoBarData::row2ValuePos, sequencer.getSpeed());
}

void printStepPositionBar()
{
  lcd.setCursor(0, 1);
  lcd.print("STEP:");
  lcd.print(sequencer.getCurrentStep());
  // StepPositionBar::printLabel(&tft, InfoBarData::row3LabelPos, InfoBarData::stepPosLabel);
  // StepPositionBar::printValue(&tft, InfoBarData::row3ValuePos, sequencer.getCurrentStep());
}

void printStaticData()
{
  printTitleBar();
  printStepsBar();
  printSpeedBar();
}

void updateSequence()
{
  if(sequencer.internalClock()){
    sequencer.changeStep();
    // sequencer.clockOut();
  }
}

void draw()
{
  printStaticData();
  printStepPositionBar();
}

void update()
{
  updateSequence();
}

void checkPause()
{
  if(control.pausedTriggered())  sequencer.paused();
}

bool running()
{
  // game is paused
  checkPause();
  if (sequencer.isPaused())
  {
    // print PAUSED status message on-screen
    printPause(); 
    while (!control.pausedTriggered()) {}   // wait for play button to play sequence
    
    lcd.setCursor(0, 1);
    lcd.print("                ");
    
    sequencer.restart();
  }

  update();
  draw();

  // delay(FRAME_DELAY); // maintain upper bound to frame rate
  return true;
}

void restart()
{
  printStaticData();
}

void setup()
{
  menuBegin();
  encoder.begin();

  restart();
}

void loop()
{
  while(running());
}
