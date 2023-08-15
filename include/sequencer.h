//Track states of sequence
#include <Arduino.h>

#ifndef SEQUENCER_H
#define SEQUENCER_H

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed);

    //Speed methods
    float speed; // in BPM
    void  setSpeed(float variation);
    int   speedToMillis(float speed);
    float getSpeed();

    //Pause methods
    bool paused = false;
    bool isPaused();
    void pauseSequence();
    void playSequence();

    //Clock methods
    uint8_t  clockOutState = LOW;
    // bool externalClock = false;
    bool internalClock();
    void setInternalClockFactor(int factor);
    float internalClockFactor = 1;
    // bool externalClock();
    void updateClock();
    void clockOutput();

    //Steps methods
    void changeStep();
    bool isStepChanged();
    byte getStepsQuantity();
    uint8_t getCurrentPosition();
    uint8_t getStatesAndPosition();
    void setStepsState(byte position);
    byte getStepsState();
    void setManualStep(int8_t variation);

    //Sequence progression
    enum Mode { ASCEND, DESCEND, RANDOM, CUSTOM };
    Mode sequenceMode = ASCEND;
    void setSequenceMode(int8_t variation);
    int  getSequenceMode();

    //Clock mode
    // enum Factor { MULTIPLY, DIVIDER };
    // Factor clockMode;

    byte stepsLength = 0;
    
  // private:
    byte stepPosition = 0;
    byte lastPosition = 0;
    byte stepStates = 0;
    uint8_t currentBytePosition = 1 << 0;
    long speedInMillis = 0;
    long currentMillis = 0;
    long lastChange = 0;
};

#endif