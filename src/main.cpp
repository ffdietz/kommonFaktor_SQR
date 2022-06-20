#include "shared.h"
#include "global.h"

// #include "controller.h"
// #include "game.h"

// globals for player controls, game map, and overall game state
// extern Controller con;
// extern Game game; 

PDQ_ST7735 tft;   // Creates LCD object 

void setup() 
{ 
  Serial.begin(115200);  
  tft.begin();
}

void drawScoreBar() {
  ScoreBar::drawLabel(&tft, InfoBarData::topBarLabelPos, InfoBarData::scoreLabel);
  ScoreBar::drawScore(&tft, InfoBarData::topBarValuePos, 2);
}

// draw remaining lives bar (label and value) on-screen
void drawLivesBar() {
  LivesBar::drawLabel(&tft, InfoBarData::bottomBarLabelPos, InfoBarData::livesLabel);
  LivesBar::drawLives(&tft, InfoBarData::bottomBarValuePos, 3);
}


// void checkPauseGame() {
//   if (con.buttonTriggered())
//     game.pauseGame();
// }

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

// main loop for game runtime
bool running() {
  // game is paused
  // checkPauseGame();
  // if (game.isPaused()) {
  if (true) {
    // print PAUSED status message on-screen
    ScoreBar::drawPause(&tft, InfoBarData::topBarPausePos, 
      InfoBarData::pauseLabel);
    
    // wait for joystick click to resume game
    // while (!con.buttonTriggered()) {}
  
    // redraw top bar
    drawScoreBar();
    // game.resumeGame();
  }
  
  update();
  draw();

  delay(FRAME_DELAY); // maintain upper bound to frame rate
  return true;
}

void loop()
{
  while(running());

}
