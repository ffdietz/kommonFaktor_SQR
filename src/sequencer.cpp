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

//Set pause state
bool Sequencer::isPaused(){
  return paused;
}

//Pause sequence
void Sequencer::pauseSequence()
{
  this->paused = true;
}

//Active sequence
void Sequencer::restartSequence(){
  this->paused = false;
}

//Define new sequence speed
void Sequencer::setSpeed(float variation){
  speed += variation;
}

//Obtain the current speed value (in BPMs)
float Sequencer::getSpeed(){
  return speed;
}

//Obtain number sequence steps
uint8_t Sequencer::getStepsQuantity(){
  return steps + 1;
}

//Trigger clock gate
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

//Obtain step position
uint8_t Sequencer::getCurrentStep(){
  return currentStep;
}

//Set new step position
void Sequencer::changeStep(){
  if(currentStep > steps) currentStep = 0;
  lastStep = currentStep;
  currentStep++;
}

//Trigger if current step positon changes
bool Sequencer::stepChanged(){
  if(lastStep != currentStep) return true;
  return false;
}

void Sequencer::clockOut(){
  clockOutState = !clockOutState;
  digitalWrite(13, clockOutState);
}