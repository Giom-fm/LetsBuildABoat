#include "motor.hpp"
#include <avr/io.h>

#define LEFT_FORWARD OCR0A
#define LEFT_BACKWARD OCR0B
#define RIGHT_FORWARD OCR2A
#define RIGHT_BACKWARD OCR2B

Motor::Motor()
{

  // Init Timer 0 For Left Motor
  // Set Fast-PWM-Mode
  TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  // Set Prescaler to 64
  TCCR0B = (1 << CS01) | (1 << CS00);
  // Set OC0A and OC9B as output ports
  DDRD |= (1 << PORTD5) | (1 << PORTD6);

  // Init Timer 2 for Right Motor
  TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
  // Set Prescaler to 64
  TCCR2B = (1 << CS22);
  // Set OC0A and OC0B as output ports
  DDRD |= (1 << PORTD3);
  DDRB |= (1 << PORTB3);
}

void Motor::left(Direction direction, uint8_t speed)
{
  if (direction == Direction::FORWARD)
  {
    LEFT_FORWARD = speed;
    LEFT_BACKWARD = 0;
  }
  else
  {
    LEFT_FORWARD = 0;
    LEFT_BACKWARD = speed;
  }
}

void Motor::left_stop()
{
  LEFT_FORWARD = 0;
  LEFT_BACKWARD = 0;
}

void Motor::right_stop()
{
  RIGHT_FORWARD = 0;
  RIGHT_BACKWARD = 0;
}

void Motor::right(Direction direction, uint8_t speed)
{
  if (direction == Direction::FORWARD)
  {
    RIGHT_FORWARD = speed;
    RIGHT_BACKWARD = 0;
  }
  else
  {
    RIGHT_FORWARD = 0;
    RIGHT_BACKWARD = speed;
  }
}
