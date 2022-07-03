#include "shared.h"
#include "global.h"

PDQ_ST7735 tft;   // Creates LCD object 


void printTitleBar() {
  TitleBar::printLabel(&tft, InfoBarData::row0TitlePos, InfoBarData::titleLabel);
}

void printStepsBar() {
  StepsBar::printLabel(&tft, InfoBarData::row1LabelPos, InfoBarData::stepsLabel);
  StepsBar::printValue(&tft, InfoBarData::row1ValuePos, sequence.getSteps());
}

void printSpeedBar(){
  SpeedBar::printLabel(&tft, InfoBarData::row2LabelPos, InfoBarData::speedLabel);
  SpeedBar::printValue(&tft, InfoBarData::row2ValuePos, sequence.getSpeed());
}

void printStepPositionBar(){
  StepPositionBar::printLabel(&tft, InfoBarData::row3LabelPos, InfoBarData::stepPosLabel);
  StepPositionBar::printValue(&tft, InfoBarData::row3ValuePos, sequence.getCurrentStep());
}

// void updateScore() {
void printCurrentStep() {
  StepPositionBar::printValue(&tft, InfoBarData::row3ValuePos, sequence.getCurrentStep());
}

void updateCurrentStep(){
}

void updateActiveSteps() {
  // LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, sequence.getSteps());
}

void updateSequence(){
  if (sequence.clockTimer()) sequence.changeStep();
}

void update() {
  updateSequence();
  updateActiveSteps();
  updateCurrentStep();

  // // compare ghost states to pac-man
  // checkGhost(orange);
  // checkGhost(blue);
  // checkGhost(pink);
  // checkGhost(red);

  // early game conditions for releasing ghosts
  //   - red is released immediately
  //   - pink is released after 20 points
  //   - blue is released after 35 points
  //   - orange is released after 50 points
  // if(game.getScore()>20 && pink.draw().pos == CoordinatesF({13.0f,13.0f}))
  // {
  //   pink.tpTo(11.0f,13.0f,LEFT);
  // }
  // else if (game.getScore()>35 && blue.draw().pos == CoordinatesF({13.0f,13.0f}))
  // {
  //   blue.tpTo(11.0f,13.0f,LEFT);
  // }
  // else if (game.getScore()>50 && orange.draw().pos == CoordinatesF({13.0f,13.0f}))
  // {
  //   orange.tpTo(11.0f,13.0f,LEFT);
  // }
  // else if (red.draw().pos ==  CoordinatesF({13.0f,13.0f}))
  // {
  //   red.tpTo(11.0F,13.0f,LEFT);
  // }

}

void draw() {
  // drawPacMan();
  // drawGhosts();
  if (sequence.stepChanged()){
    printCurrentStep();
    DrawLayout::drawLayout(&tft, sequence.getCurrentStep());
  }
}

void restart(){
  // tft.setFont(&FONT_FAMILY);
  // tft.setRotation(ROTATE_90);
  tft.setRotation(ROTATE_270);  
  tft.setTextSize(FONT_SCALE);
  DrawLayout::clearScreen(&tft);

  printTitleBar();
  printStepsBar();  // printPause();
  printSpeedBar();
  printStepPositionBar();
  DrawLayout::drawLayout(&tft, sequence.getCurrentStep());
  
}

void checkPause() {
  if (control.buttonTriggered())
    sequence.pauseSequence();
}

// main loop for game runtime
bool running() {
  // game is paused
  checkPause();
  if (sequence.isPaused()) {
    // print PAUSED status message on-screen
    TitleBar::drawPause(&tft, InfoBarData::row0PausePos, InfoBarData::pauseLabel);

    // wait for play button to play sequence
    while (!control.buttonTriggered()) {}
  
    // print title row
    printTitleBar();
    sequence.resumeSequence();
  }
  
  update();
  draw();

  delay(FRAME_DELAY); // maintain upper bound to frame rate
  return true;
}

void setup() 
{ 
  Serial.begin(115200);
  tft.begin();
  DrawLayout::clearScreen(&tft);
  restart();
}

void loop()
{
  while( running() );
}
