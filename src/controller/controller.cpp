#include "controller.h"
#include "pinout.h"
#include "utils.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  if(input_pin != A6 && input_pin != A7) 
    pinMode(input_pin, INPUT_PULLUP);
  
  lastPressTime = 0;
  singlePressActive = false;
  doublePressActive = false;
  isSinglePushed = false;
  isDoublePushed = false;
  doublePushInterval = 400;
  currentState = pinRead();

}
bool Controller::pinRead() {
  int read;

  if (input_pin == A6 || input_pin == A7){
    read = analogRead(input_pin) > 690 ? HIGH : LOW;
  } else {
    read = digitalRead(input_pin);
  }

  return read;
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