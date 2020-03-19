#include "max7219_driver.h"
#include <avr/io.h>

void sendByte(uint8_t data) {
    USIDR = data;
    asm volatile (
    "ldi r16,(1<<USIWM0)|(0<<USICS0)|(1<<USITC)" "\n\t"
    "ldi r17,(1<<USIWM0)|(0<<USICS0)|(1<<USITC)|(1<<USICLK)" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    "out USICR,r16" "\n\t"
    "out USICR,r17" "\n\t"
    );
}

void sendWord(uint16_t data) {
    uint8_t lowerByte = data & 0xFF;
    sendByte(data >> 8);
    sendByte(lowerByte);
}

uint8_t receiveByte(void) {
    return USIBR;
}

