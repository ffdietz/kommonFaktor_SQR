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
      int16_t minValue,
      int16_t maxValue,
      int16_t initalValue,
      uint8_t type = FULL_PULSE) 
      : encoder{aPin, bPin, minValue, maxValue, initalValue, type}
  {
  }

  bool begin()
  {
    NewEncoder::EncoderState state;
    if (!encoder.begin())
    {
      return false;
    }
    newValueAvailable = false;
    encoder.getState(state);
    encoderValue = state.currentValue;
    encoder.attachCallback(callBack, this);
    return true;
  }

  bool newDataAvailable()
  {
    noInterrupts();
    bool temp = newValueAvailable;
    newValueAvailable = false;
    interrupts();
    return temp;
  }

  int16_t getData()
  {
    int16_t temp;
    noInterrupts();
    temp = encoderValue;
    interrupts();
    return temp;
  }

private:
  // embedded NewEncoder object
  NewEncoder encoder;

  volatile int16_t encoderValue = 0;
  volatile bool newValueAvailable = false;
  void handleEncoder(const volatile NewEncoder::EncoderState *state);
  static void callBack(NewEncoder *encPtr, const volatile NewEncoder::EncoderState *state, void *uPtr);
};

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

// Pins 2 and 3 should work for many processors, including Uno. See README for meaning of constructor arguments.
// Use FULL_PULSE for encoders that produce one complete quadrature pulse per detnet, such as: https://www.adafruit.com/product/377
// Use HALF_PULSE for endoders that produce one complete quadrature pulse for every two detents, such as: https://www.mouser.com/ProductDetail/alps/ec11e15244g1/?qs=YMSFtX0bdJDiV4LBO61anw==&countrycode=US&currencycode=USD


// void encoderBegin()
// {
//   if (!encoder.begin())
//   {
//     Serial.println("Encoder failed to start. Aborting");
//     while (1)
//     {
//       delay(1);
//     }
//   }

//   // Serial.print("myObject started at: ");
//   // Serial.println(encoder.getData());
// }


// void encoderRun()
// {
//   if (encoder.newDataAvailable())
//   {
//     Serial.print("myObject: ");
//     Serial.println(encoder.getData());
//   }
// }
