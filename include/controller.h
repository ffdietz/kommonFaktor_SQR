#ifndef controller_h
#define controller_h

class Controller
{
  public:
    Controller(uint8_t pin);

    void begin();
    void update();
    void check();
    void toggleActive();
    int  pinRead();
    bool active;
    bool isTrigged;

  // private:
    int input_pin;
    int lastPosition;
    int lastState;
    int currentState;
    
};

#endif