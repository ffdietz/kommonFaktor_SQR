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
void Clock::check() {
  const uint32_t debounceTime = 5000;
  static uint32_t lastChange = 0;
  static uint32_t timePassed = 0;
  bool currentState = external();

  if (currentState == HIGH) lastChange = millis();

  timePassed = millis() - lastChange;

  if (timePassed < debounceTime) {
    externalClockInput = true;
  } else {
    externalClockInput = false;
  }
}
void  Clock::update(){
  if(externalClockInput){
    flag = external();
  } else {
    flag = internal();
  }
}

bool Clock::external()
{
  static bool lastState = LOW;
  bool currentState = analogRead(CLOCK_IN) > 0 ? HIGH : LOW;

  if(lastState == LOW && currentState == HIGH)
  {
    lastState = currentState;
    return true;
  }
  else {
    lastState = currentState;
    return false;
  }
}

bool Clock::internal(){
  static uint32_t lastChange = 0;
  uint32_t totalPeriodMillis = speedInMillis * internalClockFactor;

  currentMillis = millis();
  if(currentMillis - lastChange >= totalPeriodMillis * .2) {
    clockOut = LOW;
  } else {
    clockOut = HIGH; 
  }

  if(paused) clockOut = HIGH;

  if (currentMillis - lastChange >= totalPeriodMillis) {
    lastChange = currentMillis;
    return true;
  } else {
    return false;
  }
}
void  Clock::output(){
  if(paused) clockOut = HIGH;
  digitalWrite(CLOCK_OUT, clockOut);
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
