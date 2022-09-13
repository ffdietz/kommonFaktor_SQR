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


Controller::Controller(int pin)
{
    input_pin = pin;
    pinMode(input_pin, INPUT_PULLUP);
    
    // Init button state
    currentState = digitalRead(input_pin); 
    enable = false;
}

bool Controller::triggered()
{
    /* Will update the button readings */
    lastState = currentState;
    currentState = digitalRead(input_pin);

    /* Return if the button just got pressed down */
    if(currentState == LOW && lastState == HIGH)
    {
        enable = !enable;
        return true;
    }

    return false;
}

