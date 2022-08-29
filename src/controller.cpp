/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000001                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/*Track state of game controller*/
#include <Arduino.h>

#include "controller.h"
#include "pinout.h"

// #include "DebouncedEncoder.h"

ClickEncoder *encoder;

void timerIsr()
{
    encoder->service();
}
Controller::Controller()
{
    encoder = new DebouncedEncoder(encPinA, encPinB, encMaxValue, encMinValue, false);
    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr);

    pinMode(PAUSE_BUTTON, INPUT_PULLUP);
    currentState = digitalRead(PAUSE_BUTTON); // Init button state
}

// int Controller::getDirection()
// {

// }

bool Controller::pausedTriggered()
{
    /* Will update the button readings */
    lastState = currentState;
    currentState = digitalRead(PAUSE_BUTTON);
    /* Return if the button just got pressed down */
    return (currentState == LOW && lastState == HIGH);
}


// bool Controller::displayAccelerationStatus(){
//  return (encoder->getAccelerationEnabled() ? "on " : "off");
// }


int Controller::encoderGetValue()
{
    Serial.println(encoder->getPosition());
    return (encoder->getPosition());
}

