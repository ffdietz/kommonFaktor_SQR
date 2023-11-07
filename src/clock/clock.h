#ifndef CLOCK_H_
#define CLOCK_H_
#include <Arduino.h>

class Clock {
  public:
    Clock(float speed);
    void begin();
    // Speed methods
    float speed;
    float internalSpeed;
    uint32_t externalClockPeriodAverage = 0;
    int bpmToMillis(float bpm);
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
    bool external();
    // Clock Factor
    void setInternalFactor(int factor);
    bool externalClockFlag = false;
    int externalClockPeriod = 0;
    float internalClockFactor = 1;
    uint8_t clockOut = LOW;

    uint32_t speedInMillis = 0;
    uint32_t currentMillis = 0;
};

#endif