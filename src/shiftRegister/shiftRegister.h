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
    bool locked();
    bool unlocked();
    bool lock = false;
    uint8_t keyPressed = 0;
    
  private:
    int8_t outputState;
};

#endif
