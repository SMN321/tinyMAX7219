
#include "max7219_matrix.h"

static volatile uint8_t matrix[8];  // row-first indexing

void max7219_matrix_set_pixel(uint8_t row, uint8_t col, uint8_t state) {
    if (state) {
        max7219_matrix_activate_pixel(row, col);
    } else {
        max7219_matrix_clear_pixel(row, col);
    }
    // both of the above methods may call update(), no need to introduce redundancy here.
}

void max7219_matrix_activate_pixel(uint8_t row, uint8_t col) {
    matrix[row] |= (1u << (uint8_t) (7 - col));
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_clear_pixel(uint8_t row, uint8_t col) {
    matrix[row] &= ~(1u << (uint8_t) (7-col));
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_set_row(uint8_t row, uint8_t data) {
    matrix[row] = data;
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

//MSB of data will be in row 0, LSB of data will be in row 7
void max7219_matrix_set_col(uint8_t col, uint8_t data) {
    uint8_t mask = ~(1u << (uint8_t) (7 - col));
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] &= mask; //set the column col in row row to 0
        //maybe change this to a conditional branch for the sake of readability
        matrix[row] |= ((uint8_t) ((uint8_t) data >> (uint8_t) (7 - row)) & 1u) << (uint8_t) (7 - col);  //set the data
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_set_matrix(const uint8_t data[8]) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = data[row];
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_set_hex_string(uint64_t data) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = 0xFFu & (data >> (uint8_t) (8 * (7 - row)));
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_shift_left(void) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] <<= 1u;
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_shift_right(void) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] >>= 1u;
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_shift_left_circular(void) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = (uint8_t) (matrix[row] << 1u) | (uint8_t) (matrix[row] >> 7u);
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_shift_right_circular(void) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = (uint8_t) (matrix[row] << 7u) | (uint8_t) (matrix[row] >> 1u);
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

// this is no mathematical matrix inversion but the inversion of each bit (in a binary context)
void max7219_matrix_invert_elements(void) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = ~matrix[row];
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_rotate_left(void) {
    uint8_t temp[8] = {0};
    for (uint8_t row_old = 0; row_old < 8; ++row_old) {
        for (uint8_t row_new = 0; row_new < 8; ++row_new) {
            temp[row_new] |= (uint8_t) ((uint8_t) ((uint8_t) (matrix[row_old] & (uint8_t) (1u << row_new)) >> row_new) \
                             << (uint8_t) (7 - row_old));
        }
    }
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = temp[row];
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_rotate_right(void) {
    uint8_t temp[8] = {0};
    for (uint8_t row_old = 0; row_old < 8; ++row_old) {
        for (uint8_t row_new = 0; row_new < 8; ++row_new) {
            temp[7 - row_new] |= (uint8_t) ((uint8_t) ((uint8_t) (matrix[row_old] & (uint8_t) (1u << row_new)) >> row_new) \
                                 << row_old);
        }
    }
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = temp[row];
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_flip_horizontal(void) {
    uint8_t temp;
    for (uint8_t row = 0; row < 4; ++row) {
        temp = matrix[7 - row];
        matrix[7 - row] = matrix[row];
        matrix[row] = temp;
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_flip_vertical(void) {
    uint8_t b;
    for (uint8_t row = 0; row < 8; ++row) {
        b = matrix[row];
        // reverse a byte
        b = (b & 0xF0u) >> 4u | (b & 0x0Fu) << 4u;
        b = (b & 0xCCu) >> 2u | (b & 0x33u) << 2u;
        b = (b & 0xAAu) >> 1u | (b & 0x55u) << 1u;
        matrix[row] = b;
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_clear(void) {
    for (uint8_t row = 0; row < 8; ++row) {
        matrix[row] = 0;
    }
    #ifndef MAX7219_MATRIX_UPDATE_MANUALLY
    max7219_matrix_update();
    #endif
}

void max7219_matrix_update(void) {
    for (volatile uint8_t row = 0; row < 8; ++row) {
        max7219_send_command(row + 1, matrix[row]);  // the MAX7219 starts indexing at 1
    }
}