#include "sequence.h"

Sequence::Sequence(uint8_t steps){
  this->steps = steps - 1;
  speedInMillis = int( 60000 / speed );
  currentTime = millis();
  
}

bool Sequence::isPaused(){
  return paused;
}

void Sequence::pauseSequence(){
  paused = true;
}

void Sequence::resumeSequence(){
  paused = false;
}

void Sequence::setSpeed(float variation){
  speed += variation;
}

float Sequence::getSpeed(){
  return speed;
}

uint8_t Sequence::getSteps(){
  return steps + 1;
}

bool Sequence::clockTimer(){
  currentTime = millis();
  if(currentTime - lastChange >= speedInMillis ){
    lastChange = currentTime;
    return true;
  } 
  return false;
}

uint8_t Sequence::getCurrentStep(){
  return currentStep;
}

void Sequence::changeStep(){
  if(currentStep > steps) currentStep = 0;
  lastStep = currentStep;
  currentStep++;
}

bool Sequence::stepChanged(){
  if(lastStep != currentStep) return true;
  return false;
}


// uint8_t Sequence::stepChange(){
//   //matematicas del cambio de paso en funcion de variable SPEED
//   //actualizacion del currentStep
// }