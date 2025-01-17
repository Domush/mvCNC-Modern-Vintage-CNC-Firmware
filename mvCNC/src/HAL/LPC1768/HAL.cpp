/**
 * Modern Vintage CNC Firmware
*/
#ifdef TARGET_LPC1768

#include "../../inc/mvCNCConfig.h"
#include "../shared/Delay.h"
#include "../../../gcode/parser.h"

#if ENABLED(USE_WATCHDOG)
  #include "watchdog.h"
#endif

DefaultSerial1 USBSerial(false, UsbSerial);

uint32_t HAL_adc_reading = 0;

// U8glib required functions
extern "C" {
  void u8g_xMicroDelay(uint16_t val) { DELAY_US(val); }
  void u8g_MicroDelay()              { u8g_xMicroDelay(1); }
  void u8g_10MicroDelay()            { u8g_xMicroDelay(10); }
  void u8g_Delay(uint16_t val)       { delay(val); }
}

//************************//

// return free heap space
int freeMemory() {
  char stack_end;
  void *heap_start = malloc(sizeof(uint32_t));
  if (heap_start == 0) return 0;

  uint32_t result = (uint32_t)&stack_end - (uint32_t)heap_start;
  free(heap_start);
  return result;
}

// scan command line for code
//   return index into pin map array if found and the pin is valid.
//   return dval if not found or not a valid pin.
int16_t PARSED_PIN_INDEX(const char code, const int16_t dval) {
  const uint16_t val = (uint16_t)parser.intval(code, -1), port = val / 100, pin = val % 100;
  const  int16_t ind = (port < ((NUM_DIGITAL_PINS) >> 5) && pin < 32) ? ((port << 5) | pin) : -2;
  return ind > -1 ? ind : dval;
}

void flashFirmware(const int16_t) {
  delay(500);          // Give OS time to disconnect
  USB_Connect(false);  // USB clear connection
  delay(1000);         // Give OS time to notice
  HAL_reboot();
}

void HAL_clear_reset_source(void) {
  TERN_(USE_WATCHDOG, watchdog_clear_timeout_flag());
}

uint8_t HAL_get_reset_source(void) {
  #if ENABLED(USE_WATCHDOG)
    if (watchdog_timed_out()) return RST_WATCHDOG;
  #endif
  return RST_POWER_ON;
}

void HAL_reboot() { NVIC_SystemReset(); }

#endif // TARGET_LPC1768
