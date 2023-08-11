#include "sequencer.h"
#include "pinout.h"

// constructor
Sequencer::Sequencer(uint8_t _steps, float _speed)
{
  speed = _speed;
  stepsLength = _steps - 1;

  speedInMillis = speedToMillis(speed);
  clockOutValue = true;
  lastChange = 0;
  paused = false;

  if(sequenceMode == ASCEND) stepPosition = 0;
  if(sequenceMode == DESCEND) stepPosition = stepsLength;
  
  pinMode(CLOCK_OUT, OUTPUT);

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
bool  Sequencer::internalClock()
{
  if (currentMillis - lastChange >= speedInMillis)
  {
    lastChange =  currentMillis;
    digitalWrite(CLOCK_OUT, LOW);

    return true;
  }

  digitalWrite(CLOCK_OUT, HIGH);

  return false;
}
void Sequencer::clockOut()
{
  digitalWrite(CLOCK_OUT, clockOutValue);
}

// steps methods
void  Sequencer::changeStep()
{
  currentBytePosition =  0;
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
bool  Sequencer::isStepChanged()
{
  if(lastPosition != stepPosition) return true;
  return false;
}
uint8_t  Sequencer::getCurrentPosition()
{
  return stepPosition;
}

byte  Sequencer::getStepsState()
{
  return stepStates;
}
void  Sequencer::setStepsState(byte state)
{
  stepStates ^= state;
}
byte Sequencer::getStatesAndPosition()
{
  byte states = getStepsState();
  byte position = getCurrentPosition();

  // Serial.print("  states ");
  //   Serial.print(states);
  // Serial.print("  position ");
  //   Serial.print(position);

  states ^= (1 << position);

  return states;
}
void  Sequencer::setManualStep(int8_t variation)
{
  lastPosition = stepPosition;
  stepPosition = (stepPosition + variation) % (stepsLength + 1);
}

// Step mode methods
void  Sequencer::setSequenceMode(int8_t mode)
{
  switch(mode){
    case 0: sequenceMode = ASCEND;  break;
    case 1: sequenceMode = DESCEND; break;
    case 2: sequenceMode = RANDOM;  break;
    case 3: sequenceMode = CUSTOM;  break;
  }
}
int   Sequencer::getSequenceMode()
{
  return sequenceMode;
}
