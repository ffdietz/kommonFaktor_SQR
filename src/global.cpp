#include "pinout.h"

#include "sequencer/sequencer.h"
#include "encoder/encoder.h"
#include "controller/controller.h"
#include "display/display.h"
#include "shiftRegister/shiftRegister.h"
#include "multiplexer/multiplexer.h"
#include "menu/menu.h"
#include "clock/clock.h"

Clock           clock(200.0);
Sequencer       sequencer(8, ALL_OFF);
Encoder         encoder(ENCODER_A, ENCODER_B);
Controller      encoderSetButton(ENCODER_SET);
Controller      pauseButton(PAUSE_BUTTON);
ShiftRegister   stepButtonPanel;
Multiplexer     multiplexer;
Display         display;
Menu            menu;

