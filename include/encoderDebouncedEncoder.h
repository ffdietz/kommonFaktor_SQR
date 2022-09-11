// // #include <ClickEncoder.h>
// #include <Arduino.h>
// #include <TimerOne.h>
// #include "pinout.h"

// #include "DebouncedEncoder.h"

// // ClickEncoder *encoder;
// DebouncedEncoder *encoder;
// // ClickEncoder::Button button;

// byte encoderMin = 0;
// byte encoderMax = 50;
// byte lastPosition = 0;

// void ISREnc()
// {
//   encoder->encoderCheck();
// }

// // #define ENCODER_A 2
// // #define ENCODER_B 3

// void encoderBegin()
// {
//   // encoder = new ClickEncoder(ENCODER_A, ENCODER_B, ENCODER_SET, 2); // 4 pulses per option
//   // encoder = new DebouncedEncoder(ENCODER_A, ENCODER_B, encoderMax, encoderMin, true);
//   encoder = new DebouncedEncoder(2, 3, encoderMax, encoderMin, true);

//   attachInterrupt(digitalPinToInterrupt(2), ISREnc, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(3), ISREnc, CHANGE);

//   // Timer1.initialize(1000);
//   // Timer1.attachInterrupt(ISREnc);
// }

// int encoder_position()
// {
//   int position = encoder->getPosition();
//   if (lastPosition != position)
//   {
//     lastPosition = position;
//     return position;
//   }
//   else
//     return lastPosition;
// }

// int encoder_direction()
// {
//   int direction = encoder->getDirection();
//   return direction;
// }