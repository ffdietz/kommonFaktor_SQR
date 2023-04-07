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
    void  setSpeed(float variation);
    int   speedToMillis(float speed);
    float getSpeed();

    //Pause methods
    bool paused = true;
    bool isPaused();
    void pauseSequence();
    void playSequence();

    //Clock methods
    bool clockOutState = true;
    bool internalClock();
    bool externalClock();
    void clockOut();

    //Steps methods
    void changeStep();
    bool stepChanged();
    byte getCurrentStep();
    byte getStepsQuantity();
    void setStepManually(int8_t variation);


    //Set methods
    bool isSetMode();
    void setModeOff();
    void setModeOn();

    bool setMode = false;
    byte steps;
    
  private:
    uint16_t speedInMillis = 0;
    byte currentStep = 0;
    byte lastStep = 0;
    long currentTime = 0;
    long lastChange = 0;
};

#endif