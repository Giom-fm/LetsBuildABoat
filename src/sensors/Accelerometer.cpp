#include "sensors/Accelerometer.hpp"

#include "Twi.hpp"
#include "Usart.hpp"

// Addresses ###################################################################

#define WRITE_ADDRESS 0xD6
#define READ_ADDRESS 0xD7

// Registers ###################################################################

#define CTRL9_XL 0x18
#define CTRL1_XL 0x10
#define STATUS_REG 0x1E

// Accel X
#define OUTX_L_XL 0x28
#define OUTX_H_XL 0x29

// Accel Y
#define OUTY_L_XL 0x2A
#define OUTY_H_XL 0x2B

// Accel Z
#define OUTZ_L_XL 0x2C
#define OUTZ_H_XL 0x2D

// Bits ########################################################################

// CTRL9_XL
#define Xen_XL 3
#define Yen_XL 4
#define Zen_XL 5

// CTRL1_XL
#define ODR_XL0 4
#define ODR_XL1 5
#define ODR_XL2 6
#define ODR_XL3 7

// STATUS_REG
#define XLDA 0

// Config ######################################################################

// Enable all 3 Axis
#define ACCEL_CONFIG_AXIS ((1 << Zen_XL) | (1 << Yen_XL) | (1 << Xen_XL))
// Set speed to 416Hz
#define ACCEL_CONFIG_CLOCK ((1 << ODR_XL2) | (1 << ODR_XL1))
// #############################################################################

Accelerometer::Accelerometer() {
  twi_status_t status;

  status = Twi::write(WRITE_ADDRESS, CTRL9_XL, ACCEL_CONFIG_AXIS);
  if (status != TWI_OK)
    Usart::print_ln("Accelerometer::Accelerometer - Axis init Error: %d",
                    status);

  status = Twi::write(WRITE_ADDRESS, CTRL1_XL, ACCEL_CONFIG_CLOCK);
  if (status != TWI_OK)
    Usart::print_ln("Accelerometer::Accelerometer - Clock init Error: %d",
                    status);
}

bool Accelerometer::has_next_value() {
  bool result;
  twi_status_t status;
  status = TwiSensor::has_next_value(&result, WRITE_ADDRESS, READ_ADDRESS,
                                     STATUS_REG, XLDA);

  if (status != TWI_OK) {
    Usart::print_ln("Accelerometer::has_next_value - Twi Error: %d", status);
    return false;
  } else {
    return result;
  }
}

acceleration_t Accelerometer::read() {
  twi_status_t status;
  raw_axis_values_t data;

  status = TwiSensor::read(&data, WRITE_ADDRESS, READ_ADDRESS, OUTX_L_XL);
  if (status != TWI_OK)
    Usart::print_ln("Accelerometer::read - Twi Error: %d", status);

  // TODO Convert to acceleration
  return {.x = data.x, .y = data.y, .z = data.z};
}