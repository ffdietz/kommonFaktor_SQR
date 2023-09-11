#ifndef GLOBAL_H
#define GLOBAL_H

#include <pinout.h>
#include <sequencer/sequencer.h>
#include <encoder/encoder.h>
#include <controller/controller.h>
#include <display/display.h>
#include <shiftRegister/shiftRegister.h>
#include <multiplexer/multiplexer.h>

Sequencer       sequencer(8, 200.0, ALL_OFF);
Encoder         encoder(ENCODER_A, ENCODER_B);
Controller      encoderSetButton(ENCODER_SET);
Controller      pauseButton(PAUSE_BUTTON);
ShiftRegister   stepButtonPanel;
Display         display;
Multiplexer     multiplexer;

#endif
