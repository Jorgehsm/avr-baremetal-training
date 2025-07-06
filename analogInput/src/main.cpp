#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

// Reads ADC 0
// Alternates the state of pin 5 (PD5):
// when ADC reading is greater than 512, pin 5 is LOW, and vice versa.

void usart_init(void)
{
  uint16_t ubrr = 103; // 16 MHz 9600 baudrate (U2X0 = 0)
  UBRR0H = (ubrr >> 8);
  UBRR0L = ubrr;
  UCSR0B = (1 << TXEN0);                  // Enables transmission
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

void usart_send_char(char c)
{
  while (!(UCSR0A & (1 << UDRE0))); // Waits emptying buffer
  UDR0 = c;
}

void usart_send_string(const char *str)
{
  while (*str)
  {
    usart_send_char(*str++);
  }
}

void usart_send_uint16(uint16_t value)
{
  char buffer[6];          // Max 65535 + '\0'
  itoa(value, buffer, 10); // base 10
  usart_send_string(buffer);
}

void adc_init(void)
{
  ADMUX = (1 << REFS0);                                  // Reference AVcc (5V), channel ADC0 (A0)
  ADCSRA = (1 << ADEN)                                   // Enables ADC
           | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
}

uint16_t adc_read(void)
{
  ADCSRA |= (1 << ADSC);          // Starts conversion
  while (ADCSRA & (1 << ADSC));   // Waits conversion
  return ADC;                     // returns (ADCL + ADCH)
}

int main(void)
{
  usart_init();
  adc_init();         // Starts ADC
  DDRD |= (1 << PD5); // LED 5 As OUTPUT

  while (1)
  {
    uint16_t value = adc_read();

    if (value > 512)
    {
      PORTD |= (1 << PD5);
    }
    else
    {
      PORTD &= ~(1 << PD5);
    }

    usart_send_uint16(value);
    usart_send_string("\r\n");

    _delay_ms(100);
  }
}