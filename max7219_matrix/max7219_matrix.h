
#ifndef MAX7219_MATRIX_H
#define MAX7219_MATRIX_H

#include <inttypes.h>
#include "../max7219_driver/max7219_driver.h"

//TODO: implement n*8xm*8 matrices

void max7219_matrix_set_pixel(uint8_t x, uint8_t y);
void max7219_matrix_set_row(uint8_t row, uint8_t data);
void max7219_matrix_set_col(uint8_t col, uint8_t data);
void max7219_matrix_set_matrix(const uint8_t data[8]);// 8x8 bit -> uint8_t[8]
void max7219_matrix_update(void);

#endif //MAX7219_MATRIX_H
