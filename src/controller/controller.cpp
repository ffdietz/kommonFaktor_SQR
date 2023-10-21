#include <Arduino.h>

#include "controller.h"
#include "pinout.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  if(input_pin != A6 && input_pin != A7) pinMode(input_pin, INPUT_PULLUP);
  
  lastPressTime = 0;
  singlePressLatch = false;
  doublePressLatch = false;
  isSinglePushed = false;
  isDoublePushed = false;
  doublePushInterval = 600;
  currentState = pinRead();

}

int Controller::pinRead(){
  if (input_pin == A6 || input_pin == A7) {
    return analogRead(input_pin) == 0 ? HIGH : LOW;
  } else {
    return digitalRead(input_pin);
  }
}

void Controller::check()
{
  uint32_t currentTime;
  currentState = pinRead();

  if (lastState == LOW && currentState == HIGH) {
    currentTime = millis();
    if (currentTime - lastPressTime <= doublePushInterval) {
      isSinglePushed = false;
      isDoublePushed = true;
      doublePressLatch = !doublePressLatch;
    } else {
      isDoublePushed = false;
      isSinglePushed = true;
      singlePressLatch = !singlePressLatch;
      lastPressTime = currentTime;
    }
  } else {
    isSinglePushed = false;
    isDoublePushed = false;
  }
  lastState = currentState;
}

bool Controller::isChanged()
{
  if(lastState != currentState) return true;
  else return false;
}