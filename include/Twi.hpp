#pragma once
#include <stdint.h>
#include <util/twi.h>

typedef enum TwiStatus {
  TWI_OK,
  TWI_START_NOT_SET,
  TWI_ADDRESS_NOT_SET,
  TWI_REGISTER_NOT_SET,
  TWI_DATA_NOT_SET
} twi_status_t;

class Twi {
 private:
  static twi_status_t write(char data);
  static twi_status_t write(uint8_t reg, char data);
  static char read_byte(bool acknowledge);

 public:
  static twi_status_t start(uint8_t address);
  static void stop();
  static twi_status_t read(int8_t *buffer, uint8_t length,
                           uint8_t write_address, uint8_t read_address,
                           uint8_t reg);

  static twi_status_t write(uint8_t address, uint8_t reg, char data);
};