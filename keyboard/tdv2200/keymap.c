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
 * |  ESC|  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | F13 |  F14 |  |STRYK| KOPI|FLYTT|     | P1  | P2  | P3  | P4  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 *                                                                                               | TAB | (...| aaa |     | P5  | P6  | P7  | P8  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * | * Caps |   1 |   2 |   3 |   4 |   5 |   6 |   7 |   8 |   9 |   0 |   + |   @ |???| BCSP|  | < < | JUST| > > |     | 000 | 00  |  =  |SPACE|
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * | Eksp| CTRL|   Q |   W |   E |   R |   T |   Y |   U |   I |   O |   P |   Å |  ^ |  LF   |  | <== |ANGRE| ==> |     |  7  |  8  |  9  |  +  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|-----|
 * |  ^^ |* LOCK|   A |   S |   D |   F |   G |   H |   J |   K |   L |   Ø |   Æ |   * |  E  |  | <=  | UP  |  => |     |  4  |  5  |  6  |  -  |
 * |------------------------------------------------------------------------------------|  N  |  |-----|-----|-----|     |-----|-----|-----|-----|
 * |    Lshift| <  |   Z |   X |   C |   V |   B |   N |   M |   , |   . |   - | Rshift |  T  |  |HOME | UP  | END |     |  1  |  2  |  3  |  E  |
 * |------------------------------------------------------------------------------------------|  |-----|-----|-----|     |-----|-----|-----|  N  |
 *                             |          SPACE                          |                       |LEFT |DOWN |RIGHT|     |     0     |  ,  |  T  |
 *                             `-----------------------------------------'                       `-----------------'     `-----------------------'
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer */
    [0] = KEYMAP( \
        ESC , F1  , F2  , F3  , F4  , F5  , F6  , F7  , F8  , F9  , F10 , F11 , F12 , F13 , F14 ,       NO  , NO  , NO  , NO  , NO  , NO  , NO  , FN1 , \
                                                                                                        NO  , NO  , NO  , NO  , NO  , NO  , NO  , NO  , \
        CAPS,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,EQL  , BSPC, BSPC,       NO  , NO  , NO  , NO  ,FN18 ,FN17 , PEQL, SPC , \
        LGUI,LCTRL,    Q,    W,    E,    R,    T,    Y,    U,    I,    O, P   , LBRC, RBRC, ENT ,       NO  , NO  , PGUP, NO  , P7  , P8  , P9  , PPLS, \
        LALT, LSCR,    A,    S,    D,    F,    G,    H,    J,    K,    L,SCOLON, NO  , PAST,            NO  , NO  , PGDN, NO  , P4  , P5  , P6  , PMNS, \
      LSHIFT, SCLN,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH,             ENT ,       HOME, UP  , END , NO  , P1  , P2  , P3  ,       \
                                          SPC ,                                                         LEFT, DOWN, RGHT, NO  , P0  , NO  , NO  , PENT  \
    )                              
}; 

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	phex(layer); 
	print(" "); 
	phex(key.row); 
	print(" "); 
	phex(key.col); 
	print("\n"); //Prints the layer to debug console.. only used for debugging layers
	return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}
