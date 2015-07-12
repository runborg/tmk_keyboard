/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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
#include "keymap_common.h"


/*
 * ,---------------------------------------------------------------------------------------------------------------------------------------------.
 * |  ESC|  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | F13 |  F14 |  |STRYK| KOPI|FLYTT|     | FUNC|SKRIV|HJELP|SLUTT|
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 *                                                                                               | TAB | (...| aaa |     | P1  | P2  | P3  | P4  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * | * Caps |   1 |   2 |   3 |   4 |   5 |   6 |   7 |   8 |   9 |   0 |   + |   @ |???| BCSP|  | < < | JUST| > > |     | P5  | P6  | P7  | P8  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * | Eksp| CTRL|   Q |   W |   E |   R |   T |   Y |   U |   I |   O |   P |   Å |  ^ |  LF   |  | <== |ANGRE| ==> |     |  7  |  8  |  9  |SPACE|
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * |  ^^ |* LOCK|   A |   S |   D |   F |   G |   H |   J |   K |   L |   Ø |   Æ |   * |  E  |  | <=  | UP  |  => |     |  4  |  5  |  6  |  -  |
 * |------------------------------------------------------------------------------------|  N  |  |-----|-----|-----|     |-----|-----|-----|-----|
 * |    Lshift| <  |   Z |   X |   C |   V |   B |   N |   M |   , |   . |   - | Rshift |  T  |  |LEFT |^HOME|RIGHT|     |  1  |  2  |  3  |  E  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|  N  |
 *                             |          SPACE                          |                       |HOME | DOWN| END |     |     0     |  ,  |  T  |
 *                             `-----------------------------------------'                       `-----------------'     `-----------------------'
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer */
    [0] = KEYMAP( \
        ESC , F1  , F2  , F3  , F4  , F5  , F6  , F7  , F8  , F9  , F10 , F11 , F12 , NO  , NO  ,       NO  , NO  , NO  , NO  , NO  , NO  , NO  , FN1 , \
                                                                                                        NO  , NO  , NO  , NO  , NO  , NO  , NO  , NO  , \
        CAPS,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, NO  , NO  , BSPC, BSPC,       NO  , NO  , NO  , NO  , FN1 , PEQL, PSLS, PAST, \
        LGUI ,LCTRL,    Q,    W,    E,    R,    T,    Y,    I,    O,    P, NO  , NO  , NO  , ENT ,      NO  , NO  , NO  , NO  , P7  , P8  , P9  , PPLS, \
        LALT, SLCK,    A,    S,    D,    F,    G,    H,    J,    K,    L, NO  , NO  , PAST,             NO  , UP  , NO  , NO  , P4  , P5  , P6  , PMNS, \
      LSHIFT, NO  ,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, MINS,             ENT ,       NO  , HOME, NO  , NO  , P1  , P2  , P3  ,       \
                                          SPC ,                                                         LEFT, DOWN, RGHT, NO  , P0  , NO  , NO  , PENT  \
    )                              
};

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}
