#include <Arduino.h>
// #include <ButtonsControl.h>
#include <ShiftRegister.h>
// #include <Display.h>
// #include <Clock.h>
#include <avdweb_Switch.h>
Switch pushButton = Switch(4);

void setup() 
{ 
  Serial.begin(115200);
  Serial.println("connected");
  
  shiftRegister_begin();
}

void loop() {
  ShiftRegister_update();
  pushButton.poll();
  if(pushButton.pushed()) Serial.println( Shiftregister_position() );

  // delay(500);
  // shiftRegister_test(20);
}


// PRINT EN PANTALLA
// EL BIT DEL SHIFT REGISTER
// ACTIVARLO SIN DELAY

//DETECTAR BOTONES ACTIVADOS Y MOSTRAR EN PANTALLA
//BPM MANUAL >> JUST ANALOGREAD