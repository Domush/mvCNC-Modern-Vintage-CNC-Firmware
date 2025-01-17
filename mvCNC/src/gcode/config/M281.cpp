/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if ENABLED(EDITABLE_SERVO_ANGLES)

#include "../gcode.h"
#include "../../module/servo.h"

/**
 * M281 - Edit / Report Servo Angles
 *
 *  P<index> - Servo to update
 *  L<angle> - Deploy Angle
 *  U<angle> - Stowed Angle
 */
void GcodeSuite::M281() {
  if (!parser.seen_any()) return M281_report();

  if (!parser.seenval('P')) return;

  const int servo_index = parser.value_int();
  if (WITHIN(servo_index, 0, NUM_SERVOS - 1)) {
    #if ENABLED(BLTOUCH)
      if (servo_index == Z_PROBE_SERVO_NR) {
        SERIAL_ERROR_MSG("BLTouch angles can't be changed.");
        return;
      }
    #endif
    if (parser.seen('L')) servo_angles[servo_index][0] = parser.value_int();
    if (parser.seen('U')) servo_angles[servo_index][1] = parser.value_int();
  }
  else
    SERIAL_ERROR_MSG("Servo ", servo_index, " out of range");
}

void GcodeSuite::M281_report(const bool forReplay/*=true*/) {
  report_heading_etc(forReplay, F(STR_SERVO_ANGLES));
  LOOP_L_N(i, NUM_SERVOS) {
    switch (i) {
      default: break;
      #if ENABLED(SWITCHING_EXTRUDER)
        case SWITCHING_EXTRUDER_SERVO_NR:
        #if EXTRUDERS > 3
          case SWITCHING_EXTRUDER_E23_SERVO_NR:
        #endif
      #elif ENABLED(SWITCHING_NOZZLE)
        case SWITCHING_NOZZLE_SERVO_NR:
      #elif ENABLED(BLTOUCH) || (HAS_Z_SERVO_PROBE && defined(Z_SERVO_ANGLES))
        case Z_PROBE_SERVO_NR:
      #endif
          report_echo_start(forReplay);
          SERIAL_ECHOLNPGM("  M281 P", i, " L", servo_angles[i][0], " U", servo_angles[i][1]);
    }
  }
}

#endif // EDITABLE_SERVO_ANGLES
