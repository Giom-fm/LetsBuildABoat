#include "usart.hpp"
#include <avr/io.h>
#include <util/setbaud.h>

void Usart::init()
{
  // Enable UART Transmitter mode
  UCSR0B = _BV(TXEN0);
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif

  // Set Frame format to 8 data with 1 stop bits
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  // Sends a "new Line"
  Usart::print_c('\r');
  Usart::print_c('\n');
}

void Usart::print_ln(const char *s)
{
  while (*s)
  {
    Usart::print_c(*s);
    s++;
  }

  Usart::print_c('\r');
  Usart::print_c('\n');
}

/*
 * Blocks until buffer is empty and sends the passed character.
 * @param c The character to send.
 */
void Usart::print_c(const char c)
{
  // Wait until UART Data Register is empty
  while (!(UCSR0A & (1 << UDRE0)))
  {
  }
  // Set Character into Data Register
  UDR0 = c;
}