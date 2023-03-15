#include "sequencer.h"
#include "pinout.h"

//Constructor
Sequencer::Sequencer(uint8_t steps, float speed){
  this->steps = steps - 1;
  this->speed = speed;
  this->speedInMillis = speedToMillis(speed);
  this->lastChange = 0;
  this->paused = false;
  
  pinMode(CLOCK_OUT, OUTPUT);

}

bool Sequencer::isPaused(){
  return paused;
}

void Sequencer::pauseSequence()
{
  paused = true;
}

void Sequencer::restartSequence(){
  paused = false;
}

int Sequencer::speedToMillis(float speed){
 return ( 60000 / speed );
}

void Sequencer::setSpeed(float variation){
  speed += variation;
}

float Sequencer::getSpeed(){
  return speed;
}

uint8_t Sequencer::getStepsQuantity(){
  return steps + 1;
}

bool Sequencer::internalClock(){
  if (millis() - lastChange >= speedInMillis)
  {
    lastChange =  millis();
    digitalWrite(CLOCK_OUT, HIGH);

    return true;
  }

  digitalWrite(CLOCK_OUT, LOW);
  return false;
}

uint8_t Sequencer::getCurrentStep(){
  return currentStep;
}

void Sequencer::changeStep(){
  if(currentStep > steps) currentStep = 0;
  lastStep = currentStep;
  currentStep++;
}

bool Sequencer::stepChanged(){
  if(lastStep != currentStep) return true;
  return false;
}

void Sequencer::clockOut(){
  clockOutState = !clockOutState;
  digitalWrite(CLOCK_OUT, clockOutState);
}

void Sequencer::setModeOn(){
  setMode = true;
}

void Sequencer::setModeOff(){
  setMode = false;
}

bool Sequencer::isSetMode(){
  return setMode;
}
