/**
 * Modern Vintage CNC Firmware
*/

#include "../../inc/mvCNCConfig.h"

#if HAS_MESH

#include "../gcode.h"
#include "../../mvCNCCore.h" // for IsRunning()
#include "../../module/motion.h"
#include "../../module/probe.h" // for probe.offset
#include "../../feature/bedlevel/bedlevel.h"

/**
 * G42: Move X & Y axes to mesh coordinates (I & J)
 */
void GcodeSuite::G42() {
  if (MOTION_CONDITIONS) {
    const bool hasI = parser.seenval('I');
    const int8_t ix = hasI ? parser.value_int() : 0;
    const bool hasJ = parser.seenval('J');
    const int8_t iy = hasJ ? parser.value_int() : 0;

    if ((hasI && !WITHIN(ix, 0, GRID_MAX_POINTS_X - 1)) || (hasJ && !WITHIN(iy, 0, GRID_MAX_POINTS_Y - 1))) {
      SERIAL_ECHOLNPGM(STR_ERR_MESH_XY);
      return;
    }

    // Move to current_position, as modified by I, J, P parameters
    destination = current_position;

    if (hasI) destination.x = _GET_MESH_X(ix);
    if (hasJ) destination.y = _GET_MESH_Y(iy);

    #if HAS_PROBE_XY_OFFSET
      if (parser.boolval('P')) {
        if (hasI) destination.x -= probe.offset_xy.x;
        if (hasJ) destination.y -= probe.offset_xy.y;
      }
    #endif

    const feedRate_t fval = parser.linearval('F'),
                     fr_mm_s = MMM_TO_MMS(fval > 0 ? fval : 0.0f);

    // SCARA kinematic has "safe" XY raw moves
    #if IS_SCARA
      prepare_internal_fast_move_to_destination(fr_mm_s);
    #else
      prepare_internal_move_to_destination(fr_mm_s);
    #endif
  }
}

#endif // HAS_MESH
