#define F_CPU 16000000UL

#include "motor.hpp"
#include <Arduino.h>
#include <avr/delay.h>
#include <avr/io.h>
#include <stdbool.h>

Motor motor;

void setup() { motor = Motor(); }

int main(int argc, char *argv[])
{
  setup();

  DDRB |= (1 << DDB5);

  int power = 50;
  bool reverse = false;
  while (true)
  {

    _delay_ms(50);

    if (power >= 255)
    {

      _delay_ms(15000);
      reverse = true;
    }
    else if (power <= 50)
      reverse = false;

    motor.left(Direction::FORWARD, power);
    motor.right(Direction::FORWARD, power);
    power += reverse ? -1 : 1;
  }

  return 0;
}
