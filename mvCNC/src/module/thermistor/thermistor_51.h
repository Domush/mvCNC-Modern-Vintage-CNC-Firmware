/**
 * Modern Vintage CNC Firmware
*/
#pragma once

// R25 = 100 kOhm, beta25 = 4092 K, 1 kOhm pull-up,
// 100k EPCOS (WITH 1kohm RESISTOR FOR PULLUP, R9 ON SANGUINOLOLU! NOT FOR 4.7kohm PULLUP! THIS IS NOT NORMAL!)
// Verified by linagee.
// Calculated using 1kohm pullup, voltage divider math, and manufacturer provided temp/resistance
// Advantage: Twice the resolution and better linearity from 150C to 200C
constexpr temp_entry_t temptable_51[] PROGMEM = {
  { OV(   1), 350 },
  { OV( 190), 250 }, // top rating 250C
  { OV( 203), 245 },
  { OV( 217), 240 },
  { OV( 232), 235 },
  { OV( 248), 230 },
  { OV( 265), 225 },
  { OV( 283), 220 },
  { OV( 302), 215 },
  { OV( 322), 210 },
  { OV( 344), 205 },
  { OV( 366), 200 },
  { OV( 390), 195 },
  { OV( 415), 190 },
  { OV( 440), 185 },
  { OV( 467), 180 },
  { OV( 494), 175 },
  { OV( 522), 170 },
  { OV( 551), 165 },
  { OV( 580), 160 },
  { OV( 609), 155 },
  { OV( 638), 150 },
  { OV( 666), 145 },
  { OV( 695), 140 },
  { OV( 722), 135 },
  { OV( 749), 130 },
  { OV( 775), 125 },
  { OV( 800), 120 },
  { OV( 823), 115 },
  { OV( 845), 110 },
  { OV( 865), 105 },
  { OV( 884), 100 },
  { OV( 901),  95 },
  { OV( 917),  90 },
  { OV( 932),  85 },
  { OV( 944),  80 },
  { OV( 956),  75 },
  { OV( 966),  70 },
  { OV( 975),  65 },
  { OV( 982),  60 },
  { OV( 989),  55 },
  { OV( 995),  50 },
  { OV(1000),  45 },
  { OV(1004),  40 },
  { OV(1007),  35 },
  { OV(1010),  30 },
  { OV(1013),  25 },
  { OV(1015),  20 },
  { OV(1017),  15 },
  { OV(1018),  10 },
  { OV(1019),   5 },
  { OV(1020),   0 },
  { OV(1021),  -5 }
};
