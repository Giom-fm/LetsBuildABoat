#include "Adc.hpp"
#include "avr/io.h"

// 5V / 1024
#define TEST 0.0050251256

void Adc::init()
{
  // Select Vref=AVcc
  ADMUX |= (1 << REFS0);
  // set prescaller to 128 and enable ADC
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

uint16_t Adc::read_raw(uint8_t channel)
{
  // select ADC channel with safety mask
  ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
  // single conversion mode
  ADCSRA |= (1 << ADSC);
  // wait until ADC conversion is complete
  while (ADCSRA & (1 << ADSC))
    ;
  return ADCW;
}

float Adc::read_voltage(uint8_t channel)
{
  float raw_value = Adc::read_raw(channel);
  return TEST * raw_value;
}

float Adc::read_voltage_avg(uint8_t channel, uint8_t samples)
{
  uint16_t raw_values = 0;
  for (uint8_t i = 0; i < samples; ++i)
  {
    raw_values += Adc::read_raw(channel);
  }

  return TEST * (raw_values / samples);
}
