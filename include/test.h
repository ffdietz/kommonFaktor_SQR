#include <Arduino.h>

void test_init()
{  
  pinMode(LED_BUILTIN, OUTPUT);
}

void test_update()
{
  digitalWrite(LED_BUILTIN, HIGH);  delay(50);
  digitalWrite(LED_BUILTIN, LOW);   delay(50);
  digitalWrite(LED_BUILTIN, HIGH);  delay(50);
  digitalWrite(LED_BUILTIN, LOW);   delay(1000);
}