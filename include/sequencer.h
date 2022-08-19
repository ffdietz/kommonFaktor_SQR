//Track states of sequence
#ifndef sequencer_h
#define sequencer_h
#include <Arduino.h>

class Sequencer {
  public:
    Sequencer(uint8_t steps, float speed);
    ~Sequencer(){};
    
    //Speed methods
    void      setSpeed(float variation);
    bool      clockTimer();
    float     getSpeed();

    //Steps methods
    uint8_t   getSteps();
    void      changeStep();
    bool      stepChanged();
    uint16_t  getCurrentStep();

    //Pause methods
    bool isPaused();
    void paused();
    void restart();

  private:
    uint8_t steps;
    float speed = 140.0;  // in BPM
    uint16_t speedInMillis = 0;
    uint8_t lastStep = 0;
    uint16_t currentStep = 0;
    bool pauseSequence = false;
    long currentTime = 0;
    long lastChange = 0;
};

#endif