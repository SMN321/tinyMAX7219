
#include "max7219_matrix.h"

static uint8_t matrix[8];

void max7219_matrix_set_pixel(uint8_t row, uint8_t col) {
    matrix[row] |= (1 << (7 - col));
}

void max7219_matrix_set_row(uint8_t row, uint8_t data) {
    matrix[row] = data;
}

//MSB of data will be in col 0, LSB of data will be in col 7
void max7219_matrix_set_col(uint8_t col, uint8_t data) {
    uint8_t mask = ~(1 << (7 - col));
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] &= mask; //set the column to 0
        matrix[i] |= (data >> (7 - i)) & 1; //set the data
    }
}

void max7219_matrix_set_matrix(const uint8_t data[8]) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = data[i];
    }
}

void max7219_matrix_set_hex_string(uint64_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = 0xFF & (data >> (8 * (7 - i)));
    }
}

void max7219_matrix_shift_left(void) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] <<= 1;
    }
}

void max7219_matrix_shift_right(void) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] >>= 1;
    }
}

void max7219_matrix_shift_left_circular(void) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = (matrix[i] << 1) | (matrix[i] >> 7);
    }
}

void max7219_matrix_shift_right_circular(void) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = (matrix[i] << 7) | (matrix[i] >> 1);
    }
}

void max7219_matrix_invert(void) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = ~matrix[i];
    }
}

void max7219_matrix_rotate_left(void) {
    uint8_t temp[8] = {0};
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            temp[j] |= ((matrix[i] & (1 << j)) >> j) << (7-i);
        }
    }
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = temp[i];
    }
}

void max7219_matrix_rotate_right(void) {
    uint8_t temp[8] = {0};
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            temp[7-j] |= ((matrix[i] & (1 << j)) >> j) << i;
        }
    }
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = temp[i];
    }
}

void max7219_matrix_flip_horizontal(void) {
    uint8_t temp;
    for (uint8_t i = 0; i < 4; i++) {
        temp = matrix[7-i];
        matrix[7-i] = matrix[i];
        matrix[i] = temp;
    }
}

void max7219_matrix_flip_vertical(void) {
    uint8_t b;
    for (uint8_t i = 0; i < 7; i++) {
        b = matrix[i];
        //reverse a byte
        b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
        b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
        b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
        matrix[i] = b;
    }
}

void max7219_matrix_clear(void) {
    for (uint8_t i = 0; i < 8; i++) {
        matrix[i] = 0;
    }
}

void max7219_matrix_update(void) {
    for (uint8_t i = 0; i < 8; i++) {
        max7219_send_command(i + 1, matrix[i]);
    }
}