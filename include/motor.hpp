#pragma once

#include <stdint.h>

typedef enum
{
  FORWARD,
  BACKWARD
} Direction;

class Motor
{
public:
  Motor();
  void left(Direction direction, uint8_t speed);
  void right(Direction direction, uint8_t speed);
  void left_stop();
  void right_stop();
};
