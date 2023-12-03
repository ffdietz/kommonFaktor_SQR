#include "sequencer.h"
#include "pinout.h"

Sequencer::Sequencer(uint8_t steps, bool initialState){

  stepsLength = steps - 1;

  if(initialState == ALL_ON) stepStates = 255;
  else stepStates = 0;
}

void Sequencer::begin(){
  if(sequenceMode == ASCEND) stepPosition = 0;
  if(sequenceMode == DESCEND) stepPosition = stepsLength;
}

// steps methods
void Sequencer::changeStep(){
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
      static byte index = 0;
      stepPosition = getStep(index);
      index = (index + 1) & stepsLength;
      break;
  }
}

bool Sequencer::isStepChanged(){
  if(lastPosition != stepPosition) return true;
  return false;
}

uint8_t Sequencer::getPosition(){
  return stepPosition;
}

uint8_t Sequencer::getStepsState(){
  return stepStates;
}

void Sequencer::setStepsState(uint8_t state){
  stepStates ^= state;
}

uint8_t Sequencer::getStepsAndPosition(){
  uint8_t states = getStepsState();
  uint8_t position = getPosition();

  states ^= (1 << position);

  return states;
}

void Sequencer::setPosition(uint8_t position){
  lastPosition = stepPosition;
  stepPosition = position;
}

void Sequencer::setPositionVariation(int8_t variation){
  lastPosition = stepPosition;
  stepPosition = (stepPosition + variation) % (stepsLength + 1);
}

// Step mode methods
void Sequencer::setSequenceMode(int8_t mode){
  switch(mode){
    case 0: sequenceMode = ASCEND;  break;
    case 1: sequenceMode = DESCEND; break;
    case 2: sequenceMode = RANDOM;  break;
    case 3: sequenceMode = CUSTOM;  break;
  }
}

int Sequencer::getSequenceMode(){
  return sequenceMode;
}

void Sequencer::resetSequence(bool reset){
  if(reset) stepStates = 255;
  if(!reset) stepStates = 0;
}

void Sequencer::setStep(uint8_t index, uint8_t value){
  steps[index] = value;
}

uint8_t Sequencer::getStep(uint8_t index){
  return steps[index];
}