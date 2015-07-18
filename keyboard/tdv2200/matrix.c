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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
//#include "xprintf.h"

#define debug_enable 1
#define print_enable 1
#define debug_keyboard 1


/*
 * Tandberg TDV2200-S keyboard
 *
 * Pin usage:
 *   COL: PD0-7      12 -> 19
 *   ROW: PB0-3      27 -> 30, paralell shift register   
 *   ROW EN: PB5     8
 *   ROW AUX: PB4    31
 *   Sound Control   B7, F5
 */

 /*
 8 - B5
10 - B6
12 - D0
13 - D1
14 - D2
15 - D3 
16 - D4
17 - D5
18 - D6
19 - D7

27 - B0
28 - B1
29 - B2
30 - B3
31 - B4
33 - GND  B7
34 - GND  B7
36 - 5V   F5
37 - F6
38 - F7
*/

#define ROW_AUX     1 << 4
#define ROW_DISABLE 1 << 5
#define LED_DISABLE 1 << 6

#define AUDIO_BIT1  1 << 7
#define AUDIO_PORT1 B

#define AUDIO_BIT2  1 << 5
#define AUDIO_PORT2 F


#ifndef DEBOUNCE
#   define DEBOUNCE	10
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static matrix_row_t read_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);
static void printBits(uint8_t b);


inline
void printBits(uint8_t b) {
    for (int i = 7; i >= 0; i--) {
         if ((b & (1 << i)) == 0) debug("0");
         else                     debug("1");
    }
    debug(" ");
}


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{



    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // initialize rows and enable pins to output
    // DDRB 0->3 = ROW 1->16 
    // DDRB 4    = ROW 17    // Disables TTL Mux, also set DDRB0->3 to low
    // DDRB 5    = ROW ENABLE
    DDRB = 0xFF;
    DDRB = 0x00;

    // initialize rows
    unselect_rows();

    // initialize columns to input
    DDRD = 0x00;
    PORTD = 0x00;



    // Set CAPS / Scroll lock leds
    DDRF |= (1<<7);
    PORTF &= ~(1<<7);
    
    DDRF |= (1<<6);
    PORTF &= ~(1<<6);


    // Set Audio so wee dont beep to death :)
    DDRB |= (1<<7);
    PORTB &= ~(1<<7);

    DDRF |= (1<<5);
    PORTF |= (1<<5);

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
    debug("Matrix initiated");
}




uint8_t matrix_scan(void)
{
    //static int debug_row = 0;
    //if (debug_row > 1000) {
    //    debug_row = 0;
    //}
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        //if (debug_row == 0)  { 
        //    debug_hex(i); (" - "); debug("PORTB:"); debug_hex(PORTB); debug("("); printBits(DDRB); debug("/"); printBits(PORTB); debug(") "); 
        //                                debug_hex(PORTD); debug("("); printBits(DDRD); debug("/"); printBits(PIND); debug(")\n"); }

        _delay_us(10);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }



    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
    // Remove nonexistent keys from matrix, these keys always reports as pressed.
    matrix[0x10] &= ~(1<<6 | 1<<5);

    //if (debug_row == 0)  { 
    //    matrix_print();

    //}


    //debug_row++;

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    matrix_print();
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]))
            return true;
    }
    return false;
}
#endif

inline
static matrix_row_t read_cols(void)
{
    PORTB |= ROW_DISABLE;      // Disables the disable pin.. :) = Enable buffer
    _delay_us(2); 
    uint8_t p = PIND;
    PORTB &= ~ROW_DISABLE;     // Enable the disable pin.. = Disable buffer

    return p;
    
}

inline
static void unselect_rows(void)
{
    // Disable output buffer and resets row to 0
    // Neds rewrite
    PORTB = ROW_DISABLE | LED_DISABLE | 0x0;
}

inline
static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    if (row < 16) {
        // Enables TTL Mux and configures Mux bits

        PORTB = LED_DISABLE | (row & 0x0F);
        DDRB = 0xFF;
    }  else {
        // Disables TTL Mux, also set DDRB0->3 to low
        PORTB = LED_DISABLE | ROW_AUX | (0x00);
        DDRB = 0xFF;
    }


}
