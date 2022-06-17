#include <Arduino.h>
#include "DebounceInput.h"

DebouncedInput button(4);

void button_update()
{
  button.read();
}