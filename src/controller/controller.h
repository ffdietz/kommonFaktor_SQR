#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
  public:
    Controller(uint8_t pin);

    void begin();
    void update();
    void check();
    int  pinRead();
    bool isChanged();
    bool isSinglePushed;
    bool isDoublePushed;
    bool singlePressLatch;
    bool doublePressLatch;
    uint32_t doublePushInterval;

  // private:
    int input_pin;
    int lastState;
    int currentState;
    uint32_t lastPressTime;
};

#endif