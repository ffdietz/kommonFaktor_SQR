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
#include "gameConfig.h"
#include "DebouncedEncoder.h"

Controller::Controller()
{
    pinMode(ENCODER_A, INPUT);        // x joystick
    pinMode(ENCODER_B, INPUT);        // y joystick
    pinMode(ENCODER_SET, INPUT_PULLUP);  // Button pin
    pinMode(PAUSE_BUTTON, INPUT_PULLUP);  // Button pin

    // currentState = digitalRead(ENCODER_SET); // Init button state
    currentState = digitalRead(PAUSE_BUTTON); // Init button state
}

int Controller::getDirection()
{

}

bool Controller::buttonTriggered()
{
    /* Will update the button readings */
    lastState = currentState;
    currentState = digitalRead(PAUSE_BUTTON);
    /* Return if the button just got pressed down */
    return (currentState == LOW && lastState == HIGH);
}
