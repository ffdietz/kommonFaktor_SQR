//Track states of sequence
#include <Arduino.h>

#ifndef SEQUENCER_H
#define SEQUENCER_H

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed, bool initialState);
    void begin();

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
    uint8_t  clockOut = LOW;
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

    byte stepsLength = 0;

  // private:
    uint8_t stepPosition = 0;
    uint8_t lastPosition = 0;
    uint8_t stepStates = 0;
    long speedInMillis = 0;
    long currentMillis = 0;
    long lastChange = 0;
};

#endif