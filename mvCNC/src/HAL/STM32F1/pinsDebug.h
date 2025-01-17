/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Support routines for MAPLE_STM32F1
 */

/**
 * Translation of routines & variables used by pinsDebug.h
 */

#ifndef BOARD_NR_GPIO_PINS // Only in MAPLE_STM32F1
  #error "Expected BOARD_NR_GPIO_PINS not found"
#endif

#include "fastio.h"

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS];

#define NUM_DIGITAL_PINS BOARD_NR_GPIO_PINS
#define NUMBER_PINS_TOTAL BOARD_NR_GPIO_PINS
#define VALID_PIN(pin) (pin >= 0 && pin < BOARD_NR_GPIO_PINS)
#define GET_ARRAY_PIN(p) pin_t(pin_array[p].pin)
#define pwm_status(pin) PWM_PIN(pin)
#define digitalRead_mod(p) extDigitalRead(p)
#define PRINT_PIN(p) do{ sprintf_P(buffer, PSTR("%3hd "), int16_t(p)); SERIAL_ECHO(buffer); }while(0)
#define PRINT_PIN_ANALOG(p) do{ sprintf_P(buffer, PSTR(" (A%2d)  "), DIGITAL_PIN_TO_ANALOG_PIN(pin)); SERIAL_ECHO(buffer); }while(0)
#define PRINT_PORT(p) print_port(p)
#define PRINT_ARRAY_NAME(x) do{ sprintf_P(buffer, PSTR("%-" STRINGIFY(MAX_NAME_LENGTH) "s"), pin_array[x].name); SERIAL_ECHO(buffer); }while(0)
#define MULTI_NAME_PAD 21 // space needed to be pretty if not first name assigned to a pin

// pins that will cause hang/reset/disconnect in M43 Toggle and Watch utilities
#ifndef M43_NEVER_TOUCH
  #define M43_NEVER_TOUCH(Q) (Q >= 9 && Q <= 12) // SERIAL/USB pins PA9(TX) PA10(RX)
#endif

static int8_t get_pin_mode(pin_t pin) {
  return VALID_PIN(pin) ? _GET_MODE(pin) : -1;
}

static pin_t DIGITAL_PIN_TO_ANALOG_PIN(pin_t pin) {
  if (!VALID_PIN(pin)) return -1;
  int8_t adc_channel = int8_t(PIN_MAP[pin].adc_channel);
  #ifdef NUM_ANALOG_INPUTS
    if (adc_channel >= NUM_ANALOG_INPUTS) adc_channel = ADCx;
  #endif
  return pin_t(adc_channel);
}

static bool IS_ANALOG(pin_t pin) {
  if (!VALID_PIN(pin)) return false;
  if (PIN_MAP[pin].adc_channel != ADCx) {
    #ifdef NUM_ANALOG_INPUTS
      if (PIN_MAP[pin].adc_channel >= NUM_ANALOG_INPUTS) return false;
    #endif
    return _GET_MODE(pin) == GPIO_INPUT_ANALOG && !M43_NEVER_TOUCH(pin);
  }
  return false;
}

static bool GET_PINMODE(const pin_t pin) {
  return VALID_PIN(pin) && !IS_INPUT(pin);
}

static bool GET_ARRAY_IS_DIGITAL(const int16_t array_pin) {
  const pin_t pin = GET_ARRAY_PIN(array_pin);
  return (!IS_ANALOG(pin)
    #ifdef NUM_ANALOG_INPUTS
      || PIN_MAP[pin].adc_channel >= NUM_ANALOG_INPUTS
    #endif
  );
}

#include "../../inc/mvCNCConfig.h" // Allow pins/pins.h to set density

static void pwm_details(const pin_t pin) {
  if (PWM_PIN(pin)) {
    timer_dev * const tdev = PIN_MAP[pin].timer_device;
    const uint8_t channel = PIN_MAP[pin].timer_channel;
    const char num = (
      #if EITHER(STM32_HIGH_DENSITY, STM32_XL_DENSITY)
        tdev == &timer8 ? '8' :
        tdev == &timer5 ? '5' :
      #endif
      tdev == &timer4 ? '4' :
      tdev == &timer3 ? '3' :
      tdev == &timer2 ? '2' :
      tdev == &timer1 ? '1' : '?'
    );
    char buffer[10];
    sprintf_P(buffer, PSTR(" TIM%c CH%c"), num, ('0' + channel));
    SERIAL_ECHO(buffer);
  }
}

static void print_port(pin_t pin) {
  const char port = 'A' + char(pin >> 4); // pin div 16
  const int16_t gbit = PIN_MAP[pin].gpio_bit;
  char buffer[8];
  sprintf_P(buffer, PSTR("P%c%hd "), port, gbit);
  if (gbit < 10) SERIAL_CHAR(' ');
  SERIAL_ECHO(buffer);
}
