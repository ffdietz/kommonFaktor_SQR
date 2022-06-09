#include <Arduino.h>
#include <ButtonsControl.h>
// #include <ShiftRegister.h>
// #include <Display.h>
// #include <Clock.h>


void setup() 
{ 
  // shiftRegister_init();
  // display_init();
  button_init();
  // clock_init();

}

// uint8_t bit_out = 0;
// int aux = 0;

void loop() {
  // clock_update();
  // unsigned long current_millis = millis();
  // if(current_millis - last_update >= waiting){
  //   last_update = millis();
  //   aux = bit_out++ % 8;
  //   shiftRegister_out(aux);
  //   text_template(aux);
  // } 
  // if(bit_out > 7) bit_out = 0;

  // shiftRegister_test();
  // display_text_test();
}


// PRINT EN PANTALLA
// EL BIT DEL SHIFT REGISTER
// ACTIVARLO SIN DELAY

//DETECTAR BOTONES ACTIVADOS Y MOSTRAR EN PANTALLA
//BPM MANUAL >> JUST ANALOGREAD