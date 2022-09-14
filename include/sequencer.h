//Track states of sequence
#ifndef sequencer_h
#define sequencer_h
#include <Arduino.h>

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed);
    ~Sequencer(){};

    //Clock methods
    float speed;  // in BPM
    bool internalClock();
    bool externalClock();
    void clockOut();
    bool clockOutState = LOW;

    //Speed methods
    void  setSpeed(float variation);
    float getSpeed();

    //Steps methods
    void  changeStep();
    bool  stepChanged();
    uint8_t getCurrentStep();
    uint8_t getStepsQuantity();

    //Pause methods
    bool paused = false;
    bool isPaused();
    void pauseSequence();
    void restartSequence();

  private:
    uint8_t steps;
    uint8_t lastStep = 0;
    uint8_t currentStep = 0;
    uint16_t speedInMillis = 0;
    long currentTime = 0;
    long lastChange = 0;
};

#endif