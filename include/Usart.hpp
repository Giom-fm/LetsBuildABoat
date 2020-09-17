#pragma once

#define BAUD 9600

class Usart
{

public:
  static void init();
  static void print_ln(const char *s, ...);

private:
  static void print_c(const char c);
};
