#include "encoder.h"

bool Encoder::begin()
{
  NewEncoder::EncoderState state;
  if (!encoder.begin()) return false;

  newValueAvailable = false;
  encoder.getState(state);
  encoderValue = state.currentValue;
  encoder.attachCallback(callBack, this);
  return true;
}

bool Encoder::newDataAvailable()
{
  noInterrupts();
  bool temp = newValueAvailable;
  newValueAvailable = false;
  interrupts();
  return temp;
}

uint8_t Encoder::getPosition()
{
  int16_t temp;
  noInterrupts();
  temp = encoderValue;
  interrupts();
  return temp;
}

int8_t Encoder::getDirection()
{
  int16_t direction;
  int16_t value;
  noInterrupts();
  value = encoderValue;
  interrupts();
  
  if (value != prevEncoderValue) {
    direction = value - prevEncoderValue;
    prevEncoderValue = value;
    return direction < 0 ? -1 : 1;
  } 
  return 0;
}

// Static class callback function. Common to all instances. Uses the uPtr parameter to select the proper
// instance. Then, calls the instance function.
// Be careful, the callback executes in interrupt contexts.
void ESP_ISR Encoder::callBack(NewEncoder *encPtr, const volatile NewEncoder::EncoderState *state, void *uPtr)
{
  (void)encPtr;
  Encoder *ptr = (Encoder *)uPtr;
  ptr->handleEncoder(state);
}

// Instance function to handle encoder specific to each object. Called by static callback function.
// This is where instance-specific actions will be taken when the encoder is rotated.
// In this example, we just set a flag and make encoder value available to main code.
// Be careful, the callback executes in interrupt contexts.
void ESP_ISR Encoder::handleEncoder(const volatile NewEncoder::EncoderState *state)
{
  if (state->currentValue != encoderValue)
  {
    encoderValue = state->currentValue;
    newValueAvailable = true;
  }
}

