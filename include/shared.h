#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"

#include "menu.h"
#include "encoderNewEncoder.h"

//variables
//controllers
//menu

int lastValue = -1, encoderValue = 0;

void start()
{
  menuBegin();
  encoderBegin();
  printScreen(encoderValue);
}


bool run()
{
  // encoderRun();

  if (encoder.newDataAvailable())
  {
    encoderValue = encoder.getData();
    printScreen(encoderValue);
  }

  return true;
}

#endif
