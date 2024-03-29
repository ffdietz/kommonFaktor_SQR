#include "clock.h"
#include "pinout.h"
#include "utils.h"

#define READ_TRESHOLD 620

Clock::Clock(float _bpm)
{
  bpm = _bpm;
  internalClockMillis = bpmToMillis(bpm);
}
void Clock:: begin(){
  pinMode(CLOCK_IN, INPUT);
  pinMode(CLOCK_OUT, OUTPUT);

  currentMillis = millis();
}
// speed methods
void Clock::setSpeedInMillis(int millis){
  internalClockMillis = millis;
  bpm = millisToBpm(internalClockMillis);
}

void Clock::setSpeedInBpm(float variation){
  bpm += variation;
  internalClockMillis = bpmToMillis(bpm);
}

uint32_t Clock::bpmToMillis(float bpm){
 return ( 60000 / bpm );
}

float Clock::millisToBpm(int millis){
 return ( 60000 / millis );
}

float Clock::getSpeed(){
  return bpm;
}

// pause methods
bool Clock::isPaused(){
  return paused;
}

void Clock::play(){
  paused = false;
}

void  Clock::pause(){
  paused = true;
}

// clock methods
void Clock::check() {
  external();

  if(isExternalClock)
    clockMillis = externalClockMillis;
  else 
    clockMillis = internalClockMillis;
}

void  Clock::update(){
  currentMillis = millis();
  internal();
}

void Clock::external() {
  static bool lastState = LOW;
  static uint32_t lastChange = 0;

  bool currentState = 
    analogRead(CLOCK_IN) > READ_TRESHOLD ? HIGH : LOW;

  if(lastState == LOW && currentState == HIGH){
    const int readings = 4;
    static uint32_t externalReadings[readings] = {0};
    static int index = 0;

    externalReadings[index] = millis() - lastChange;
    index = (index + 1) % readings;
    
    uint32_t sum = 0;
    for(int i = 0; i < readings; i++){
      sum += externalReadings[i];
    }
    externalClockMillis = sum / readings;

    lastChange = millis();
  }

  if(millis() - lastChange > 3000){
    isExternalClock = false;
  } else if(millis() > 3000){
    isExternalClock = true;
  }
  
  lastState = currentState;
}

void Clock::internal(){
  static uint32_t lastChange = 0;
  uint32_t millisPeriod = clockMillis * internalClockFactor;

  if(currentMillis - lastChange >= millisPeriod){
    tick = true;
    lastChange = currentMillis;
  } else {
    tick = false;
  }

  if(!isExternalClock){
    if(currentMillis - lastChange >= millisPeriod * .2) {
      clockOut = LOW;
    } else {
      clockOut = HIGH;
    }
  }

}
void  Clock::output(){
  // if(paused) clockOut = HIGH;
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
