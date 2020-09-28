#pragma once

#include <stdint.h>

#include "TwiSensor.hpp"

typedef struct MagneticField {
  int16_t x;
  int16_t y;
  int16_t z;
} magnetic_field_t;

class Magnetometer : public TwiSensor {
 public:
  Magnetometer();
  bool has_next_value();
  magnetic_field_t read();
};