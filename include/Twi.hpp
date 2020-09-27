#pragma once

#include "stdint.h"

typedef uint8_t twi_status_t;

class Twi {
 private:
  static twi_status_t write(char data);

 public:
  static void start(uint8_t address);
  static void stop();
  static char read(bool acknowledge);
  static twi_status_t write(uint8_t reg, char data);
};