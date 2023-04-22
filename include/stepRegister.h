#include <Arduino.h>

#ifndef stepRegister_h
#define stepRegister_h

class StepRegister
{
  public:
    StepRegister();
    void begin();

    void check();
    void write(byte value);
    byte output = B00000000;
    byte shifter = 1 << 0;
};

#endif
