#include "sequencer.h"
#include "pinout.h"

Sequencer::Sequencer(uint8_t steps, float _speed, bool initialState){
  speed = _speed;
  stepsLength = steps - 1;

  if(initialState) stepStates = 255;
  else stepStates = 0;
}

void Sequencer::begin(){
  pinMode(CLOCK_IN, INPUT);
  pinMode(CLOCK_OUT, OUTPUT);

  speedInMillis = speedToMillis(speed);

  if(sequenceMode == ASCEND) stepPosition = 0;
  if(sequenceMode == DESCEND) stepPosition = stepsLength;

currentMillis = millis();
}

// speed methods
void  Sequencer::setSpeed(float variation){
  speed += variation;
  speedInMillis = speedToMillis(speed);
}

int   Sequencer::speedToMillis(float speed){
 return ( 60000 / speed );
}

float Sequencer::getSpeed(){
  return speed;
}

// pause methods
bool  Sequencer::isPaused(){
  return paused;
}

void  Sequencer::playSequence(){
  paused = false;
}

void  Sequencer::pauseSequence(){
  paused = true;
}

// clock methods
void  Sequencer::updateClock(){
  currentMillis = millis();
}

void  Sequencer::clockOutput(){
  digitalWrite(CLOCK_OUT, clockOut);
}

bool Sequencer::internalClock() {
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
// bool Sequencer::externalClock()
// {
//   // CREATE CONTROLLER OBJECT TO READ CLOCK INPUT 
//   // static uint8_t extClock = digitalRead(CLOCK_IN);
//   // if(extClock == HIGH) externalClock = true;
//   return false; 
// }

void  Sequencer::setInternalClockFactor(int factor){
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

// steps methods
void    Sequencer::changeStep(){
  lastPosition = stepPosition;
  switch(sequenceMode){
    case ASCEND:
      stepPosition = (stepPosition + 1) & stepsLength;
      break;

    case DESCEND:
      stepPosition = (stepPosition - 1) & stepsLength;
      break;

    case RANDOM:
      stepPosition = random(0, stepsLength + 1);
      break;

    case CUSTOM:
      stepPosition = (stepPosition + 1) & stepsLength;
      break;
  }

}

bool    Sequencer::isStepChanged(){
  if(lastPosition != stepPosition) return true;
  return false;
}

uint8_t Sequencer::getCurrentPosition(){
  return stepPosition;
}

uint8_t Sequencer::getStepsState(){
  return stepStates;
}

void    Sequencer::setStepsState(uint8_t state){
  stepStates ^= state;
}

uint8_t Sequencer::getStatesAndPosition(){
  uint8_t states = getStepsState();
  uint8_t position = getCurrentPosition();

  states ^= (1 << position);

  return states;
}

void  Sequencer::setManualStep(int8_t variation){
  lastPosition = stepPosition;
  stepPosition = (stepPosition + variation) % (stepsLength + 1);
}

// Step mode methods
void  Sequencer::setSequenceMode(int8_t mode){
  switch(mode){
    case 0: sequenceMode = ASCEND;  break;
    case 1: sequenceMode = DESCEND; break;
    case 2: sequenceMode = RANDOM;  break;
    case 3: sequenceMode = CUSTOM;  break;
  }
}

int   Sequencer::getSequenceMode(){
  return sequenceMode;
}

void  Sequencer::resetSequence(bool reset){
  if(reset) stepStates = 255;
  if(!reset) stepStates = 0;
}