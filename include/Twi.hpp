#pragma once
#include <stdint.h>
#include <util/twi.h>

typedef uint8_t twi_status_t;

class Twi {
 public:
  static twi_status_t start(uint8_t address);
  static void stop();
  static char read(bool acknowledge);
  static twi_status_t write(char data);
  static twi_status_t write(uint8_t reg, char data);
};