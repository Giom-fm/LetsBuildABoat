#pragma once

#include <stdint.h>

class Adc {
 public:
  static void init();
  static float read_voltage(uint8_t channel);
  static float read_voltage_avg(uint8_t channel, uint8_t samples);

 private:
  static uint16_t read_raw(uint8_t channel);
};