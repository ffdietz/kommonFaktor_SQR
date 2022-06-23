#include "shared.h"

PDQ_ST7735 tft;   // Creates LCD object 

void updateScore() {
  // ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos, sequence.getSteps());
}

void updateLives() {
  // LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, sequence.isPaused());
}

// void drawGameOver(bool winner) {
//   tft.fillRect(InfoBarData::bottomBarLabelPos.x, 
//     InfoBarData::bottomBarLabelPos.y, Display::width, FONT_H, 
//     ST7735_BLACK);

//   tft.setCursor(InfoBarData::bottomBarLabelPos.x, 
//     InfoBarData::bottomBarLabelPos.y);
  
//   if (winner) tft.print("YOU WIN!");
//   else tft.print("GAME OVER");
// }

void drawScoreBar() {
  // ScoreBar::drawLabel(&tft, InfoBarData::topBarLabelPos, InfoBarData::titleLabel);
  // ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos, sequence.getSteps());
}

// draw remaining lives bar (label and value) on-screen
void drawLivesBar() {
  // LivesBar::drawLabel(&tft, InfoBarData::bottomBarLabelPos, InfoBarData::stepsLabel);
  // LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, 3);
}

void update() {
  // updatePacMan();
  // updateGhosts();

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

  // if (game.scoreChanged) {
  //   updateScore();
  //   game.scoreChanged = false;
  // }

  // if (game.livesChanged) {
  //   updateLives();
  //   game.livesChanged = false;
  // }
}

void restart(){
  tft.setRotation(ROTATE_270);
  DrawMap::clearScreen(&tft);
  // DrawMap::drawDot(&tft, 20, 30);
  
  // drawScoreBar();
  // drawLivesBar();
}

void checkPause() {
  if (control.buttonTriggered())
    sequence.pauseSequence();
}

// main loop for game runtime
bool running() {
  // game is paused
  // checkPause();
  // if (sequence.isPaused()) {
  //   // print PAUSED status message on-screen
  //   ScoreBar::drawPause(&tft, InfoBarData::topBarPausePos, 
  //     InfoBarData::pauseLabel);
    
  //   // wait for joystick click to resume game
  //   while (!control.buttonTriggered()) {}
  
  //   // redraw top bar
  //   drawScoreBar();
  //   // sequence.resumeGame();
  // }
  
  // update();
  // draw();

  // // // check for game over
  // // if (game.isGameOver()) {
  // //   // print winning or losing message
  // //   if (game.getScore() == Game::maxScore)
  // //     drawGameOver(true);
  // //   else  
  // //     drawGameOver(false);
    
  // //   // click joystick to play again
  // //   while (!con.buttonTriggered()) {} 
  // //   restart();
  // // }

  delay(FRAME_DELAY); // maintain upper bound to frame rate
  return true;
}

void setup() 
{ 
  Serial.begin(115200);
  tft.begin();
  DrawMap::clearScreen(&tft);
  // restart();
}

void loop()
{
  while( running() );
}
