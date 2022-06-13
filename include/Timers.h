#include <Arduino.h>

boolean LED_STATE = 0;

void Timers_init()
{
  
  DDRB |= (1 << 5);

  TCCR1A = 0;   // RESET ENTIRE TCCR1A TO 0
  TCCR1B = 0;   // RESET ENTIRE TCCR1B TO 0

  TCCR1B |= (1 << CS12); //SETTING CS12 TO 1 ACTIVE PRESCALE TO 256
  TCNT1   = 0;

  TIMSK1 |= (1 << OCIE1A); // SET OCIE1A TO COMPARE MATCH A

  OCR1A = 1;  
}


ISR(TIMER1_COMPA_vect)
{
  TCNT1 = 0;
  PORTB |= (1 << 5 );   //LATCH HIGH
  PORTB &= ~(1 << 5);   //LATCH LOW
}