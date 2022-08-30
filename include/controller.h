#ifndef controller_h
#define controller_h

#include "ClickEncoder.h"
#include "TimerOne.h"

class Controller
{
  private:

    int lastPosition;
    int lastState;
    int currentState;

  public:
    Controller();
    void begin();
    bool pausedTriggered();
    void update();

};

#endif