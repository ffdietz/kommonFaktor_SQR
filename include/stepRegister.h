#ifndef STEPREGISTER_H
#define STEPREGISTER_H

#include <Arduino.h>

class StepRegister
{
  public:
    StepRegister();
    void begin();

    byte check();
    void write(byte value);
    void keepOutputValue(byte value);
    byte output = 0;
    byte shifter = 1 << 0;
    int8_t keepValueOutput;
};

#endif
