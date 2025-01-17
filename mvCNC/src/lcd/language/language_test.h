/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * TEST
 *
 * LCD Menu Messages
 * See also https://mvcncfw.org/docs/development/lcd_language.html
 */

// Select ONE of the following Mappers.
// They decide what to do with a symbol in the area of [0x80:0xFF]. They take a symbol of this language file and make them point
// into an array with 128 cells, where they'll find the place of the symbol of the font in use.
//
// a.)For ASCII coded Language_xx.h files like (en) there are no occurrences of symbols above 0x7F so no mapper is needed.
//   If such a symbol appears it is mapped directly into the font. This is the case for the language files we used until now, with all the STR_XX or
//   "\xxx" symbols. All Symbols are only one byte long.
// b.) For Unicoded Language_xx.h files (currently ru, de and kana_utf8 ) the non ASCII [0x00-0x7F] symbols are represented by more than one byte.
//   In the case of two bytes the first is pointing to a 'codepage' and the second to a place in the codepage. These codepages contain 64 symbols.
//   So two of them can be mapped. For most of the European languages the necessary symbols are contained in the pages C2 and C3. Cyrillic uses D0
//   and D1.
// c.) For katakana (one of the Japanese symbol sets) Unicode uses 3 bytes. Here the second byte also points to a codepage and byte 3 to the symbol.
//   I hope the pages E282 and E283 are sufficient to write katakana.
//   Kanji (an other Japanese symbol set) uses far more than two codepages. So currently I don't see a chance to map the Unicodes. Its not
//   impossible to have a close to direct mapping but will need giant conversion tables and fonts (we don't want to have in a embedded system).


// Select the better font for full graphic displays.
//#define DISPLAY_CHARSET_ISO10646_1
//#define DISPLAY_CHARSET_ISO10646_5
//#define DISPLAY_CHARSET_ISO10646_GREEK
//#define DISPLAY_CHARSET_ISO10646_KANA



// next 5 lines select variants in this file only
#define DISPLAYTEST
//#define WEST
//#define CYRIL
//#define KANA


// TESTSTRINGS

#define STRG_ASCII_2 _UxGT(" !\"#$%&'()*+,-./")
#define STRG_ASCII_3 _UxGT("0123456789:;<=>?")
#define STRG_ASCII_4 _UxGT("@ABCDEFGHIJKLMNO")
#define STRG_ASCII_5 _UxGT("PQRSTUVWXYZ[\\]^_")
#define STRG_ASCII_6 _UxGT("`abcdefghijklmno")
#define STRG_ASCII_7 _UxGT("pqrstuvwxyz{|}~")

#define STRG_C2_8 _UxGT("")
#define STRG_C2_9 _UxGT("")
#define STRG_C2_a _UxGT(" ¡¢£¤¥¦§¨©ª«¬­®¯")
#define STRG_C2_b _UxGT("°±²³´µ¶·¸¹º»¼½¾¿")
#define STRG_C3_8 _UxGT("ÈÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ")
#define STRG_C3_9 _UxGT("ÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß")
#define STRG_C3_a _UxGT("àáâãäåæçèéêëìíîï")
#define STRG_C3_b _UxGT("ðñòóôõö÷øùúûüýþÿ")

#define STRG_D0_8 _UxGT("ЀЁЂЃЄЅІЇЈЉЊЋЌЍЎЏ")
#define STRG_D0_9 _UxGT("АБВГДЕЖЗИЙКЛМНОП")
#define STRG_D0_a _UxGT("РСТУФХЦЧШЩЪЫЬЭЮЯ")
#define STRG_D0_b _UxGT("абвгдежзийклмноп")
#define STRG_D1_8 _UxGT("рстуфхцчшщъыьэюя")
#define STRG_D1_9 _UxGT("ѐёђѓєѕіїјљњћќѝўџ")
#define STRG_D1_a _UxGT("ѠѡѢѣѤѥѦѧѨѩѪѫѬѭѮѯ")
#define STRG_D1_b _UxGT("ѰѱѲѳѴѵѶѷѸѹѺѻѼѽѾѿ")

#define STRG_E382_8 _UxGT("よめもゃやゅゆょよらりるれろゎわ")
#define STRG_E382_9 _UxGT("ゐゑをんゔゕゖ゗゘゙゚゛ ゜ゝゞゟ")
#define STRG_E382_a _UxGT("゠ァアィイゥウェエォオカガキギク")
#define STRG_E382_b _UxGT("グケゲコゴサザシジスズセゼソゾタ")
#define STRG_E383_8 _UxGT("トチヂッツヅテデトドナニヌネノハ")
#define STRG_E383_9 _UxGT("バパヒビピフブプヘベペホボポマミ")
#define STRG_E383_a _UxGT("ムメモャヤュユョヨラリルレロヮワ")
#define STRG_E383_b _UxGT("ヰヱヲンヴヵヶヷヸヹヺ・ーヽヾヿ")

#define STRG_OKTAL_0 "\000\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017"
#define STRG_OKTAL_1 "\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037"
#define STRG_OKTAL_2 "\040\041\042\043\044\045\046\047\050\051\052\053\054\055\056\057"
#define STRG_OKTAL_3 "\060\061\062\063\064\065\066\067\070\071\072\073\074\075\076\077"
#define STRG_OKTAL_4 "\100\101\102\103\104\105\106\107\110\111\112\113\114\115\116\117"
#define STRG_OKTAL_5 "\120\121\122\123\124\125\126\127\130\131\132\133\134\135\136\137"
#define STRG_OKTAL_6 "\140\141\142\143\144\145\146\147\150\151\152\153\154\155\156\157"
#define STRG_OKTAL_7 "\160\161\162\163\164\165\166\167\170\171\172\173\174\175\176\177"
#define STRG_OKTAL_8 "\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217"
#define STRG_OKTAL_9 "\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237"
#define STRG_OKTAL_a "\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257"
#define STRG_OKTAL_b "\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277"
#define STRG_OKTAL_c "\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317"
#define STRG_OKTAL_d "\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337"
#define STRG_OKTAL_e "\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357"
#define STRG_OKTAL_f "\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377"

namespace Language_test {
  using namespace Language_en; // Inherit undefined strings from English

  constexpr uint8_t CHARSIZE                  = 1;

  #if ENABLED(DISPLAYTEST)
    LSTR WELCOME_MSG                        = _UxGT("Language TEST");

    LSTR MSG_INFO_SCREEN                    = _UxGT("Display test");
    LSTR MSG_PREPARE                        = STRG_OKTAL_b;
    LSTR MSG_CONTROL                        = STRG_OKTAL_c;
  #endif

  #if ENABLED(WEST)
    LSTR WELCOME_MSG                        = _UxGT("Language TEST");

    LSTR MSG_INFO_SCREEN                    = _UxGT("\001\002\003\004\005\006\007\010\011");
    LSTR MSG_PREPARE                        = _UxGT("UTF8");
    LSTR MSG_CONTROL                        = _UxGT("ASCII");

    LSTR MSG_MAIN                           = _UxGT("..");
    LSTR MSG_DISABLE_STEPPERS               = STRG_C2_8;
    LSTR MSG_AUTO_HOME                      = STRG_C2_9;
    LSTR MSG_SET_HOME_OFFSETS               = STRG_C2_a;
    LSTR MSG_PREHEAT_1                      = STRG_C2_b;
    LSTR MSG_PREHEAT_2                      = STRG_C3_8;
    LSTR MSG_COOLDOWN                       = STRG_C3_9;
    LSTR MSG_SWITCH_PS_OFF                  = STRG_C3_a;
    LSTR MSG_MOVE_AXIS                      = STRG_C3_b;

    LSTR MSG_MAIN                           = STRG_OKTAL_2;
    LSTR MSG_TEMPERATURE                    = STRG_OKTAL_3;
    LSTR MSG_MOTION                         = STRG_OKTAL_4;
    LSTR MSG_FILAMENT                       = STRG_OKTAL_5;
    LSTR MSG_CONTRAST                       = STRG_OKTAL_6;
    LSTR MSG_RESTORE_DEFAULTS               = STRG_OKTAL_7;

    LSTR MSG_NOZZLE                         = STRG_OKTAL_8;
    LSTR MSG_NOZZLE_N                       = STRG_OKTAL_8 " ~";
    LSTR MSG_FAN_SPEED                      = STRG_OKTAL_9;
    LSTR MSG_FAN_SPEED_N                    = STRG_OKTAL_9;
    LSTR MSG_AUTOTEMP                       = STRG_OKTAL_a;
    LSTR MSG_MIN                            = STRG_OKTAL_b;
    LSTR MSG_MAX                            = STRG_OKTAL_c;
    LSTR MSG_FACTOR                         = STRG_OKTAL_d;
    LSTR MSG_PID_P                          = STRG_OKTAL_e;
    LSTR MSG_PID_I                          = STRG_OKTAL_f;

  #endif

  #if ENABLED(CYRIL)
    LSTR WELCOME_MSG                        = _UxGT("Language TEST");

    LSTR MSG_INFO_SCREEN                    = _UxGT("\001\002\003\004\005\006\007\010\011");
    LSTR MSG_PREPARE                        = _UxGT("UTF8");
    LSTR MSG_CONTROL                        = _UxGT("ASCII");

    LSTR MSG_MAIN                           = _UxGT("..");
    LSTR MSG_DISABLE_STEPPERS               = STRG_D0_8;
    LSTR MSG_AUTO_HOME                      = STRG_D0_9;
    LSTR MSG_SET_HOME_OFFSETS               = STRG_D0_a;
    LSTR MSG_PREHEAT_1                      = STRG_D0_b;
    LSTR MSG_PREHEAT_2                      = STRG_D1_8;
    LSTR MSG_COOLDOWN                       = STRG_D1_9;
    LSTR MSG_SWITCH_PS_OFF                  = STRG_D1_a;
    LSTR MSG_MOVE_AXIS                      = STRG_D1_b;

    LSTR MSG_MAIN                           = STRG_OKTAL_2;
    LSTR MSG_TEMPERATURE                    = STRG_OKTAL_3;
    LSTR MSG_MOTION                         = STRG_OKTAL_4;
    LSTR MSG_FILAMENT                       = STRG_OKTAL_5;
    LSTR MSG_CONTRAST                       = STRG_OKTAL_6;
    LSTR MSG_RESTORE_DEFAULTS               = STRG_OKTAL_7;

    LSTR MSG_NOZZLE                         = STRG_OKTAL_8;
    LSTR MSG_NOZZLE_N                       = STRG_OKTAL_8 " ~";
    LSTR MSG_FAN_SPEED_N                    = STRG_OKTAL_9;
    LSTR MSG_AUTOTEMP                       = STRG_OKTAL_a;
    LSTR MSG_MIN                            = STRG_OKTAL_b;
    LSTR MSG_MAX                            = STRG_OKTAL_c;
    LSTR MSG_FACTOR                         = STRG_OKTAL_d;
    LSTR MSG_PID_P                          = STRG_OKTAL_e;
    LSTR MSG_PID_I                          = STRG_OKTAL_f;

  #endif

  #if ENABLED(KANA)
    LSTR WELCOME_MSG                        = _UxGT("Language TEST");

    LSTR MSG_INFO_SCREEN                    = _UxGT("\001\002\003\004\005\006\007\010\011");
    LSTR MSG_PREPARE                        = _UxGT("UTF8");
    LSTR MSG_CONTROL                        = _UxGT("ASCII");

    LSTR MSG_MAIN                           = _UxGT("..");
    LSTR MSG_DISABLE_STEPPERS               = STRG_E382_8;
    LSTR MSG_AUTO_HOME                      = STRG_E382_9;
    LSTR MSG_SET_HOME_OFFSETS               = STRG_E382_a;
    LSTR MSG_PREHEAT_1                      = STRG_E382_b;
    LSTR MSG_PREHEAT_2                      = STRG_E383_8;
    LSTR MSG_COOLDOWN                       = STRG_E383_9;
    LSTR MSG_SWITCH_PS_OFF                  = STRG_E383_a;
    LSTR MSG_MOVE_AXIS                      = STRG_E383_b;

    LSTR MSG_MAIN                           = STRG_OKTAL_2;
    LSTR MSG_TEMPERATURE                    = STRG_OKTAL_3;
    LSTR MSG_MOTION                         = STRG_OKTAL_4;
    LSTR MSG_FILAMENT                       = STRG_OKTAL_5;
    LSTR MSG_CONTRAST                       = STRG_OKTAL_6;
    LSTR MSG_RESTORE_DEFAULTS               = STRG_OKTAL_7;

    LSTR MSG_NOZZLE                         = STRG_OKTAL_8;
    LSTR MSG_NOZZLE_N                       = STRG_OKTAL_8 " ~";
    LSTR MSG_FAN_SPEED_N                    = STRG_OKTAL_9;
    LSTR MSG_AUTOTEMP                       = STRG_OKTAL_a;
    LSTR MSG_MIN                            = STRG_OKTAL_b;
    LSTR MSG_MAX                            = STRG_OKTAL_c;
    LSTR MSG_FACTOR                         = STRG_OKTAL_d;
    LSTR MSG_PID_P                          = STRG_OKTAL_e;
    LSTR MSG_PID_I                          = STRG_OKTAL_f;
  #endif
}
