#include "sequence.h"

//Constructor
Sequence::Sequence(uint8_t steps)
{
  this->steps = steps - 1;
  speedInMillis = int( 60000 / speed );  
}

//Set pause state
bool Sequence::isPaused()
{
  return paused;
}

//Pause sequence
void Sequence::pauseSequence()
{
  paused = true;
}

//Active sequence
void Sequence::resumeSequence()
{
  paused = false;
}

//Define new sequence speed
void Sequence::setSpeed(float variation)
{
  speed += variation;
}

//Obtain the current speed value (in BPMs)
float Sequence::getSpeed()
{
  return speed;
}

//Obtain number sequence steps
uint8_t Sequence::getSteps()
{
  return steps + 1;
}

//Trigger clock gate
bool Sequence::clockTimer()
{
  if( millis() - lastChange >= speedInMillis ){
    lastChange =  millis();
    return true;
  } 
  return false;
}

//Obtain step position
uint16_t Sequence::getCurrentStep()
{
  return currentStep;
}

//Set new step position
void Sequence::changeStep()
{
  if(currentStep > steps) currentStep = 0;
  lastStep = currentStep;
  currentStep++;
}

//Trigger if current step positon changes
bool Sequence::stepChanged()
{
  if(lastStep != currentStep) return true;
  return false;
}
