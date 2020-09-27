#include "Twi.hpp"

#include <util/twi.h>

#include "Usart.hpp"

#define WAIT_FOR(bit) while (!(TWCR & (1 << bit)))
#define TWI_STATUS (TWSR & TW_NO_INFO)

void Twi::start(uint8_t address) {
  while (1) {
    Usart::print_ln("TWI Start");
    // Clear Interrupt, Set START and Enable TWI
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // Wait until interrupt-flag has been set
    WAIT_FOR(TWINT);

    // check Status - if Fail -> Retry
    if (TWI_STATUS != TW_START && TWI_STATUS != TW_REP_START) {
      Usart::print_ln("TWI Start-Error: Startcondition not set 0x%x",
                      TWI_STATUS);
      continue;
    }

    uint8_t status = Twi::write(address);

    // Check Status - If Fail Stop and retry
    if (status != TW_MT_SLA_ACK) {
      Usart::print_ln("TWI Start-Error: ACK not received 0x%x", status);
      Twi::stop();
      continue;
    }
    break;
  }
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
  Twi::write(data);
  return TWI_STATUS;
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
