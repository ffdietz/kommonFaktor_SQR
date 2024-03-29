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
    void setStepsState(byte position);
    void setPositionVariation(int8_t variation);
    void setPosition(uint8_t position);
    uint8_t getStepsState();
    uint8_t getPosition();
    uint8_t getStepsAndPosition();
    uint8_t stepsLength;
    uint8_t steps[8] = {0, 1, 2, 3, 7, 6, 5, 4};
    void setStep(uint8_t index, uint8_t value);
    uint8_t getStep(uint8_t index);
    //Sequence progression
    enum Mode { ASCEND, DESCEND, RANDOM, CUSTOM };
    Mode sequenceMode = ASCEND;
    void setSequenceMode(int8_t variation);
    int  getSequenceMode();
    void resetSequence(bool reset);
    
  private:
    uint8_t stepPosition = 0;
    uint8_t lastPosition = 0;
    uint8_t stepStates = 0;
};

#endif