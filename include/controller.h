#ifndef controller_h
#define controller_h

class Controller
{
  public:
    Controller(int pin);

    void begin();
    void update();
    bool check();
    bool trigged;

  private:
    int input_pin;
    int lastPosition;
    int lastState;
    int currentState;
    
};

#endif