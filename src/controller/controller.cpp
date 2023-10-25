#include "controller.h"
#include "pinout.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  if(input_pin != A6 && input_pin != A7) pinMode(input_pin, INPUT_PULLUP);
  
  lastPressTime = 0;
  singlePressActive = false;
  doublePressActive = false;
  isSinglePushed = false;
  isDoublePushed = false;
  doublePushInterval = 300;
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
      if(currentTime - lastPressTime <= doublePushInterval) 
      {
        isSinglePushed = false;
        isDoublePushed = true;
        doublePressActive = !doublePressActive;
      } else {
        isDoublePushed = false;
        isSinglePushed = true;
        singlePressActive = !singlePressActive;
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