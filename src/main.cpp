#define F_CPU 16000000UL

#include "Motor.hpp"
#include "Usart.hpp"
#include <avr/delay.h>
#include <avr/io.h>
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

  motor.left(100);
  motor.right(-75);
  while (true)
  {
    MotorStatus left, right;
    motor.get_status(&left, &right);
    _delay_ms(1000);
    Usart::print_ln("Motor Status");
    Usart::print_ln("\tLeft\t Enable: %d\tSpeed: %d", left.enable,
                    left.speed);
    Usart::print_ln("\tRight\t Enable: %d\tSpeed: %d", right.enable,
                    right.speed);
  }

  return 0;
}
