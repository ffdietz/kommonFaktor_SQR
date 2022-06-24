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
    bool clock();
    void changeStep();
    uint8_t getCurrentStep();
    bool stepChanged();

  private:
    uint8_t steps;
    uint8_t currentStep = 0;
    uint8_t lastStep = 0;
    float speed = 140.0; // in BPM
    uint8_t speedInMillis = 0;
    bool paused = false;
    long currentTime = 0;
    long lastChange = 0;
};

#endif