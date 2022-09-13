//Track states of sequence
#ifndef sequencer_h
#define sequencer_h
#include <Arduino.h>

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed);
    ~Sequencer(){};

    //Clock methods
    bool internalClock();
    bool externalClock();
    void clockOut();
    bool clockOutState = LOW;

    //Speed methods
    void  setSpeed(float variation);
    float getSpeed();

    //Steps methods
    uint8_t getStepsQuantity();
    void  changeStep();
    bool  stepChanged();
    uint8_t getCurrentStep();

    //Pause methods
    bool paused = false;
    bool isPaused();
    void pauseSequence();
    void restartSequence();

  private:
    float speed = 140.0;  // in BPM
    uint8_t steps;
    uint8_t lastStep = 0;
    uint8_t currentStep = 0;
    uint16_t speedInMillis = 0;
    long currentTime = 0;
    long lastChange = 0;
};

#endif