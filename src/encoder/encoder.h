// #include <ClickEncoder.h>
#include <Arduino.h>
#include <TimerOne.h>
#include "pinout.h"

#include "NewEncoder.h"

// Demonstrate how to include an encoder object inside of a class and how to use the
// callback feature to call an instance function of the class
class Encoder
{
public:
  Encoder(
    uint8_t aPin,
    uint8_t bPin,
    int16_t minValue = ENCODER_MIN,
    int16_t maxValue = ENCODER_MAX,
    int16_t initalValue = 0,
    uint8_t type = FULL_PULSE
    ):encoder{aPin, bPin, minValue, maxValue, initalValue, type}{}

  bool begin() {
    NewEncoder::EncoderState state;
    if (!encoder.begin()) return false;

    newValueAvailable = false;
    encoder.getState(state);
    encoderValue = state.currentValue;
    encoder.attachCallback(callBack, this);
    return true;
  }

  bool newDataAvailable() {
    noInterrupts();
    bool temp = newValueAvailable;
    newValueAvailable = false;
    interrupts();
    return temp;
  }

  int16_t getPosition() {
    int16_t temp;
    noInterrupts();
    temp = encoderValue;
    interrupts();
    return temp;
  }

  int8_t getDirection()
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

  int16_t prevEncoderValue = 0;


private:
  // embedded NewEncoder object
  NewEncoder encoder;

  static void callBack(NewEncoder *encPtr, const volatile NewEncoder::EncoderState *state, void *uPtr);
  void handleEncoder(const volatile NewEncoder::EncoderState *state);
  volatile bool newValueAvailable = false;
  volatile int16_t encoderValue = 0;
};
