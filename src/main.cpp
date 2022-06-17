#include <Arduino.h>
#include <ShiftRegister.h>
#include <Display.h>
// #include <Clock.h>
// #include <avdweb_Switch.h>
// Switch pushButton = Switch(4);

#include "DebounceInput.h"

DebouncedInput Button;
// DebounceFilter4ms Button;

long current_time = 0, last_change = 0, wait = 28;
void setup() 
{ 
  Serial.begin(115200);
  Serial.println("connected");

  Button.attach(4);

  shiftRegister_begin();
  // display_init();
}

void loop()
{
  current_time = millis();

  // if(Button.rising()) Serial.println(position);
  if(current_time - last_change >= wait){
    last_change = current_time;
    shiftRegister_shifter();
  } 
    shiftRegister_update();

  // Button.read();
  if(Button.readRising()) shiftRegister_set_position();

  shiftRegister_serial_print();
  // text_template();
  // display_text_test();
}


// PRINT EN PANTALLA
// EL BIT DEL SHIFT REGISTER
// ACTIVARLO SIN DELAY

//DETECTAR BOTONES ACTIVADOS Y MOSTRAR EN PANTALLA
//BPM MANUAL >> JUST ANALOGREAD