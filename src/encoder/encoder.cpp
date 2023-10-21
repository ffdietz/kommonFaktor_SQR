#include "encoder.h"
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


// void encoderRun()
// {
//   if (encoder.newDataAvailable())
//   {
//     Serial.print("myObject: ");
//     Serial.println(encoder.getData());
//   }
// }
