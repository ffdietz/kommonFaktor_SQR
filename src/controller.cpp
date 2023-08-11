#include <Arduino.h>

#include "controller.h"
#include "pinout.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  if(input_pin != A6 || input_pin != A7) pinMode(input_pin, INPUT_PULLUP);
  
  currentState = pinRead();

  active = false;
}

void Controller::check()
{
  lastState = currentState;
  currentState = pinRead();

  if(currentState == LOW && lastState == HIGH){
    isTrigged = true;
    toggleActive();
  }
  else isTrigged = false;

  // return isTrigged;
}

void Controller::toggleActive(){
  active = !active;
}

int Controller::pinRead(){
  if (input_pin == A6 || input_pin == A7) {
    return analogRead(input_pin) < 200 ? LOW : HIGH;
  } else {
    return digitalRead(input_pin);
  }
}