#include <Arduino.h>

#include "controller.h"
#include "pinout.h"


Controller::Controller(uint8_t pin)
{
  input_pin = pin;
  // pinMode(input_pin, INPUT_PULLUP);
  
  // Init button state
  // currentState = digitalRead(input_pin);

  currentState = analogRead(input_pin) < 200 ? HIGH : LOW;
  active = false;
}

bool Controller::check()
{
  /* Update the button readings */
  lastState = currentState;
  currentState = analogRead(input_pin) < 200 ? HIGH : LOW;

  /* Return if the button just got pressed down */
  if(currentState == LOW && lastState == HIGH){
    toggleActive();
    return true;
  }

  return false;
}

void Controller::toggleActive(){
  active = !active;
}