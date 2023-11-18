#ifndef SEQUENCER_H_
#define SEQUENCER_H_
#include <Arduino.h>

class Sequencer {
  public:
    Sequencer(uint8_t steps, bool initialState);
    void begin();
    //Steps methods
    void changeStep();
    bool isStepChanged();
    uint8_t getCurrentPosition();
    uint8_t getStepsAndPosition();
    void setStepsState(byte position);
    uint8_t getStepsState();
    bool setManual = false;
    void setManualStep(int8_t variation);
    //Sequence progression
    enum Mode { ASCEND, DESCEND, RANDOM, CUSTOM };
    Mode sequenceMode = ASCEND;
    void setSequenceMode(int8_t variation);
    int  getSequenceMode();
    void resetSequence(bool reset);
  private:
    uint8_t stepsLength = 0;
    uint8_t stepPosition = 0;
    uint8_t lastPosition = 0;
    uint8_t stepStates = 0;
};

#endif