#ifndef CLOCK_H_
#define CLOCK_H_
#include <Arduino.h>

class Clock {
  public:
    Clock(float speed);
    void begin();
    // Speed methods
    float bpm;
    uint32_t clockMillis = 0;
    uint32_t currentMillis = 0;
    uint32_t internalClockMillis = 0;
    uint32_t externalClockMillis = 0;
    uint32_t bpmToMillis(float bpm);
    bool externalClockFlag = false;
    float millisToBpm(int millis);
    void setSpeedInBpm(float variation);
    void setSpeedInMillis(int speed);
    float getSpeed();
    //Pause methods
    bool paused = false;
    bool isPaused();
    void pause();
    void play();
    //Clock methods
    bool flag = false;
    void check();
    void update();
    void output();
    void internal();
    void external();
    // Clock Factor
    void setInternalFactor(int factor);
    float internalClockFactor = 1;
    uint8_t clockOut = LOW;

};

#endif