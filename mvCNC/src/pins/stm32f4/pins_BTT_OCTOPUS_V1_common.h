/**
 * Modern Vintage CNC Firmware
 * Copyright (c) 2021 mvCNCFirmware [https://github.com/Domush/mvCNC-Modern-Vintage-CNC-Firmware]
 *
 * Based on Marlin and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "env_validate.h"

#define HAS_OTG_USB_HOST_SUPPORT                  // USB Flash Drive support
#define USES_DIAG_JUMPERS
#define DIAG_JUMPERS_REMOVED  // enable this if you don't use SENSORLESS_HOMING and removed the DIAG jumpers from the board.

// Onboard I2C EEPROM
#define I2C_EEPROM
#define MVCNC_EEPROM_SIZE                0x8000  // 32KB (24C32A)
#define I2C_SCL_PIN                         PB8
#define I2C_SDA_PIN                         PB9

// Avoid conflict with TIMER_TONE
#define STEP_TIMER 10

//
// Servos
//
#define SERVO0_PIN                          PB6

//
// Misc. Functions
//
#define LED_PIN                             PA13

#define ENDSTOP0 PG6   // X-MIN
#define ENDSTOP1 PG9   // Y-MIN
#define ENDSTOP2 PG10  // Y2-MIN
#define ENDSTOP3 PG11  // Z-MAX
#define ENDSTOP4 PG12  //
#define ENDSTOP5 PG13  //
#define ENDSTOP6 PG14  //
#define ENDSTOP7 PG15  //

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                   PB7
#endif

//
// Check for additional used endstop pins
//
#if HAS_EXTRA_ENDSTOPS
  #define _ENDSTOP_IS_ANY(ES) X2_USE_ENDSTOP == ES || Y2_USE_ENDSTOP == ES || Z2_USE_ENDSTOP == ES || Z3_USE_ENDSTOP == ES || Z4_USE_ENDSTOP == ES
  #if _ENDSTOP_IS_ANY(_XMIN_) || _ENDSTOP_IS_ANY(_XMAX_)
    #define NEEDS_X_MINMAX 1
  #endif
  #if _ENDSTOP_IS_ANY(_YMIN_) || _ENDSTOP_IS_ANY(_YMAX_)
    #define NEEDS_Y_MINMAX 1
  #endif
  #if _ENDSTOP_IS_ANY(_ZMIN_) || _ENDSTOP_IS_ANY(_ZMAX_)
    #define NEEDS_Z_MINMAX 1
  #endif
  #undef _ENDSTOP_IS_ANY
#endif

//
// Limit Switches
//
#ifdef X_STALL_SENSITIVITY
  #define X_STOP_PIN ENDSTOP0
  #if X_HOME_TO_MIN
    #define X_MAX_PIN ENDSTOP4  //
  #else
    #define X_MIN_PIN ENDSTOP4  //
  #endif
#elif EITHER(DUAL_X_CARRIAGE, NEEDS_X_MINMAX)
  #ifndef X_MIN_PIN
    #define X_MIN_PIN ENDSTOP0  // X-STOP
  #endif
  #ifndef X_MAX_PIN
    #define X_MAX_PIN ENDSTOP4  //
  #endif
#else
  #define X_STOP_PIN ENDSTOP0  // X-STOP
#endif

#ifdef Y_STALL_SENSITIVITY
  #define Y_STOP_PIN ENDSTOP1
  #if Y_HOME_TO_MIN
    #define Y_MAX_PIN ENDSTOP5  //
  #else
    #define Y_MIN_PIN ENDSTOP5  //
  #endif
#elif NEEDS_Y_MINMAX
  #ifndef Y_MIN_PIN
    #define Y_MIN_PIN ENDSTOP1  // Y-STOP
  #endif
  #ifndef Y_MAX_PIN
    #define Y_MAX_PIN ENDSTOP5  //
  #endif
#else
  #define Y_STOP_PIN ENDSTOP1  // Y-STOP
#endif

#ifdef Z_STALL_SENSITIVITY
  #define Z_STOP_PIN ENDSTOP2
  #if Z_HOME_TO_MIN
    #define Z_MAX_PIN ENDSTOP6  //
  #else
    #define Z_MIN_PIN ENDSTOP6  //
  #endif
#elif NEEDS_Z_MINMAX
  #ifndef Z_MIN_PIN
    #define Z_MIN_PIN ENDSTOP2  // Z-STOP
  #endif
  #ifndef Z_MAX_PIN
    #define Z_MAX_PIN ENDSTOP6  //
  #endif
#else
  #define Z_STOP_PIN ENDSTOP2  // Z-STOP
#endif

#undef NEEDS_X_MINMAX
#undef NEEDS_Y_MINMAX
#undef NEEDS_Z_MINMAX

//
// Power Supply Control
//
#ifndef PS_ON_PIN
  #define PS_ON_PIN                         PE11  // PS-ON
#endif

//
// Power Loss Detection
//
#ifndef POWER_LOSS_PIN
  #define POWER_LOSS_PIN                    PC0   // PWRDET
#endif

//
// Steppers
//
#define X_STEP_PIN                          PF13  // MOTOR 0
#define X_DIR_PIN                           PF12
#define X_ENABLE_PIN                        PF14
#ifndef X_CS_PIN
  #define X_CS_PIN                          PC4
#endif

#define X2_STEP_PIN   PG0  // MOTOR 1
#define X2_DIR_PIN    PG1
#define X2_ENABLE_PIN PF15
#ifndef X2_CS_PIN
  #define X2_CS_PIN PD11
#endif

#define Y_STEP_PIN   PF11  // MOTOR 2
#define Y_DIR_PIN    PG3
#define Y_ENABLE_PIN PG5
#ifndef Y_CS_PIN
  #define Y_CS_PIN PC6
#endif

#define Y2_STEP_PIN   PG4  // MOTOR 3
#define Y2_DIR_PIN    PC1
#define Y2_ENABLE_PIN PA0
#ifndef Y2_CS_PIN
  #define Y2_CS_PIN PC7
#endif

#define Z_STEP_PIN   PF9  // MOTOR 4
#define Z_DIR_PIN    PF10
#define Z_ENABLE_PIN PG2
#ifndef Z_CS_PIN
  #define Z_CS_PIN PF2
#endif

#define Z2_STEP_PIN   PC13  // MOTOR 5
#define Z2_DIR_PIN    PF0
#define Z2_ENABLE_PIN PF1
#ifndef Z2_CS_PIN
  #define Z2_CS_PIN PE4
#endif

#define I_STEP_PIN   PE2  // MOTOR 6
#define I_DIR_PIN    PE3
#define I_ENABLE_PIN PD4
#ifndef I_CS_PIN
  #define I_CS_PIN PE1
#endif

#define J_STEP_PIN   PE6  // MOTOR 7
#define J_DIR_PIN    PA14
#define J_ENABLE_PIN PE0
#ifndef J_CS_PIN
  #define J_CS_PIN PD3
#endif

//
// Temperature Sensors
//
#define TEMP_BED_PIN                        PF3   // TB
#define TEMP_1_PIN                          PF5   // TH1
#define TEMP_2_PIN                          PF6   // TH2
#define TEMP_3_PIN                          PF7   // TH3

//
// Heaters / Fans
//
#define HEATER_BED_PIN                      PA1   // Hotbed
#define HEATER_0_PIN                        PA2   // Heater0
#define HEATER_1_PIN                        PA3   // Heater1
#define HEATER_2_PIN                        PB10  // Heater2
#define HEATER_3_PIN                        PB11  // Heater3

#define FAN_PIN                             PA8   // Fan0
// #define FAN1_PIN                            PE5   // Fan1
// #define FAN2_PIN                            PD12  // Fan2
// #define FAN3_PIN                            PD13  // Fan3
// #define FAN4_PIN                            PD14  // Fan4
// #define FAN5_PIN                            PD15  // Fan5

#if ENABLED(WII_NUNCHUCK) && !defined(WII_EN_PIN)
//#define WII_EN_PIN                        ENDSTOP5 // Default: Endstop5
#endif

//
// SD Support
//
#ifndef SDCARD_CONNECTION
  #if HAS_WIRED_LCD
    #define SDCARD_CONNECTION                LCD
  #else
    #define SDCARD_CONNECTION            ONBOARD
  #endif
#endif

//
// Software SPI pins for TMC2130 stepper drivers
//
#if ENABLED(TMC_USE_SW_SPI)
  #ifndef TMC_SW_MOSI
    #define TMC_SW_MOSI                     PA7
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO                     PA6
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK                      PA5
  #endif
#endif

#if HAS_TMC_UART
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  //#define X_HARDWARE_SERIAL  Serial1
  //#define X2_HARDWARE_SERIAL Serial1
  //#define Y_HARDWARE_SERIAL  Serial1
  //#define Y2_HARDWARE_SERIAL Serial1
  //#define Z_HARDWARE_SERIAL  Serial1
  //#define Z2_HARDWARE_SERIAL Serial1
  //#define E0_HARDWARE_SERIAL Serial1
  //#define E1_HARDWARE_SERIAL Serial1
  //#define E2_HARDWARE_SERIAL Serial1
  //#define E3_HARDWARE_SERIAL Serial1
  //#define E4_HARDWARE_SERIAL Serial1

  #define X_SERIAL_TX_PIN                   PC4
  #define X_SERIAL_RX_PIN        X_SERIAL_TX_PIN

  #define Y_SERIAL_TX_PIN                   PD11
  #define Y_SERIAL_RX_PIN        Y_SERIAL_TX_PIN

  #define Z_SERIAL_TX_PIN                   PC6
  #define Z_SERIAL_RX_PIN        Z_SERIAL_TX_PIN

  #define Z2_SERIAL_TX_PIN                  PC7
  #define Z2_SERIAL_RX_PIN      Z2_SERIAL_TX_PIN

  #define E0_SERIAL_TX_PIN                  PF2
  #define E0_SERIAL_RX_PIN      E0_SERIAL_TX_PIN

  #define E1_SERIAL_TX_PIN                  PE4
  #define E1_SERIAL_RX_PIN      E1_SERIAL_TX_PIN

  #define E2_SERIAL_TX_PIN                  PE1
  #define E2_SERIAL_RX_PIN      E2_SERIAL_TX_PIN

  #define E3_SERIAL_TX_PIN                  PD3
  #define E3_SERIAL_RX_PIN      E3_SERIAL_TX_PIN

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    19200
#endif

/**               ------                                      ------
 * (BEEPER) PE8  |10  9 | PE7  (BTN_ENC)         (MISO) PA6  |10  9 | PA5  (SCK)
 * (LCD_EN) PE9  | 8  7 | PE10 (LCD_RS)       (BTN_EN1) PB2  | 8  7 | PA4  (SD_SS)
 * (LCD_D4) PE12   6  5 | PE13 (LCD_D5)       (BTN_EN2) PB1    6  5 | PA7  (MOSI)
 * (LCD_D6) PE14 | 4  3 | PE15 (LCD_D7)     (SD_DETECT) PC15 | 4  3 | RESET
 *           GND | 2  1 | 5V                             GND | 2  1 | --
 *                ------                                      ------
 *                 EXP1                                        EXP2
 */
#define EXP1_03_PIN                         PE15
#define EXP1_04_PIN                         PE14
#define EXP1_05_PIN                         PE13
#define EXP1_06_PIN                         PE12
#define EXP1_07_PIN                         PE10
#define EXP1_08_PIN                         PE9
#define EXP1_09_PIN                         PE7
#define EXP1_10_PIN                         PE8

#define EXP2_03_PIN                         -1
#define EXP2_04_PIN                         PC15
#define EXP2_05_PIN                         PA7
#define EXP2_06_PIN                         PB2
#define EXP2_07_PIN                         PA4
#define EXP2_08_PIN                         PB1
#define EXP2_09_PIN                         PA5
#define EXP2_10_PIN                         PA6

//
// Onboard SD card
// Must use soft SPI because mvCNC's default hardware SPI is tied to LCD's EXP2
//
#if SD_CONNECTION_IS(ONBOARD)
  #define SDIO_SUPPORT                            // Use SDIO for onboard SD
  #ifndef SD_DETECT_STATE
    #define SD_DETECT_STATE HIGH
  #elif SD_DETECT_STATE == LOW
    #error "BOARD_BTT_OCTOPUS_V1_0 onboard SD requires SD_DETECT_STATE set to HIGH."
  #endif
  #define SD_DETECT_PIN                     PC14
#elif SD_CONNECTION_IS(LCD)

  #define SDSS                              PA4
  #define SD_SS_PIN                         SDSS
  #define SD_SCK_PIN                        PA5
  #define SD_MISO_PIN                       PA6
  #define SD_MOSI_PIN                       PA7
  #define SD_DETECT_PIN                     PC15

#elif SD_CONNECTION_IS(CUSTOM_CABLE)
  #error "CUSTOM_CABLE is not a supported SDCARD_CONNECTION for this board"
#endif

#if ENABLED(BTT_MOTOR_EXPANSION)
  /**
   *         ------                  ------
   * M3DIAG |10  9 | M3RX     M3STP |10  9 | M3DIR
   * M2DIAG | 8  7 | M2RX     M2STP | 8  7 | M2DIR
   * M1DIAG   6  5 | M1RX     M1DIR   6  5 | M1STP
   *   M3EN | 4  3 | M2EN      M1EN | 4  3 | --
   *    GND | 2  1 | --         GND | 2  1 | --
   *        ------                   ------
   *         EXP1                     EXP2
   */

  // M1 on Driver Expansion Module
  #define E4_STEP_PIN                EXP2_05_PIN
  #define E4_DIR_PIN                 EXP2_06_PIN
  #define E4_ENABLE_PIN              EXP2_04_PIN
  #define E4_DIAG_PIN                EXP1_06_PIN
  #define E4_CS_PIN                  EXP1_05_PIN
  #if HAS_TMC_UART
    #define E4_SERIAL_TX_PIN         EXP1_05_PIN
    #define E4_SERIAL_RX_PIN    E4_SERIAL_TX_PIN
  #endif

  // M2 on Driver Expansion Module
  #define E5_STEP_PIN                EXP2_08_PIN
  #define E5_DIR_PIN                 EXP2_07_PIN
  #define E5_ENABLE_PIN              EXP1_03_PIN
  #define E5_DIAG_PIN                EXP1_08_PIN
  #define E5_CS_PIN                  EXP1_07_PIN
  #if HAS_TMC_UART
    #define E5_SERIAL_TX_PIN         EXP1_07_PIN
    #define E5_SERIAL_RX_PIN    E5_SERIAL_TX_PIN
  #endif

  // M3 on Driver Expansion Module
  #define E6_STEP_PIN                EXP2_10_PIN
  #define E6_DIR_PIN                 EXP2_09_PIN
  #define E6_ENABLE_PIN              EXP1_04_PIN
  #define E6_DIAG_PIN                EXP1_10_PIN
  #define E6_CS_PIN                  EXP1_09_PIN
  #if HAS_TMC_UART
    #define E6_SERIAL_TX_PIN         EXP1_09_PIN
    #define E6_SERIAL_RX_PIN    E6_SERIAL_TX_PIN
  #endif

#endif // BTT_MOTOR_EXPANSION

//
// LCDs and Controllers
//
#if IS_TFTGLCD_PANEL

  #if ENABLED(TFTGLCD_PANEL_SPI)
    #define TFTGLCD_CS               EXP2_08_PIN
  #endif

#elif HAS_WIRED_LCD

  #define BEEPER_PIN                 EXP1_10_PIN
  #define BTN_ENC                    EXP1_09_PIN

  #if ENABLED(CR10_STOCKDISPLAY)

    #define LCD_PINS_RS              EXP1_04_PIN

    #define BTN_EN1                  EXP1_08_PIN
    #define BTN_EN2                  EXP1_06_PIN

    #define LCD_PINS_ENABLE          EXP1_03_PIN
    #define LCD_PINS_D4              EXP1_05_PIN

  #else

    #define LCD_PINS_RS              EXP1_07_PIN

    #define BTN_EN1                  EXP2_08_PIN
    #define BTN_EN2                  EXP2_06_PIN

    #define LCD_PINS_ENABLE          EXP1_08_PIN
    #define LCD_PINS_D4              EXP1_06_PIN

    #if ENABLED(FYSETC_MINI_12864)
      #define DOGLCD_CS              EXP1_08_PIN
      #define DOGLCD_A0              EXP1_07_PIN
      //#define LCD_BACKLIGHT_PIN           -1
      #define LCD_RESET_PIN          EXP1_06_PIN  // Must be high or open for LCD to operate normally.
      #if EITHER(FYSETC_MINI_12864_1_2, FYSETC_MINI_12864_2_0)
        #ifndef RGB_LED_R_PIN
          #define RGB_LED_R_PIN      EXP1_05_PIN
        #endif
        #ifndef RGB_LED_G_PIN
          #define RGB_LED_G_PIN      EXP1_04_PIN
        #endif
        #ifndef RGB_LED_B_PIN
          #define RGB_LED_B_PIN      EXP1_03_PIN
        #endif
      #elif ENABLED(FYSETC_MINI_12864_2_1)
        #define NEOPIXEL_PIN         EXP1_05_PIN
      #endif
    #endif // !FYSETC_MINI_12864

    #if IS_ULTIPANEL
      #define LCD_PINS_D5            EXP1_05_PIN
      #define LCD_PINS_D6            EXP1_04_PIN
      #define LCD_PINS_D7            EXP1_03_PIN

      #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
        #define BTN_ENC_EN           LCD_PINS_D7  // Detect the presence of the encoder
      #endif

    #endif

  #endif
#endif  // HAS_WIRED_LCD

// Alter timing for graphical display
#if IS_U8GLIB_ST7920
  #define BOARD_ST7920_DELAY_1               120
  #define BOARD_ST7920_DELAY_2                80
  #define BOARD_ST7920_DELAY_3               580
#endif

#if HAS_SPI_TFT
  #define TFT_CS_PIN                 EXP2_07_PIN
  #define TFT_A0_PIN                 EXP2_04_PIN
  #define TFT_SCK_PIN                EXP2_09_PIN
  #define TFT_MISO_PIN               EXP2_10_PIN
  #define TFT_MOSI_PIN               EXP2_05_PIN

  #define TOUCH_INT_PIN              EXP1_04_PIN
  #define TOUCH_MISO_PIN             EXP1_05_PIN
  #define TOUCH_MOSI_PIN             EXP1_08_PIN
  #define TOUCH_SCK_PIN              EXP1_06_PIN
  #define TOUCH_CS_PIN               EXP1_07_PIN

  #define BTN_EN1                    EXP2_08_PIN
  #define BTN_EN2                    EXP2_06_PIN
  #define BTN_ENC                    EXP1_09_PIN
#endif

//
// NeoPixel LED
//
#ifndef NEOPIXEL_PIN
  #define NEOPIXEL_PIN                      PB0
#endif

//
// WIFI
//

/**
 *                      -------
 *            GND | 9  |       | 8 | 3.3V
 *  (ESP-CS) PB12 | 10 |       | 7 | PB15 (ESP-MOSI)
 *           3.3V | 11 |       | 6 | PB14 (ESP-MISO)
 * (ESP-IO0)  PD7 | 12 |       | 5 | PB13 (ESP-CLK)
 * (ESP-IO4) PD10 | 13 |       | 4 | --
 *             -- | 14 |       | 3 | PE15 (ESP-EN)
 *  (ESP-RX)  PD8 | 15 |       | 2 | --
 *  (ESP-TX)  PD9 | 16 |       | 1 | PE14 (ESP-RST)
 *                      -------
 *                       WIFI
 */
#define ESP_WIFI_MODULE_COM                    3  // Must also set either SERIAL_PORT or SERIAL_PORT_2 to this
#define ESP_WIFI_MODULE_BAUDRATE        BAUDRATE  // Must use same BAUDRATE as SERIAL_PORT & SERIAL_PORT_2
#define ESP_WIFI_MODULE_RESET_PIN           PG7
#define ESP_WIFI_MODULE_ENABLE_PIN          PG8
#define ESP_WIFI_MODULE_GPIO0_PIN           PD7
#define ESP_WIFI_MODULE_GPIO4_PIN           PD10