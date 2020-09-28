#include "Twi.hpp"

#include "Usart.hpp"

#define WAIT_FOR(bit) while (!(TWCR & (1 << bit)))
#define TWI_STATUS (TWSR & TW_NO_INFO)
#define TWI_START TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN)

twi_status_t Twi::start(uint8_t address) {
  Usart::print_ln("TWI Start");

  // Clear Interrupt, Set START and Enable TWI
  TWI_START;
  // Wait until interrupt-flag has been set
  WAIT_FOR(TWINT);

  if (TWI_STATUS != TW_START) {
    return TWI_START_NOT_SET;
  }

  twi_status_t status = Twi::write(address);

  if (status != TWI_DATA_NOT_SET) {
    return TWI_ADDRESS_NOT_SET;
  }
  return TWI_OK;
}

void Twi::stop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  WAIT_FOR(TWSTO);
}

twi_status_t Twi::write(char data) {
  // Set Data
  TWDR = data;
  // Clear TWI interrupt flag, Enable TWI
  TWCR = (1 << TWINT) | (1 << TWEN);
  // Wait until interrupt-flag has been set
  WAIT_FOR(TWINT);

  if (TWI_STATUS != TW_MT_SLA_ACK) {
    return TWI_DATA_NOT_SET;
  }

  return TWI_OK;
}

twi_status_t Twi::write(uint8_t reg, char data) {
  twi_status_t status;
  // Set Register
  status = Twi::write(reg);
  if (status != TWI_OK) {
    return TWI_REGISTER_NOT_SET;
  }
  // Set Data
  return Twi::write(data);
}

twi_status_t Twi::write(uint8_t address, uint8_t reg, char data) {
  twi_status_t status;

  status = Twi::start(address);
  if (status == TWI_OK) {
    status = Twi::write(reg, data);
  }

  Twi::stop();
  return status;
}

char Twi::read_byte(bool acknowledge) {
  // Clear TWI interrupt flag, Enable TWI
  // If needed, set acknowledge bit
  if (acknowledge) {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
  } else {
    TWCR = (1 << TWEN) | (1 << TWINT);
  }

  // Wait until interrupt-flag has been set
  WAIT_FOR(TWINT);

  return TWDR;
}

twi_status_t Twi::read(int8_t *buffer, uint8_t length, uint8_t write_address,
                       uint8_t read_address, uint8_t reg) {
  twi_status_t status;

  status = Twi::start(write_address);
  if (status != TWI_OK) return status;

  status = Twi::write(reg);
  if (status != TWI_OK) return TWI_REGISTER_NOT_SET;

  status = Twi::start(read_address);
  if (status != TWI_OK) return status;

  for (uint8_t i = 0; i < length; ++i) {
    *buffer = Twi::read_byte(i < length);
    ++buffer;
  }

  //*data = (result_h << 8) | (result_l & 0xff);

  return TWI_OK;
}
