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

  return TWI_STATUS == TW_REP_START ? Twi::write(address) : TWI_STATUS;
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
  return TWI_STATUS;
}

twi_status_t Twi::write(uint8_t reg, char data) {
  // Set Register
  Twi::write(reg);
  // Set Data
  return Twi::write(data);
}

char Twi::read(bool acknowledge) {
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
