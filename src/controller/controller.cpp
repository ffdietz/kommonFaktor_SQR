#include "controller.h"
#include "pinout.h"
#include "utils.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  if(input_pin != A6 && input_pin != A7) pinMode(input_pin, INPUT_PULLUP);
  
  lastPressTime = 0;
  singlePressActive = false;
  doublePressActive = false;
  isSinglePushed = false;
  isDoublePushed = false;
  doublePushInterval = 500;
  currentState = pinRead();

}
bool Controller::pinRead() {
  const int readings = 100;
  const uint32_t debounceTime = 200;
  uint32_t lastChange = 0;
  int total = 0;

  if(millis() - lastChange > debounceTime)
  {
    if (input_pin == A6 || input_pin == A7){
      for (int i = 0; i < readings; i++){
        total += analogRead(input_pin);
      }
    } else {
      for (int i = 0; i < readings; i++) {
        total += digitalRead(input_pin);
      }
    }
    lastChange = millis();
  }
  int average = total / readings;

  return average > 0 ? HIGH : LOW;
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