/**
 * Modern Vintage CNC Firmware
*/

#ifdef __MK20DX256__

/**
 * HAL PersistentStore for Teensy 3.2 (MK20DX256)
 */

#include "../../inc/mvCNCConfig.h"

#if USE_WIRED_EEPROM

#include "../shared/eeprom_api.h"
#include <avr/eeprom.h>

#ifndef MVCNC_EEPROM_SIZE
#define MVCNC_EEPROM_SIZE size_t(E2END + 1)
#endif
size_t PersistentStore::capacity() { return MVCNC_EEPROM_SIZE; }

bool PersistentStore::access_start()  { return true; }
bool PersistentStore::access_finish() { return true; }

bool PersistentStore::write_data(int &pos, const uint8_t *value, size_t size, uint16_t *crc) {
  uint16_t written = 0;
  while (size--) {
    uint8_t * const p = (uint8_t * const)pos;
    uint8_t v = *value;
    if (v != eeprom_read_byte(p)) { // EEPROM has only ~100,000 write cycles, so only write bytes that have changed!
      eeprom_write_byte(p, v);
      if (++written & 0x7F) delay(2); else safe_delay(2); // Avoid triggering watchdog during long EEPROM writes
      if (eeprom_read_byte(p) != v) {
        SERIAL_ECHO_MSG(STR_ERR_EEPROM_WRITE);
        return true;
      }
    }
    crc16(crc, &v, 1);
    pos++;
    value++;
  }
  return false;
}

bool PersistentStore::read_data(int &pos, uint8_t *value, size_t size, uint16_t *crc, const bool writing/*=true*/) {
  do {
    uint8_t c = eeprom_read_byte((uint8_t*)pos);
    if (writing) *value = c;
    crc16(crc, &c, 1);
    pos++;
    value++;
  } while (--size);
  return false;
}

#endif // USE_WIRED_EEPROM
#endif // __MK20DX256__