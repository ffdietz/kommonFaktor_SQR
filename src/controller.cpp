#include <Arduino.h>

#include "controller.h"
#include "pinout.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  if(input_pin != A6 && input_pin != A7) pinMode(input_pin, INPUT_PULLUP);
  
  currentState = pinRead();

}

int Controller::pinRead(){
  if (input_pin == A6 || input_pin == A7) {
    return analogRead(input_pin) == 0 ? HIGH : LOW;
  } else {
    return digitalRead(input_pin);
  }
}

void Controller::toggleActive(){
  active = !active;
}

void Controller::check()
{
  lastState = currentState;
  currentState = pinRead();

  if(lastState == LOW && currentState == HIGH){
    isTrigged = true;
    toggleActive();
  }
  else {
    isTrigged = false;
  }

}