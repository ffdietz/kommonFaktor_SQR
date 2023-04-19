//Track states of sequence
#include <Arduino.h>

#ifndef sequencer_h
#define sequencer_h

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed);

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
    bool isStepChanged();
    byte getCurrentPosition();
    byte getStepsQuantity();
    void setManualStep(int8_t variation);
    enum sequenceMode {LINEAR, INVERT, RANDOM, CUSTOM};
    sequenceMode mode = RANDOM;

    //Set methods
    bool isSetMode();
    void setModeOff();
    void setModeOn();

    bool setMode = false;
    byte stepsLength;
    
  // private:
    byte stepPosition = 0;
    byte lastPosition = 0;
    uint16_t speedInMillis = 0;
    uint16_t currentMillis = 0;
    uint16_t lastChange = 0;
};

#endif