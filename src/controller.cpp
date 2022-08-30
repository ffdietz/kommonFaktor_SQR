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



Controller::Controller()
{
    pinMode(PAUSE_BUTTON, INPUT_PULLUP);
    currentState = digitalRead(PAUSE_BUTTON); // Init button state

}

void Controller::update()
{
}


void Controller:: begin(){
}

bool Controller::pausedTriggered()
{
    /* Will update the button readings */
    lastState = currentState;
    currentState = digitalRead(PAUSE_BUTTON);
    /* Return if the button just got pressed down */
    return (currentState == LOW && lastState == HIGH);
}

