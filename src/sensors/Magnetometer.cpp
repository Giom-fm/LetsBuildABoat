#include "sensors/Magnetometer.hpp"

#include "Twi.hpp"
#include "Usart.hpp"

// Addresses ###################################################################

#define READ_ADDRESS 0x3C
#define WRITE_ADDRESS 0x3D

// Registers ###################################################################

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23

#define STATUS_REG 0x27

#define OUT_X_L 0x28
#define OUT_X_H 0x29

#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B

#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

// Bits ########################################################################

// CTRL_REG1
#define DO0 2
#define DO1 3
#define DO2 4
#define OM0 5
#define OM1 6

// CTRL_REG2
#define FS0 5
#define FS1 6

// CTRL_REG4
#define OMZ0 2
#define OMZ1 3

// STATUS_REG
#define ZYXDA 3
#define ZYXOR 7

//##############################################################################

Magnetometer::Magnetometer() {
  twi_status_t status;

  // Set Fullscale to 16 gauss
  status = Twi::write(WRITE_ADDRESS, CTRL_REG2, (1 << FS1) | (1 << FS0));
  if (status != TWI_OK)
    Usart::print_ln("Magnetometer::Magnetometer - Set Fullscale Error: %d",
                    status);

  // Set UHP mode for X/Y and ODR at 80Hz
  status = Twi::write(
      WRITE_ADDRESS, CTRL_REG1,
      (1 << OM1) | (1 << OM0) | (1 << DO2) | (1 << DO1) | (1 << DO0));
  if (status != TWI_OK)
    Usart::print_ln("Magnetometer::Magnetometer - Set X/Y-Axis Error: %d",
                    status);

  // Set UHP mode for Z
  status = Twi::write(WRITE_ADDRESS, CTRL_REG4, (1 << OMZ1) | (1 << OMZ0));
  if (status != TWI_OK)
    Usart::print_ln("Magnetometer::Magnetometer - Set Z-Axis Error: %d",
                    status);

  // Set Continuous mode
  status = Twi::write(WRITE_ADDRESS, CTRL_REG3, 0);
  if (status != TWI_OK)
    Usart::print_ln(
        "Magnetometer::Magnetometer - Set  Set Continuous mode Error: %d",
        status);
}

bool Magnetometer::has_next_value() {
  bool result;
  twi_status_t status;
  status = TwiSensor::has_next_value(&result, WRITE_ADDRESS, READ_ADDRESS,
                                     STATUS_REG, ZYXDA);

  if (status != TWI_OK) {
    Usart::print_ln("Magnetometer::has_next_value - Twi Error: %d", status);
    return false;
  } else {
    return result;
  }
}

magnetic_field_t Magnetometer::read() {
  twi_status_t status;
  raw_axis_values_t data;

  status = TwiSensor::read(&data, WRITE_ADDRESS, READ_ADDRESS, OUT_X_L);
  if (status != TWI_OK)
    Usart::print_ln("Magnetometer::read - Twi Error: %d", status);

  // TODO Convert to direction
  return {.x = data.x, .y = data.y, .z = data.z};
}