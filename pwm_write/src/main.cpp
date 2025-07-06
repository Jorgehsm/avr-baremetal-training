#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

// Reads ADC 0 and sets PWM duty cycle proportionally


void pwm_init(void)
{
    DDRD |= (1 << PD5); // PD5 (OC0B) as OUTPUT

    // Configures Timer0 in Fast PWM mode
    TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); // Fast PWM
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler = 64 (16MHz / 64 = 250kHz)

    // Initial duty cycle= 0
    OCR0A = 0;
}

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
  pwm_init();         // Iniatializes PWM
  usart_init();       // Iniatializes Serial
  adc_init();         // Iniatializes ADC
  DDRD |= (1 << PD5); // LED 5 As OUTPUT

  while (1)
  {
    uint16_t value = adc_read();
    OCR0B = value/4; //ADC reading is 0-1023 whileduty cylce is 0-255

    usart_send_uint16(value);
    usart_send_string("\r\n");

    _delay_ms(100);
  }
}