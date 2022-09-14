#ifndef GLOBAL_H
#define GLOBAL_H

#include "pinout.h"
#include "sequencer.h"
#include "encoder.h"
#include "controller.h"
#include "menu.h"

Sequencer   sequencer(8, 100.0);
Encoder     encoder{ENCODER_A, ENCODER_B, ENCODER_MIN, ENCODER_MAX, ENCODER_MIN};
Controller  encoderSet(ENCODER_SET);
Controller  pause(PAUSE_BUTTON);
Menu        menu;

#endif
