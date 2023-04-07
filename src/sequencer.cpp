#include "sequencer.h"
#include "pinout.h"

// constructor
Sequencer::Sequencer(uint8_t steps, float speed){
  this->steps = steps - 1;
  this->speed = speed;
  speedInMillis = speedToMillis(speed);
  lastChange = 0;
  paused = false;
  
  pinMode(CLOCK_OUT, OUTPUT);

}

// speed methods
void  Sequencer::setSpeed(float variation)
{
  speed += variation;
  speedInMillis = speedToMillis(speed);
}
int   Sequencer::speedToMillis(float speed)
{
 return ( 60000 / speed );
}
float Sequencer::getSpeed()
{
  return speed;
}


// pause methods
bool Sequencer::isPaused() 
{
  return paused;
}
void Sequencer::playSequence() 
{
  paused = false;
}
void Sequencer::pauseSequence() 
{
  paused = true;
}


// clock methods
bool Sequencer::internalClock()
{
  if (millis() - lastChange >= speedInMillis)
  {
    lastChange =  millis();
    return true;
  }
  return false;
}
void Sequencer::clockOut()
{
  clockOutState = !clockOutState;
  digitalWrite(CLOCK_OUT, clockOutState);
}


// steps methods
void  Sequencer::changeStep()
{
  lastStep = currentStep;
  currentStep++;
  if(currentStep > steps) currentStep = 0;
}
bool  Sequencer::stepChanged()
{
  if(lastStep != currentStep) return true;
  return false;
}
byte  Sequencer::getCurrentStep()
{
  return currentStep + 1;
}
void  Sequencer::setStepManually(int8_t variation)
{
  lastStep = currentStep;
  currentStep += variation;

  if(currentStep > steps) currentStep = 0;
  if(currentStep < 0) currentStep = steps;

}


// set methods
void Sequencer::setModeOn()
{
  setMode = true;
}
void Sequencer::setModeOff()
{
  setMode = false;
}
bool Sequencer::isSetMode()
{
  return setMode;
}
