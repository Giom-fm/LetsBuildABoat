#define F_CPU 16000000UL

#include "Adc.hpp"
#include "Motor.hpp"
#include "Usart.hpp"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

Motor motor;

void setup()
{
  motor = Motor();
  Usart::init();
  Adc::init();
}

void print_motor_status()
{
  MotorStatus left, right;
  motor.get_status(&left, &right);
  //Usart::print_ln("Motor Status");
  Usart::print_ln("\tLeft\t Enable: %d\tSpeed: %d\tCurrent: %f", left.enable,
                  left.speed, left.current);
  //Usart::print_ln("\tRight\t Enable: %d\tSpeed: %d\tCurrent: %f", right.enable,
   //               right.speed, right.current);
}

int main(int argc, char *argv[])
{
  setup();

  motor.left(100);
  //motor.right(-75);
  while (true)
  {
    print_motor_status();
    _delay_ms(100);
  }

  return 0;
}
