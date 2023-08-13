#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
  public:
    Controller(uint8_t pin);

    void begin();
    void update();
    void check();
    void toggleActive();
    int  pinRead();
    bool isChanged();
    bool active = false;
    bool isTrigged = false;

  // private:
    int input_pin;
    int lastState;
    int currentState;
};

#endif