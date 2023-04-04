#include "global.h"
#include "menu.h"

void debugger()
{
  Serial.print("  indexSelector.menu ");        Serial.print(indexSelector.menu);
  Serial.print("  setMenuFnIndex ");            Serial.print(setMenuFnIndex(indexSelector.menu,indexSelector.subMenu));
  Serial.print("  menuIsSetMode ");             Serial.print(menuIsSetMode());
  Serial.print("  encoderSetButton.active ");   Serial.print(encoderSetButton.active);
  Serial.print("  sequencer.getCurrentStep ");  Serial.print(sequencer.getCurrentStep());
  Serial.println();
}

unsigned long lastUpdateTime = 0;
unsigned long frameInterval = 1000 / 30; // 30 fps

void print() 
{
  // if(sequencer.paused) Menu::printPause();
  if (millis() - lastUpdateTime >= frameInterval) 
  {
    printMenu();
  lastUpdateTime = millis();
  }
}


void updateSequence() 
{
  if(sequencer.internalClock() && !sequencer.paused)
  {
    sequencer.changeStep();
    sequencer.clockOut();
  }
}


void updateVariables() 
{
  if(menuIsSetMode()) currentFunc();
}


void update() 
{
  updateVariables();
  updateSequence();
}


void checkEncoder()
{
  if(encoder.newDataAvailable()){
    if(!setMenuMode) selectMenuIndex(encoder.getDirection());
    else currentFunc();
    clearMenu();
  };
}

void checkSetEncoder() 
{
  encoderSetButton.check();
  setMenuMode = encoderSetButton.active;
  clearMenu();
}


void checkPause() 
{
  pauseButton.check();

  if(pauseButton.active)
    sequencer.pauseSequence();
  else
    sequencer.restartSequence();
}


void check() 
{
  checkPause();
  checkSetEncoder();
  checkEncoder();
}


bool running() 
{
  check();
  update();
  print();

  debugger();

  return true;
}


void restart() 
{
  display.clear();
}


void setup() 
{
  Serial.begin(9600);
  Serial.println("serial connected");

  encoder.begin();
  display.begin();
  menuInit();

  restart();
}


void loop() 
{
  while (
    running()
  );
}