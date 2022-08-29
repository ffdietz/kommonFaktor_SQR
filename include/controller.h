#ifndef controller_h
#define controller_h

#include "ClickEncoder.h"
#include "TimerOne.h"

// Game controller is described by an instance of this class
class Controller
{
public:

  Controller();
  void timerIsr();

  int getDirection();

  bool pausedTriggered();

  int encoderGetValue();

  int encoderLast = -1;

  int encoderValue = 0;
  int lastPosition;

  int lastState;
  int currentState;


};

#endif