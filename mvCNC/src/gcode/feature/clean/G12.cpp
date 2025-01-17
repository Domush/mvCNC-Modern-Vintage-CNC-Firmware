/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfig.h"

#if ENABLED(NOZZLE_CLEAN_FEATURE)

#include "../../../libs/nozzle.h"

#include "../../gcode.h"
#include "../../parser.h"
#include "../../../module/motion.h"

#if HAS_LEVELING
  #include "../../../module/planner.h"
  #include "../../../feature/bedlevel/bedlevel.h"
#endif

/**
 * G12: Clean the nozzle
 *
 *  E<bool>          : 0=Never or 1=Always apply the "software endstop" limits
 *  P0 S<strokes>    : Stroke cleaning with S strokes
 *  P1 Sn T<objects> : Zigzag cleaning with S repeats and T zigzags
 *  P2 Sn R<radius>  : Circle cleaning with S repeats and R radius
 *  X, Y, Z          : Specify axes to move during cleaning. Default: ALL.
 */
void GcodeSuite::G12() {
  // Don't allow nozzle cleaning without homing first
  if (homing_needed_error()) return;

  #ifdef WIPE_SEQUENCE_COMMANDS
    if (!parser.seen_any()) {
      process_subcommands_now(F(WIPE_SEQUENCE_COMMANDS));
      return;
    }
  #endif

  const uint8_t pattern = parser.ushortval('P', 0),
                strokes = parser.ushortval('S', NOZZLE_CLEAN_STROKES),
                objects = parser.ushortval('T', NOZZLE_CLEAN_TRIANGLES);
  const float radius = parser.linearval('R', NOZZLE_CLEAN_CIRCLE_RADIUS);

  const bool seenxyz = parser.seen("XYZ");
  const uint8_t cleans =  (!seenxyz || parser.boolval('X') ? _BV(X_AXIS) : 0)
                        | (!seenxyz || parser.boolval('Y') ? _BV(Y_AXIS) : 0)
                        | TERN(NOZZLE_CLEAN_NO_Z, 0, (!seenxyz || parser.boolval('Z') ? _BV(Z_AXIS) : 0))
                      ;

  #if HAS_LEVELING
    // Disable bed leveling if cleaning Z
    TEMPORARY_BED_LEVELING_STATE(!TEST(cleans, Z_AXIS) && planner.leveling_active);
  #endif

  SET_SOFT_ENDSTOP_LOOSE(!parser.boolval('E'));

  nozzle.clean(pattern, strokes, radius, objects, cleans);

  SET_SOFT_ENDSTOP_LOOSE(false);
}

#endif // NOZZLE_CLEAN_FEATURE
