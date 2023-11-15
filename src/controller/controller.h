#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <Arduino.h>


class Controller
{
  public:
    Controller(uint8_t pin);

    void begin();
    void update();
    void check();
    bool pinRead();
    bool isChanged();
    bool isSinglePushed;
    bool isDoublePushed;
    bool singlePressActive;
    bool doublePressActive;
    uint32_t doublePushInterval;
  // private:
    int inputPin;
    bool isAnalogPin;
    int lastState;
    int currentState;
    uint32_t lastPressTime;
};

#endif