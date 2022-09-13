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

// void printStepsBar()
// {
//   Serial.print("STEPS:");
//   Serial.print(sequencer.getStepsQuantity());
//   Serial.print(" ");
// }

void printSpeedBar()
{
  if(pause.enable) printPause(); // print PAUSED status message on-screen
  
  else{
    lcd.setCursor(7,1);
    lcd.print("BPM:");
    lcd.print(sequencer.getSpeed());
  }

}

void printStepPositionBar()
{
  lcd.setCursor(0, 1);
  lcd.print("STEP:");
  lcd.print(sequencer.getCurrentStep());
}

void printStaticData()
{
  // printTitleBar();
  printSpeedBar();
  // printStepsBar();
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
  encoderSet.triggered();
  if (encoderSet.enable)
  {
    lcd.setCursor(0, 0);
    lcd.print('E');
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print('U');
  }
}

void checkPause()
{
  pause.triggered();

  if(pause.enable)
  {
    sequencer.pauseSequence();
  }

  else
    sequencer.restartSequence();
}

void update()
{
  updateSequence();
}

bool running()
{
  // game is paused
  checkPause();
  checkEncoderEnable();

  update();
  displayPrint();

  return true;
}

void restart()
{
  printStaticData();
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(LCD_CHARS, LCD_LINES);
  encoder.begin();

  lcd.clear();
  restart();
}

void loop()
{
  while(running());
}

// STRUCTURE TO SHOW LABEL AND VALUES AND MODIFY BY ENCODER

//SEQUENCE OPTIONS
////RANDOM SEQUENCE
////INVERT SEQUENCE
////RANGE SEQUENCE
////CUSTOM SEQUENCE

//CLOCK OPTIONS
////INTERNAL CLOCK
////EXTERNAL CLOCK
////DIVIDE CLOCK
////MULTIPLY CLOCK