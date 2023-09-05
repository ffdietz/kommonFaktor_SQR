#ifndef GLOBAL_H
#define GLOBAL_H

#include "pinout.h"
#include "sequencer.h"
#include "encoder.h"
#include "controller.h"
#include "display.h"
#include "shiftRegister.h"
#include "multiplexer.h"

Sequencer       sequencer(8, 99.0, ALL_ON);
Encoder         encoder(ENCODER_A, ENCODER_B);
Controller      encoderSetButton(ENCODER_SET);
Controller      pauseButton(PAUSE_BUTTON);
Display         display;
Multiplexer     mux;
ShiftRegister   stepButtonPanel;

#endif
