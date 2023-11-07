#include "clock.h"
#include "pinout.h"
#include "utils.h"

Clock::Clock(float _speed)
{
  internalSpeed = _speed;
  speed = _speed;
}

void Clock:: begin(){
  speedInMillis = bpmToMillis(speed);
  currentMillis = millis();
}
// speed methods
void  Clock::setSpeedInBpm(float variation){
  speed += variation;
  speedInMillis = bpmToMillis(speed);
}
void  Clock::setSpeedInMillis(int millis){
  speedInMillis = millis;
  speed = millisToBpm(millis);
}
int   Clock::bpmToMillis(float bpm){
 return ( 60000 / bpm );
}
float   Clock::millisToBpm(int millis){
 return ( 60000 / millis );
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
  static uint32_t lastChange = 0;
  const uint8_t numReadings = 10;
  static uint32_t readings[numReadings];
  static uint8_t index = 0;

  static bool lastState = LOW;
  bool currentState = external();

  if (lastState == LOW && currentState == HIGH) {
    externalClockPeriod = millis() - lastChange;
    lastChange = millis();

    readings[index] = externalClockPeriod;
    index = (index + 1) % numReadings;
  }

  uint32_t sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += readings[i];
  }
  externalClockPeriodAverage = sum / numReadings;

  if (abs(externalClockPeriod - externalClockPeriodAverage) < 5) {
    externalClockPeriod = externalClockPeriodAverage;
  }

  if (millis() - lastChange > 3500) {
    externalClockFlag = false; // Assuming 1000 ms is the threshold for disconnection
  } else {
    externalClockFlag = true;
  }

  lastState = currentState;
}

void  Clock::update(){
  if(externalClockFlag){
    setSpeedInMillis(externalClockPeriod);
  }

  currentMillis = millis();
  internal();
}

bool Clock::external() {
  return analogRead(CLOCK_IN) > 0 ? HIGH : LOW;
}

void Clock::internal(){
  static uint32_t lastChange = 0;
  uint32_t totalPeriodMillis = speedInMillis * internalClockFactor;

  // if(!externalClockFlag){
    if(currentMillis - lastChange >= totalPeriodMillis * .2) {
      clockOut = LOW;
    } else {
      clockOut = HIGH; 
    }
  // }

  if (currentMillis - lastChange >= totalPeriodMillis) {
    flag = true;
    lastChange = currentMillis;
  } else {
    flag = false;
  }

  if(paused) clockOut = HIGH;
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
