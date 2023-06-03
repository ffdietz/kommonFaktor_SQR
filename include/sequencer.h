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
    int  clockOutValue;
    bool internalClock();
    bool externalClock();
    void updateClock();
    void clockOut();

    //Steps methods
    void changeStep();
    bool isStepChanged();
    byte getStepsQuantity();
    uint8_t getCurrentPosition(); //
    byte getStatesAndPosition();
    void setStepsState(byte position);
    byte getStepsState();
    void setManualStep(int8_t variation);

    //Step mode sequence
    enum Mode { ASCEND, DESCEND, RANDOM, CUSTOM };
    Mode sequenceMode = ASCEND;
    void setSequenceMode(int8_t variation);
    int  getSequenceMode();

    byte stepsLength;
    
  // private:
    byte stepPosition = 0;
    byte lastPosition = 0;
    byte stepStates = 255;
    uint8_t currentBytePosition = 1 << 0;
    long speedInMillis = 0;
    long currentMillis = 0;
    long lastChange = 0;
};

#endif