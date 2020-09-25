#pragma once

#include "stdint.h"

class Twi {
 public:
  static void start(uint8_t address);
  static void stop();
  static char read(bool acknowledge);
  static uint8_t write(char data);
};