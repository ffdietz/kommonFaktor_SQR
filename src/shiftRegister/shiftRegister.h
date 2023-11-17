#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_
#include <Arduino.h>

class ShiftRegister
{
  public:
    ShiftRegister();

    void begin();
    byte check();
    void keepOutput(byte value);
    
  private:
    int8_t outputState;
};

#endif
