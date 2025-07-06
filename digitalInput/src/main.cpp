#include <avr/io.h>
#include <util/delay.h>

// This code alternates the states of pins 13 (PB5) and 5 (PD5):
// when pin 13 is HIGH, pin 3 is LOW, and vice versa.
// The state toggles depending on pin 7 (PB7) current state.

int main(void)
{
  DDRB |= (1 << PB5);  // pin 13 OUTPUT
  DDRD |= (1 << PD5);  // pin 5 OUTPUT
  DDRD &= ~(1 << PD7); // pin 7 INPUT
  PORTD |= (1 << PD7); // enables internal pull-up for pin 7

  while (1)
  {
    if (!(PIND & (1 << PD7))) // digitalRead pin 7
    {
      PORTB |= (1 << PB5);  // pin 13 HIGH
      PORTD &= ~(1 << PD5); // pin 5 LOW
    }
    else
    {
      PORTB &= ~(1 << PB5); // pin 13 LOW
      PORTD |= (1 << PD5);  // pin 5 HIGH
    }
    _delay_ms(50); // debounce
  }
  return 0;
}