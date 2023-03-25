#ifndef GLOBAL_H
#define GLOBAL_H

#include "pinout.h"
#include "sequencer.h"
#include "encoder.h"
#include "controller.h"
#include "display.h"

Sequencer   sequencer(8, 135.0);
Encoder     encoder{ENCODER_A, ENCODER_B, ENCODER_MIN, ENCODER_MAX, 0};
Controller  encoderSetButton(ENCODER_SET);
Controller  pauseButton(PAUSE_BUTTON);
Display     display;

#endif
