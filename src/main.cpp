#include "global.h"
#include "menu.h"

void debugger()
{
  Serial.print("  indexSelector.menu ");        Serial.print(indexSelector.menu);
  Serial.print("  setMenuFnIndex ");            Serial.print(setMenuFnIndex(indexSelector.menu,indexSelector.subMenu));
  Serial.print("  menuIsSetMode ");             Serial.print(menuIsSetMode());
  Serial.print("  encoderSetButton.active ");   Serial.print(encoderSetButton.active);
  Serial.print("  sequencer.getCurrentStep ");  Serial.print(sequencer.getCurrentStep());
  Serial.print("  sequencer.clockOut ");        Serial.print(sequencer.clockOutValue);
  Serial.print("  sequencer.internalClock ");   Serial.print(sequencer.internalClock());
  
  Serial.println();
}

unsigned long lastUpdateTime = 0;
unsigned long currentMillis = 0;

void print() 
{
  // if(sequencer.paused) Menu::printPause();
  currentMillis = millis();
  if (currentMillis - lastUpdateTime >= 1000 / 30) 
  {
    lastUpdateTime = currentMillis;
    printMenu();
  }
}


void updateSequence() 
{
  sequencer.updateClock();
  if(sequencer.internalClock() && !sequencer.paused)
  {
    sequencer.clockOut();
    sequencer.changeStep();

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
    sequencer.playSequence();
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