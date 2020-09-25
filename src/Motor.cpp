#include "Motor.hpp"

#include <avr/io.h>
#include <stdlib.h>

#include "Adc.hpp"
#include "Util.hpp"

#define LEFT_FORWARD OCR0A
#define LEFT_BACKWARD OCR0B
#define RIGHT_FORWARD OCR2A
#define RIGHT_BACKWARD OCR2B
#define LEFT_DIAG PIND2
#define RIGHT_DIAG PIND4
#define LEFT_CURRENT 0
#define RIGHT_CURRENT 1

Motor::Motor() {
  Motor::status_left = {.enable = 0, .speed = 0, .current = 0};
  Motor::status_right = {.enable = 0, .speed = 0, .current = 0};

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
  // PORTD &= ~(1 << PORTD3);
  DDRB |= (1 << PORTB3);
  // PORTB &= ~(1 << PORTB3);

  // Set Diag Pins as input
  DDRD &= ~((1 << PORTD2) | (1 << PORTD4));
}

void Motor::get_status(MotorStatus *left, MotorStatus *right) {
  Motor::status_left.enable = (PIND & (1 << LEFT_DIAG)) >> LEFT_DIAG;
  Motor::status_right.enable = (PIND & (1 << RIGHT_DIAG)) >> RIGHT_DIAG;
  Motor::status_left.current = Adc::read_voltage_avg(LEFT_CURRENT, 10);
  Motor::status_right.current = Adc::read_voltage_avg(RIGHT_CURRENT, 10);

  *left = Motor::status_left;
  *right = Motor::status_right;
}

void Motor::left(int8_t speed_percent) {
  uint8_t speed = Util::map(abs(speed_percent), 0, 100, 0, 255);
  Motor::status_left.speed = speed_percent;

  if (speed_percent > 0) {
    LEFT_FORWARD = speed;
    LEFT_BACKWARD = 0;
  } else if (speed_percent < 0) {
    LEFT_FORWARD = 0;
    LEFT_BACKWARD = speed;
  } else {
    LEFT_FORWARD = 0;
    LEFT_BACKWARD = 0;
  }
}

void Motor::right(int8_t speed_percent) {
  uint8_t speed = Util::map(abs(speed_percent), 0, 100, 0, 255);
  Motor::status_right.speed = speed_percent;

  if (speed_percent > 0) {
    RIGHT_FORWARD = speed;
    RIGHT_BACKWARD = 0;
  } else if (speed_percent < 0) {
    RIGHT_FORWARD = 0;
    RIGHT_BACKWARD = speed;
  } else {
    RIGHT_FORWARD = 0;
    RIGHT_BACKWARD = 0;
  }
}

void Motor::left_stop() {
  LEFT_FORWARD = 0;
  LEFT_BACKWARD = 0;
}

void Motor::right_stop() {
  RIGHT_FORWARD = 0;
  RIGHT_BACKWARD = 0;
}
