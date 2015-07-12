/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* 
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"

extern const uint16_t fn_actions[] = {};
//extern const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];


/*
 * ,---------------------------------------------------------------------------------------------------------------------------------------------.
 * |  ESC|  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | F13 |  F14 |  |STRYK| KOPI|FLYTT|     | FUNC|SKRIV|HJELP|SLUTT|
 * | 0-0 | 1-0 | 2-0 | 3-0 | 4-0 | 5-0 | 6-0 | 7-0 | 8-0 | 9-0 | A-0 | F-0 | E-0 | D-0 |  C-0 |  | B-0 | B-5 | E-5 | B-7 | F-5 | A-5 | 7-5 | 6-5 |
 * | A10 | A11 | A12 | A13 | A14 | A15 | A16 | A17 | A18 | A19 | A1A | A1B | A1C | A1D |  A1E |  | A20 | A21 | A22 | A23 | A24 | A25 | A26 | A27 |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 *                                                                                               | TAB | (...| aaa |     | P1  | P2  | P3  | P4  |
 *                                                                                               | C-5 | 9-5 | 1-5 | 0-5 | 4-5 | 3-5 | 2-5 | 5-5 |
 *                                                                                               | B20 | B21 | B22 | B23 | B24 | B25 | B26 | B27 |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * | * Caps |   1 |   2 |   3 |   4 |   5 |   6 |   7 |   8 |   9 |   0 |   + |   @ |???| BCSP|  | < < | JUST| > > |     | P5  | P6  | P7  | P8  |
 * |   #-1  | 0-1 | 1-1 | 2-1 | 3-1 | 4-1 | 5-1 | 6-1 | 7-1 | 8-1 | 9-1 | A-1 | F-1 |E-1| D-1 |  | C-1 | 9-7 | D-5 | E-7 | E-6 | 9-6 | B-6 | C-6 |
 * |   C10  | C11 | C12 | C13 | C14 | C15 | C16 | C17 | C18 | C19 | C1A | C1B | C1C |C1D| C1E |  | C20 | C21 | C22 | C23 | C24 | C25 | C26 | C27 |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * | Eksp| CTRL|   Q |   W |   E |   R |   T |   Y |   U |   I |   O |   P |   Å |  ^ |  LF   |  | <== |ANGRE| ==> |     |  7  |  8  |  9  |SPACE|
 * | D-2 | #-2 | 0-2 | 1-2 | 2-2 | 3-2 | 4-2 | 5-2 | 6-2 | 7-2 | 8-2 | 9-2 | A-2 | F-2|  E-2  |  | C-2 | 8-7 | 8-5 | B-2 | 8-6 | D-6 | F-6 | 7-6 |
 * | D10 | D11 | D12 | D13 | D14 | D15 | D16 | D17 | D18 | D19 | D1A | D1B | D1C | D1D|  D1E  |  | D20 | D21 | D22 | D23 | D24 | D25 | D26 | D27 |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * |  ^^ |* LOCK|   A |   S |   D |   F |   G |   H |   J |   K |   L |   Ø |   Æ |   * |     |  | <=  | UP  |  => |     |  4  |  5  |  6  |  -  |
 * | E-3 | #-3  | 0-3 | 1-3 | 2-3 | 3-3 | 4-3 | 5-3 | 6-3 | 7-3 | 8-3 | 9-3 | A-3 | F-3 |     |  | D-3 | C-3 | 7-7 | F-7 | 6-6 | A-6 | 2-6 | 0-6 |
 * | E10 | E11  | E12 | E13 | E14 | E15 | E16 | E17 | E18 | E19 | E1A | E1B | E1C | E1D |  E  |  | E20 | E21 | E22 | E23 | E24 | E25 | E26 | E27 |
 * |------------------------------------------------------------------------------------|  N  |  |-----|-----|-----|     |-----|-----|-----|-----|
 * |    Lshift| <  |   Z |   X |   C |   V |   B |   N |   M |   , |   . |   - | Rshift |  T  |  |LEFT |^HOME|RIGHT|     |  1  |  2  |  3  |     |
 * |    #-4   | 0-4| 1-4 | 2-4 | 3-4 | 4-4 | 5-4 | 6-4 | 7-4 | 8-4 | 9-4 | A-4 |  #-4   | F-4 |  | E-4 | D-4 | A-7 | 5-6 | 4-6 | 3-6 | 1-6 |     |
 * |    F10   | F11| F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F1A | F1B |  F1C   | F1D |  | F20 | F21 | F22 | F23 | F24 | F25 | F26 |  E  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|  N  |
 *                             |          SPACE                          |                       |HOME | DOWN| END |     |     0     |  ,  |  T  |
 *                             |           C-4                           |                       | 6-7 | 5-7 | 4-7 | 3-7 |    B-4    | B-1 | B-3 |
 *                             |           G10                           |                       | G20 | G21 | G22 | G23 |    G24    | G26 | G27 |
 *                             `-----------------------------------------'                       `-----------------'     `-----------------------'
 *
 * Matrix: 17x8
 * R C|       0 |       1 |       2 |       3 |       4 |       5 |       6 |       7
 * ---+---------+---------+---------+---------+---------+---------+---------+---------
 *  0 |   A10   |   C11   |   D12   |   E12   |   F11   |   B23   |   E27   |        
 *  1 |   A11   |   C12   |   D13   |   E13   |   F12   |   B22   |   F26   |        
 *  2 |   A12   |   C13   |   D14   |   E14   |   F13   |   B26   |   E26   |        
 *  3 |   A13   |   C14   |   D15   |   E15   |   F14   |   B25   |   F25   |   G23 
 *  4 |   A14   |   C15   |   D16   |   E16   |   F15   |   B24   |   F24   |   G22  
 *  5 |   A15   |   C16   |   D17   |   E17   |   F16   |   B27   |   F23   |   G21
 *  6 |   A16   |   C17   |   D18   |   E18   |   F17   |   A27   |   E24   |   G20
 *  7 |   A17   |   C18   |   D19   |   E19   |   F18   |   A26   |   D27   |   E22
 *  8 |   A18   |   C19   |   D1A   |   E1A   |   F19   |   D22   |   D24   |   D21
 *  9 |   A19   |   C1A   |   D1B   |   E1B   |   F1A   |   B21   |   C25   |   C21     
 *  A |   A1A   |   C18   |   D1C   |   E1C   |   F1B   |   A25   |   E25   |   F22
 *  B |   A20   |   G26   |   D23   |   G27   |   G24   |   A21   |   C26   |   A23
 *  C |   A1E   |   C20   |   D20   |   E21   |   G10   |   B20   |   C27   |  
 *  D |   A1D   |   C1E   |   D10   |   E20   |   F21   |   C22   |   D25   |  
 *  E |   A1C   |   C1D   |   D1E   |   E10   |   F20   |   A22   |   C24   |   C23
 *  F |   A1B   |   C1C   |   D1D   |   E1D   |   F1D   |   A24   |   D26   |   E23
 *  # |         |   C10   |   D11   |   E11   | F10/F1C |         |         |  
 



 */

 // REWRITE NEEDED
#define KEYMAP( \
    KA10, KA11, KA12, KA13, KA14, KA15, KA16, KA17, KA18, KA19, KA1A, KA1B, KA1C, KA1D, KA1E,       KA20, KA21, KA22, KA23, KA24, KA25, KA26, KA27, \
                                                                                                    KB20, KB21, KB22, KB23, KB24, KB25, KB26, KB27, \
    KC10, KC11, KC12, KC13, KC14, KC15, KC16, KC17, KC18, KC19, KC1A, KC1B, KC1C, KC1D, KC1E,       KC20, KC21, KC22, KC23, KC24, KC25, KC26, KC27, \
    KD10, KD11, KD12, KD13, KD14, KD15, KD16, KD17, KD18, KD19, KD1A, KD1B, KD1C, KD1D, KD1E,       KD20, KD21, KD22, KD23, KD24, KD25, KD26, KD27, \
    KE10, KE11, KE12, KE13, KE14, KE15, KE16, KE17, KE18, KE19, KE1A, KE1B, KE1C, KE1D,             KE20, KE21, KE22, KE23, KE24, KE25, KE26, KE27, \
    KF10, KF11, KF12, KF13, KF14, KF15, KF16, KF17, KF18, KF19, KF1A, KF1B,             KF1D,       KF20, KF21, KF22, KF23, KF24, KF25, KF26,       \
                                      KG10,                                                         KG20, KG21, KG22, KG23, KG24, KG25, KG26, KG27  \
    ) \
{ /*              0   ,      1          2          3          4          5          6          7   /*
  /* 0 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 1 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 2 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 3 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 4 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 5 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 6 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 7 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 8 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* 9 */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* A */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* B */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* C */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* D */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* E */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* F */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }, \
  /* # */  { KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1    }  \
}


