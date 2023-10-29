#include "clock.h"
#include "pinout.h"

Clock::Clock(float _speed)
{
  speed = _speed;
}

void Clock:: begin(){
  speedInMillis = speedToMillis(speed);
  currentMillis = millis();
}

// speed methods
void  Clock::setSpeed(float variation){
  speed += variation;
  speedInMillis = speedToMillis(speed);
}

int   Clock::speedToMillis(float speed){
 return ( 60000 / speed );
}

float Clock::getSpeed(){
  return speed;
}

// pause methods
bool  Clock::isPaused(){
  return paused;
}

void  Clock::play(){
  paused = false;
}

void  Clock::pause(){
  paused = true;
}

// clock methods
void  Clock::update(){
  currentMillis = millis();
}

void  Clock::output(){
  digitalWrite(CLOCK_OUT, clockOut);
}

bool Clock::internal() {
  static bool outputFlag = false;
  static uint32_t lastChange = 0;
  uint32_t totalPeriodMillis = speedInMillis * internalClockFactor;

  if ((currentMillis - lastChange) >= totalPeriodMillis) {
    lastChange = currentMillis;
    outputFlag = true;
  } else {
    outputFlag  = false; 
  }
  
  if ((currentMillis - lastChange) >= (totalPeriodMillis * .2)) {
    clockOut = LOW;
  } else {
    clockOut = HIGH; 
  }

  if (paused) clockOut = HIGH;

  return outputFlag;
}
bool Clock::external()
{
  // CREATE CONTROLLER OBJECT TO READ CLOCK INPUT 
  return false; 
}

void  Clock::setInternalFactor(int factor){
  switch(factor)
  {
    case 0:   internalClockFactor = 64;       break;
    case 1:   internalClockFactor = 32;       break;
    case 2:   internalClockFactor = 16;       break;
    case 3:   internalClockFactor = 8;        break;
    case 4:   internalClockFactor = 4;        break;
    case 5:   internalClockFactor = 2;        break;
    case 6:   internalClockFactor = 1;        break;
    case 7:   internalClockFactor = .5;       break;
    case 8:   internalClockFactor = .25;      break;
    case 9:   internalClockFactor = .125;     break;
    case 10:  internalClockFactor = .0625;    break;
    case 11:  internalClockFactor = .03125;   break;
    case 12:  internalClockFactor = .015625;  break;
  }
}
