#define F_CPU 16000000UL

#include "motor.hpp"
#include "usart.hpp"
#include <avr/delay.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

Motor motor;

void setup()
{
  motor = Motor();
  Usart::init();
}

int main(int argc, char *argv[])
{
  setup();

  //motor.left(Direction::FORWARD, 100);
  //motor.right(Direction::FORWARD, 255);
  while (true)
  {
  }

  return 0;
}
