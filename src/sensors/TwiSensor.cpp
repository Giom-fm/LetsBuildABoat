#include "sensors/TwiSensor.hpp"

#include "Twi.hpp"

//##############################################################################

#define BUFFER_SIZE 6

twi_status_t TwiSensor::has_next_value(bool* value, uint8_t write_address,
                                       uint8_t read_address,
                                       uint8_t status_register,
                                       uint8_t status_flag) {
  twi_status_t status;
  int8_t data;

  status = Twi::read(&data, 1, write_address, read_address, status_register);
  if (status != TWI_OK) return status;

  *value = (data & (1 << status_flag));

  return TWI_OK;
}

twi_status_t TwiSensor::read(raw_axis_values_t* data, uint8_t write_address,
                             uint8_t read_address, uint8_t start_register) {
  twi_status_t status;
  int8_t buffer[BUFFER_SIZE];

  status = Twi::read(buffer, BUFFER_SIZE, write_address, read_address,
                     start_register);

  if (status != TWI_OK) return status;

  *data = {.x = (buffer[1] << 8) | (buffer[0] & 0xff),
           .y = (buffer[3] << 8) | (buffer[2] & 0xff),
           .z = (buffer[5] << 8) | (buffer[4] & 0xff)};

  return TWI_OK;
}