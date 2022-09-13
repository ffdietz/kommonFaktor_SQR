#ifndef controller_h
#define controller_h

class Controller
{
  private:
    int input_pin;
    int lastPosition;
    int lastState;
    int currentState;

  public:
    Controller(int pin);

    void begin();
    void update();
    bool check();
    bool activated;
};

#endif