#include <Arduino.h>

#ifndef stepRegister_h
#define stepRegister_h

class StepRegister
{
  public:
    StepRegister();
    void begin();

    byte check(byte currentState);
    void write(byte value);
    byte output;
    byte shifter = 1 << 0;
};

#endif
