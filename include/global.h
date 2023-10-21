#ifndef GLOBAL_H
#define GLOBAL_H

#include "sequencer/sequencer.h"
#include "encoder/encoder.h"
#include "controller/controller.h"
#include "display/display.h"
#include "shiftRegister/shiftRegister.h"
#include "multiplexer/multiplexer.h"
#include "menu/menu.h"

extern Sequencer      sequencer;
extern Encoder        encoder;
extern Controller     encoderSetButton;
extern Controller     pauseButton;
extern ShiftRegister  stepButtonPanel;
extern Multiplexer    multiplexer;
extern Display        display;
extern Menu           menu;

#endif