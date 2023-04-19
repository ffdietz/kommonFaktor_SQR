#ifndef controller_h
#define controller_h

class Controller
{
  public:
    Controller(uint8_t pin);

    void begin();
    void update();
    bool check();
    void toggleActive();
    bool active;

  // private:
    int input_pin;
    int lastPosition;
    int lastState;
    int currentState;
    
};

#endif