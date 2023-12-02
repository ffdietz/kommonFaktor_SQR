#include "controller.h"
#include "pinout.h"
#include "utils.h"


Controller::Controller(uint8_t pin)
{
  inputPin = pin;
  if(inputPin == A6 || inputPin == A7){
    isAnalogPin = true;
  } else isAnalogPin = false;

  if(!isAnalogPin) pinMode(inputPin, INPUT_PULLUP);
  
  lastPressTime = 0;
  isSinglePressed = false;
  isDoublePressed = false;
  singlePressActive = false;
  doublePressActive = false;

  doublePushInterval = 400;
  
  currentState = pinRead();
}
bool Controller::pinRead() {
  int currentRead;
  currentRead = isAnalogPin ? analogRead(inputPin) : digitalRead(inputPin);

  return !currentRead;
}

void Controller::check()
{
  uint32_t currentTime;
  currentState = pinRead();

  if (lastState == LOW && currentState == HIGH) {
    currentTime = millis();
    if(currentTime - lastPressTime <= doublePushInterval) 
    {
      doublePressActive = !doublePressActive;
      isSinglePressed = false;
      isDoublePressed = true;
    } else {
      singlePressActive = !singlePressActive;
      isSinglePressed = true;
      isDoublePressed = false;
      lastPressTime = currentTime;
    }
  } else {
    isSinglePressed = false;
    isDoublePressed = false;
  }
  lastState = currentState;
}

bool Controller::isChanged()
{
  if(lastState != currentState) return true;
  else return false;
}