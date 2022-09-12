#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"

#include "menu.h"
// #include "encoder.h"

//STRUCTURE TO SHOW LABEL AND VALUES AND MODIFY BY ENCODER
//CONTROL BPM IN BUILT IN LED 13

int lastValue = -1, encoderValue = 0;

// void start()
// {
// }


// bool run()
// {
//   if (encoder.newDataAvailable())
//   {
//     encoderValue = encoder.getData();
//     printScreen(encoderValue);
//   }

//   return true;
// }

#endif
