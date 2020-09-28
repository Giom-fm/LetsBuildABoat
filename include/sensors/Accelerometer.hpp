#pragma once

#include <stdint.h>

#include "sensors/TwiSensor.hpp"

typedef struct Acceleration {
  int16_t x;
  int16_t y;
  int16_t z;
} acceleration_t;

class Accelerometer : public TwiSensor {
 public:
  Accelerometer();
  acceleration_t read();
  bool has_next_value();
};