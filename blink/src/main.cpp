#include <avr/io.h>
#include <util/delay.h>

// This code alternates the states of pins 13 (PB5) and 5 (PD5):
// when pin 13 is HIGH, pin 5 is LOW, and vice versa.
// The state toggles every 500 milliseconds.

int main(void)
{
    DDRB |= (1 << PB5); // pin 13 OUTPUT
    DDRD |= (1 << PD5); // pin 5 OUTPUT

    while (1)
    {
        PORTB |= (1 << PB5);  // pin 13 HIGH
        PORTD &= ~(1 << PD5); // pin 5 LOW

        _delay_ms(500);

        PORTB &= ~(1 << PB5); // pin 13 LOW
        PORTD |= (1 << PD5);  // pin 5 HIGH
        _delay_ms(500);
    }

    return 0;
}