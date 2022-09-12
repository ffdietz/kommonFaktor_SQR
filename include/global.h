#ifndef GLOBAL_H
#define GLOBAL_H

#include "pinout.h"
#include "controller.h"
#include "sequencer.h"
#include "encoder.h"

Sequencer sequencer(8, 140.0);
Encoder encoder{ENCODER_A, ENCODER_B, ENCODER_MIN, ENCODER_MAX, ENCODER_MIN};
// Encoder encoder{ENCODER_A, ENCODER_B, ENCODER_MIN, ENCODER_MAX, ENCODER_MIN, FULL_PULSE};
Controller control;
//Menu

#endif
