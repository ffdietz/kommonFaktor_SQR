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
  singlePressActive = false;
  doublePressActive = false;
  isSinglePushed = false;
  isDoublePushed = false;
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
      isSinglePushed = false;
      isDoublePushed = true;
    } else {
      singlePressActive = !singlePressActive;
      isSinglePushed = true;
      isDoublePushed = false;
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