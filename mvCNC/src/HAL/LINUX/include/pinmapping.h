/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../../../inc/mvCNCConfigPre.h"

#include <stdint.h>
#include "../hardware/Gpio.h"

typedef pin_type pin_t;

#define P_NC -1
constexpr uint16_t NUM_DIGITAL_PINS = Gpio::pin_count;
constexpr uint8_t NUM_ANALOG_INPUTS = 16;

#define HAL_SENSITIVE_PINS

constexpr uint8_t analog_offset = NUM_DIGITAL_PINS - NUM_ANALOG_INPUTS;

// Get the digital pin for an analog index
constexpr pin_t analogInputToDigitalPin(const int8_t p) {
  return (WITHIN(p, 0, NUM_ANALOG_INPUTS) ? analog_offset + p : P_NC);
}

// Get the analog index for a digital pin
constexpr int8_t DIGITAL_PIN_TO_ANALOG_PIN(const pin_t p) {
  return (WITHIN(p, analog_offset, NUM_DIGITAL_PINS) ? p - analog_offset : P_NC);
}

// Return the index of a pin number
constexpr int16_t GET_PIN_MAP_INDEX(const pin_t pin) { return pin; }

// Test whether the pin is valid
constexpr bool VALID_PIN(const pin_t p) { return WITHIN(p, 0, NUM_DIGITAL_PINS); }

// Test whether the pin is PWM
constexpr bool PWM_PIN(const pin_t p) { return false; }

// Test whether the pin is interruptible
constexpr bool INTERRUPT_PIN(const pin_t p) { return false; }

// Get the pin number at the given index
constexpr pin_t GET_PIN_MAP_PIN(const int16_t ind) { return ind; }

// Parse a G-code word into a pin index
int16_t PARSED_PIN_INDEX(const char code, const int16_t dval);
