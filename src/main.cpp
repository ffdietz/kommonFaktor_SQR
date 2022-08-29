#include "shared.h"
#include "global.h"

// PDQ_ST7735 tft;   // Creates LCD object 

void displaySettings(){

}

void printTitleBar() {
  Serial.print("SEQUENCER ");
  // TitleBar::printLabel(&tft, InfoBarData::row0TitlePos, InfoBarData::titleLabel);
}

void printPause(){  
  Serial.print("PAUSE ");
}

void printStepsBar() {
  Serial.print("STEPS:");  
  Serial.print(sequencer.getSteps());
  Serial.print(" ");  
  // StepsBar::printLabel(&tft, InfoBarData::row1LabelPos, InfoBarData::stepsLabel);
  // StepsBar::printValue(&tft, InfoBarData::row1ValuePos, sequencer.getSteps());
}

void printSpeedBar(){
  Serial.print("BPM:");  
  Serial.print(sequencer.getSpeed());
  Serial.print(" ");  
  // SpeedBar::printLabel(&tft, InfoBarData::row2LabelPos, InfoBarData::speedLabel);
  // SpeedBar::printValue(&tft, InfoBarData::row2ValuePos, sequencer.getSpeed());
}

void printStepPositionBar(){
  Serial.print("STEP:");  
  Serial.print(sequencer.getCurrentStep());
  Serial.print(" ");  
  // StepPositionBar::printLabel(&tft, InfoBarData::row3LabelPos, InfoBarData::stepPosLabel);
  // StepPositionBar::printValue(&tft, InfoBarData::row3ValuePos, sequencer.getCurrentStep());
}

void printStaticData(){
  printTitleBar();
  printStepsBar();
  printSpeedBar();
}

void printDynamicData(){
  printStepPositionBar();
  // DrawLayout::drawLayout(&tft, sequencer.getCurrentStep());

}

void updateCurrentStep(){
}

void updateActiveSteps() {
  // LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, sequence.getSteps());
}

void updateSequence(){
  if (sequencer.clockTimer()) sequencer.changeStep();
}



void update() {
  updateSequence();
  updateActiveSteps();
  updateCurrentStep();

}

void draw() {
  printStaticData();
  printDynamicData();  
}


void checkPause() {
  if (control.pausedTriggered())  sequencer.paused();
}

bool running() {
  // game is paused
  checkPause();
  if (sequencer.isPaused()) {
    printPause();   // print PAUSED status message on-screen

    while (!control.pausedTriggered()) {}   // wait for play button to play sequence

    sequencer.restart();
  }
  
  update();
  draw();

  Serial.println("");
  delay(FRAME_DELAY); // maintain upper bound to frame rate
  return true;
}

void restart(){
  // displaySettings();  
  printStaticData();
  printDynamicData();
}

void setup() 
{ 
  Serial.begin(115200);
  Serial.println("setup connected");

  // // tft.begin();
  // // restart();

  start();
}

void loop()
{
 while( run());
  // while( running() );
}
