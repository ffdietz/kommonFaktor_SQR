#include <Arduino.h>

#ifndef stepRegister_h
#define stepRegister_h

class StepRegister
{
  public:
    StepRegister();
    void begin();

    byte check();
    void write(byte value);
    void keepOutputValue(byte value);
    byte output;
    byte shifter = 1 << 0;
    int8_t keepValueOutput;
};

#endif
