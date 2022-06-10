#include <Arduino.h>
// #include <ButtonsControl.h>
#include <ShiftRegister.h>
// #include <Display.h>
// #include <Clock.h>


void setup() 
{ 
  Serial.begin(115200);
  // shiftRegister_begin();
  // display_init();
  // button_init();
  // clock_init();
  shiftRegister_read_begin();

}

void loop() {
  // shiftRegister_test(200);
}


// PRINT EN PANTALLA
// EL BIT DEL SHIFT REGISTER
// ACTIVARLO SIN DELAY

//DETECTAR BOTONES ACTIVADOS Y MOSTRAR EN PANTALLA
//BPM MANUAL >> JUST ANALOGREAD