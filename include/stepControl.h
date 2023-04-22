#include <Arduino.h>

#ifndef stepControl_h
#define stepControl_h

class StepControl
{
  public:
    StepControl();
    void begin();

    void check();
    void write(byte value);
    byte output = B00000000;
    byte shifter = 1 << 0;
};

#endif
