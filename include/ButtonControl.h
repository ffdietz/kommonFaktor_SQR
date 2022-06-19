#include <Arduino.h>
#include "DebounceInput.h"

DebouncedInput button(4);

void button_update()
{
  button.read();
}



  // DDRD &= ~(1 << PIN_READ); //"AND INVERT 1" OPERATOR SET LOW