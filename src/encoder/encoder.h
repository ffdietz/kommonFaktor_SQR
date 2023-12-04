#ifndef ENCODER_H_
#define ENCODER_H_
#include <Arduino.h>
#include <TimerOne.h>
#include "pinout.h"
#include "NewEncoder.h"

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

  bool begin();
  bool newDataAvailable();
  uint8_t getPosition();
  int8_t getDirection();
  int16_t prevEncoderValue = 0;

  private:
  // embedded NewEncoder object
  NewEncoder encoder;
  static void callBack(NewEncoder *encPtr, const volatile NewEncoder::EncoderState *state, void *uPtr);
  void handleEncoder(const volatile NewEncoder::EncoderState *state);
  volatile bool newValueAvailable = false;
  volatile int16_t encoderValue = 0;
};

#endif