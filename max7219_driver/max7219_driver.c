
#include "MAX7219_driver.h"
#include <avr/io.h>

static inline void send_byte(uint8_t data) {
    USIDR = data;
    //unrolled loop for faster computation
    USICR = (1 << USIWM0) | (1 << USITC); //USIWM0 == 1 to use the 3-wire-mode
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USICR = (1 << USIWM0) | (1 << USITC);
    USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
    USISR = 0;
}

inline void max7219_init() {
    DDRB |= (1 << MAX7219_SCK) | (1 << MAX7219_DO) | (1 << MAX7219_CS);
    PORTB |= (1 << MAX7219_CS);
    PORTB &= ~(1 << MAX7219_SCK);
    USISR = 0;
    max7219_send_command(MAX7219_SCAN_LIMIT, MAX7219_SCAN_LIMIT_7);
    max7219_send_command(MAX7219_DISPLAY_TEST, MAX7219_DISPLAY_TEST_OFF);
    max7219_send_command(MAX7219_SHUTDOWN, MAX7219_SHUTDOWN_OFF);
    max7219_send_command(MAX7219_INTENSITY, MAX7219_INTENSITY_MID);
}

inline void max7219_send_command(uint8_t address, uint8_t data) {
    PORTB &= ~(1 << MAX7219_CS);
    send_byte(address);
    send_byte(data);
    PORTB |= (1 << MAX7219_CS);
} 
