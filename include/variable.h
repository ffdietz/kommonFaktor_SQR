#ifndef variable_h
#define variable_h
#include <Arduino.h>

/* A structure for storing integer x y coordinates */
struct Variable
{
  String name;
  int8_t value;
  int8_t maximum;
  int8_t minimum;
  int8_t variation;
};

#endif