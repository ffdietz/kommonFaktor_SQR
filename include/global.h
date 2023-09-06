#ifndef GLOBAL_H
#define GLOBAL_H

#include "pinout.h"
#include "sequencer.h"
#include "encoder.h"
#include "controller.h"
#include "display.h"
#include "shiftRegister.h"
#include "multiplexer.h"

Sequencer       sequencer(8, 200.0, ALL_OFF);
ShiftRegister   stepButtonPanel;
Encoder         encoder(ENCODER_A, ENCODER_B);
Controller      encoderSetButton(ENCODER_SET);
Controller      pauseButton(PAUSE_BUTTON);
Display         display;
Multiplexer     mux;

#endif
