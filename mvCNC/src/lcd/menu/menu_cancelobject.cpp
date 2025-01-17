/**
 * Modern Vintage CNC Firmware
*/

//
// Cancel Object Menu
//

#include "../../inc/mvCNCConfigPre.h"

#if BOTH(HAS_MVCNCUI_MENU, CANCEL_OBJECTS)

#include "menu_item.h"
#include "menu_addon.h"

#include "../../feature/cancel_object.h"

static void lcd_cancel_object_confirm() {
  const int8_t v = MenuItemBase::itemIndex;
  const char item_num[] = {
    ' ',
    char((v > 9) ? '0' + (v / 10) : ' '),
    char('0' + (v % 10)),
    '\0'
  };
  MenuItem_confirm::confirm_screen(
    []{
      cancelable.cancel_object(MenuItemBase::itemIndex);
      ui.completion_feedback();
      ui.goto_previous_screen();
    },
    nullptr,
    GET_TEXT(MSG_CANCEL_OBJECT), item_num, PSTR("?")
  );
}

void menu_cancelobject() {
  const int8_t ao = cancelable.active_object;

  START_MENU();
  BACK_ITEM(MSG_MAIN);

  // Draw cancelable items in a loop
  for (int8_t i = -1; i < cancelable.object_count; i++) {
    if (i == ao) continue;                                          // Active is drawn on -1 index
    const int8_t j = i < 0 ? ao : i;                                // Active or index item
    if (!cancelable.is_canceled(j)) {                               // Not canceled already?
      SUBMENU_N(j, MSG_CANCEL_OBJECT_N, lcd_cancel_object_confirm); // Offer the option.
      if (i < 0) SKIP_ITEM();                                       // Extra line after active
    }
  }

  END_MENU();
}

#endif // HAS_MVCNCUI_MENU && CANCEL_OBJECTS
