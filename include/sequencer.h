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
    bool paused;
    bool isPaused();
    void pauseSequence();
    void playSequence();

    //Clock methods
    bool clockOutValue;
    bool internalClock();
    bool externalClock();
    void updateClock();

    //Steps methods
    void changeStep();
    bool stepChanged();
    byte getCurrentStep();
    byte getStepsQuantity();
    void setManualStep(int8_t variation);


    //Set methods
    bool isSetMode();
    void setModeOff();
    void setModeOn();

    bool setMode = false;
    byte steps;
    
  private:
    byte currentStep = 0;
    byte lastStep = 0;
    uint16_t speedInMillis = 0;
    uint16_t currentMillis = 0;
    uint16_t lastChange = 0;
};

#endif