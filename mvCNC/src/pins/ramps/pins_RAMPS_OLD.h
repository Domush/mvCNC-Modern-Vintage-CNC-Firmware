/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Arduino Mega with RAMPS v1.0, v1.1, v1.2 pin assignments
 */

#include "env_validate.h"

#define BOARD_INFO_NAME "RAMPS <1.2"

// Uncomment the following line for RAMPS v1.0
//#define RAMPS_V_1_0

//
// Limit Switches
//
#define X_MIN_PIN                              3
#define X_MAX_PIN                              2
#define Y_MIN_PIN                             16
#define Y_MAX_PIN                             17
#define Z_MIN_PIN                             18
#define Z_MAX_PIN                             19

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                     19
#endif

//
// Steppers
//
#define X_STEP_PIN                            26
#define X_DIR_PIN                             28
#define X_ENABLE_PIN                          24

#define Y_STEP_PIN                            38
#define Y_DIR_PIN                             40
#define Y_ENABLE_PIN                          36

#define Z_STEP_PIN                            44
#define Z_DIR_PIN                             46
#define Z_ENABLE_PIN                          42

#define E0_STEP_PIN                           32
#define E0_DIR_PIN                            34
#define E0_ENABLE_PIN                         30

//
// Temperature Sensors
//
#define TEMP_0_PIN                             2  // Analog Input
#define TEMP_BED_PIN                           1  // Analog Input

// SPI for MAX Thermocouple
#if DISABLED(SDSUPPORT)
  #define TEMP_0_CS_PIN                       66  // Don't use 53 if using Display/SD card
#else
  #define TEMP_0_CS_PIN                       66  // Don't use 49 (SD_DETECT_PIN)
#endif

//
// Heaters / Fans
//
#if ENABLED(RAMPS_V_1_0)
  #define HEATER_0_PIN                        12
  #define HEATER_BED_PIN                      -1
  #ifndef FAN_PIN
    #define FAN_PIN                           11
  #endif
#else                                             // RAMPS_V_1_1 or RAMPS_V_1_2
  #define HEATER_0_PIN                        10
  #define HEATER_BED_PIN                       8
  #ifndef FAN_PIN
    #define FAN_PIN                            9
  #endif
#endif

//
// Misc. Functions
//
#define SDPOWER_PIN                           48
#define SDSS                                  53
#define LED_PIN                               13

#ifndef CASE_LIGHT_PIN
  #define CASE_LIGHT_PIN                      45  // Hardware PWM
#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
#define SPINDLE_LASER_ENA_PIN                 41  // Pullup or pulldown!
#define SPINDLE_LASER_PWM_PIN                 45  // Hardware PWM
#define SPINDLE_DIR_PIN                       43
