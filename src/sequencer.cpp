 #include "sequencer.h"

//Constructor
Sequencer::Sequencer(uint8_t steps, float speed){
  this->steps = steps - 1;
  this->speed = speed;
  this->speedInMillis = int( 60000 / speed );
  this->pauseSequence = false;
  this->lastChange = 0;
  
  pinMode(13, OUTPUT);

}

//Set pause state
bool Sequencer::isPaused(){
  return pauseSequence;
}

//Pause sequence
void Sequencer::paused(){
  this->pauseSequence = true;
}

//Active sequence
void Sequencer::restart(){
  this->pauseSequence = false;
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
uint8_t Sequencer::getSteps(){
  return steps + 1;
}

//Trigger clock gate
bool Sequencer::internalClock(){
  if( millis() - lastChange >= speedInMillis ){
    lastChange =  millis();
    return true;
  } 
  return false;
}

//Obtain step position
uint16_t Sequencer::getCurrentStep(){
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
  bool state = true;
  if (millis() - lastChange >= speedInMillis)
  {
    state = true;
  }

  else state = false;

  digitalWrite(13, state);
}