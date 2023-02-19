 #include "sequencer.h"

//Constructor
Sequencer::Sequencer(uint8_t steps, float speed){
  this->steps = steps - 1;
  this->speed = speed;
  this->speedInMillis = int( 60000/speed );
  this->lastChange = 0;
  this->paused = false;
  
  pinMode(13, OUTPUT);

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
    digitalWrite(13, HIGH);

    return true;
  }

  digitalWrite(13, LOW);
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
  digitalWrite(13, clockOutState);
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
