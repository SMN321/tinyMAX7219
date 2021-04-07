
#ifndef MAX7219_MATRIX_H
#define MAX7219_MATRIX_H

#include <inttypes.h>
#include "../max7219_driver/max7219_driver.h"

//TODO: implement n*8xm*8 matrices

// uncomment the next macro or define it by yourself if the display should not be updated automatically
// after each change of the matrix-state buffer
//#define MAX7219_MATRIX_UPDATE_MANUALLY

void max7219_matrix_set_pixel(uint8_t row, uint8_t col, uint8_t state);
void max7219_matrix_activate_pixel(uint8_t row, uint8_t col);
void max7219_matrix_clear_pixel(uint8_t row, uint8_t col);
void max7219_matrix_set_row(uint8_t row, uint8_t data);
void max7219_matrix_set_col(uint8_t col, uint8_t data);
void max7219_matrix_set_matrix(const uint8_t data[8]);// 8x8 bit -> uint8_t[8]
void max7219_matrix_set_hex_string(uint64_t data);
void max7219_matrix_shift_left(void);
void max7219_matrix_shift_right(void);
void max7219_matrix_shift_left_circular(void);
void max7219_matrix_shift_right_circular(void);
void max7219_matrix_invert_elements(void);
void max7219_matrix_transpose(void);
void max7219_matrix_rotate_left(void);
void max7219_matrix_rotate_right(void);
void max7219_matrix_flip_horizontal(void);
void max7219_matrix_flip_vertical(void);
void max7219_matrix_clear(void);
void max7219_matrix_update(void);

#endif //MAX7219_MATRIX_H
