#include "sequence.h"

Sequence::Sequence(uint8_t steps){
  this->steps = steps - 1;
  currentStep = 0;
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

// uint8_t Sequence::stepChange(){
//   //matematicas del cambio de paso en funcion de variable SPEED
//   //actualizacion del currentStep
// }