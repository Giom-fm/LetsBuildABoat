#pragma once

#include <stdint.h>

typedef struct
{
  bool enable;
  int8_t speed;
} MotorStatus;

class Motor
{

private:
  MotorStatus status_left;
  MotorStatus status_right;

public:
  Motor();
  void left(int8_t speed_percent);
  void right(int8_t speed_percent);
  void left_stop();
  void right_stop();
  void get_status(MotorStatus *left, MotorStatus *right);
};
