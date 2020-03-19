#include "max7219_driver.h"
#include <avr/io.h>

void driver_init() {
    DDRB |= (1 << SCK) | (1 << DO) | (1 << CS);
    PORTB |= (1 << CS);
    USISR = 0;
}

void sendByte(uint8_t data) {
    USIDR = data;
    PORTB &= ~(1 << CS);

    while (!(USISR & (1 << USICNT3))) {
        USICR = (1 << USITC);
        USICR = (1 << USITC) | (1 << USICLK);
    }
    USISR = 0;
    PORTB |= (1 << CS);
}

void sendWord(uint16_t data) {
    uint8_t lowerByte = data & 0xFF;
    sendByte(data >> 8);
    sendByte(lowerByte);
}
