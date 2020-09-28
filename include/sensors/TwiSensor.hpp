#pragma once

#include <stdint.h>

#include "Twi.hpp"

typedef struct AxisValues {
  int16_t x;
  int16_t y;
  int16_t z;
} raw_axis_values_t;

class TwiSensor {
 protected:
  twi_status_t read(raw_axis_values_t* data, uint8_t write_address,
                    uint8_t read_address, uint8_t start_register);

  twi_status_t has_next_value(bool* value, uint8_t write_address,
                              uint8_t read_address, uint8_t status_register,
                              uint8_t status_flag);
};