//Track states of sequence
#ifndef sequence_h
#define sequence_h
#include <Arduino.h>

class Sequence {
  public:
    Sequence(uint8_t steps = 8);
    // ~Sequence(){};
    bool isPaused();
    void pauseSequence();
    void resumeSequence();
    void setSpeed(float variation);
    float getSpeed();
    uint8_t getSteps();

  private:
    uint8_t steps;
    uint8_t currentStep = 0;
    float speed = 120.0; // in BPM
    bool paused = false;
};

#endif