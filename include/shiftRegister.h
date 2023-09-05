#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include <Arduino.h>

class ShiftRegister
{
  public:
    ShiftRegister();
    void begin();

    byte check();
    void write(byte value);
    void keepOutputValue(byte value);
    int8_t keepValueOutput;
    byte output = 0;
    byte shifter = 1 << 0;
};

#endif
