/**
 * Modern Vintage CNC Firmware
*/

#include "../../../inc/mvCNCConfigPre.h"

#if BOTH(HAS_TFT_LVGL_UI, HAS_BED_PROBE)

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../module/probe.h"
#include "../../../inc/mvCNCConfig.h"

extern lv_group_t *g;
static lv_obj_t *scr;

enum {
  ID_OFFSET_RETURN = 1,
  ID_OFFSET_X,
  ID_OFFSET_Y,
  ID_OFFSET_Z
};

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  switch (obj->mks_obj_id) {
    case ID_OFFSET_RETURN:
      lv_clear_auto_level_offset_settings();
      draw_return_ui();
      break;
    case ID_OFFSET_X:
      value = x_offset;
      lv_clear_auto_level_offset_settings();
      lv_draw_number_key();
      break;
    case ID_OFFSET_Y:
      value = y_offset;
      lv_clear_auto_level_offset_settings();
      lv_draw_number_key();
      break;
    case ID_OFFSET_Z:
      value = z_offset;
      lv_clear_auto_level_offset_settings();
      lv_draw_number_key();
      break;
  }
}

void lv_draw_auto_level_offset_settings() {
  scr = lv_screen_create(NOZZLE_PROBE_OFFSET_UI, machine_menu.OffsetConfTitle);

  dtostrf(TERN0(HAS_PROBE_XY_OFFSET, probe.offset.x), 1, 1, public_buf_l);
  lv_screen_menu_item_1_edit(scr, machine_menu.Xoffset, PARA_UI_POS_X, PARA_UI_POS_Y, event_handler, ID_OFFSET_X, 0, public_buf_l);

  dtostrf(TERN0(HAS_PROBE_XY_OFFSET, probe.offset.y), 1, 1, public_buf_l);
  lv_screen_menu_item_1_edit(scr, machine_menu.Yoffset, PARA_UI_POS_X, PARA_UI_POS_Y * 2, event_handler, ID_OFFSET_Y, 1, public_buf_l);

  dtostrf(TERN0(HAS_PROBE_XY_OFFSET, probe.offset.z), 1, 1, public_buf_l);
  lv_screen_menu_item_1_edit(scr, machine_menu.Zoffset, PARA_UI_POS_X, PARA_UI_POS_Y * 3, event_handler, ID_OFFSET_Z, 2, public_buf_l);

  lv_big_button_create(scr, "F:/bmp_back70x40.bin", common_menu.text_back, PARA_UI_BACK_POS_X, PARA_UI_BACK_POS_Y, event_handler, ID_OFFSET_RETURN, true);
}

void lv_clear_auto_level_offset_settings() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI && HAS_BED_PROBE
