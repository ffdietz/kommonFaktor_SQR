#include <Arduino.h>
#include <ShiftRegister.h>
#include <Display.h>

boolean sequencer = true;

void setup() {
  shiftRegister_init();
  display_init();
}


void loop() {
  shiftRegister_test(sequencer);
  display_update();
}