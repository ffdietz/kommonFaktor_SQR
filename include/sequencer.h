//Track states of sequence
#ifndef sequencer_h
#define sequencer_h
#include <Arduino.h>

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed);
    ~Sequencer(){};

    //Speed methods
    float speed; // in BPM
    int   speedToMillis(float speed);
    void  setSpeed(float variation);
    float getSpeed();

    //Pause methods
    bool paused = true;
    bool isPaused();
    void pauseSequence();
    void restartSequence();

    //Clock methods
    bool internalClock();
    bool externalClock();
    void clockOut();
    bool clockOutState = LOW;

    //Steps methods
    void changeStep();
    bool stepChanged();
    uint8_t getCurrentStep();
    uint8_t getStepsQuantity();

    //Set methods
    bool isSetMode();
    void setModeOff();
    void setModeOn();

    bool setMode = false;
    
  private:
    uint16_t speedInMillis = 0;
    uint8_t currentStep = 0;
    uint8_t lastStep = 0;
    uint8_t steps;
    long currentTime = 0;
    long lastChange = 0;
};

#endif