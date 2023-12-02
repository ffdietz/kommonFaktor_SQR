#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_
#include <Arduino.h>

class ShiftRegister
{
  public:
    ShiftRegister();

    void begin();
    byte check();
    void output(byte value);
    bool locked();
    bool unlocked();
    bool lock = false;
    bool isKeyPressed = false;
    uint8_t keyPressed = 0;
    
  private:
    int8_t outputState;
};

#endif
