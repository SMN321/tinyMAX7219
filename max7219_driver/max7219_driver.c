
#include "max7219_driver.h"
#include <avr/io.h>

static inline void send_byte(uint8_t data) {
    USIDR = data;
    // this seemed to work in the simulations
    // the whole block needed 20 clock cycles there
    asm volatile (
    /* asm instructions */
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"  "\n\t"
    "out %[usicr], %[high]" "\n\t"
    "out %[usicr], %[low]"
    : /* no outputs */
    : /* only inputs */
    [usicr] "M" (_SFR_IO_ADDR(USICR)),
    [high] "r" ((1<<USIWM0)|(0<<USICS0)|(1<<USITC)),
    [low] "r" ((1<<USIWM0)|(0<<USICS0)|(1<<USITC)|(1<<USICLK))
    /* no clobbers */);
    USISR = 0;
}

inline void max7219_init() {
    DDRB |= (1u << MAX7219_SCK) | (1u << MAX7219_DO) | (1u << MAX7219_CS);
    PORTB |= (1u << MAX7219_CS);
    PORTB &= ~(1u << MAX7219_SCK);
    USISR = 0;
    max7219_send_command(MAX7219_DECODE_MODE, 0x00); // no Code B decoding
    max7219_send_command(MAX7219_SCAN_LIMIT, MAX7219_SCAN_LIMIT_7);
    max7219_send_command(MAX7219_DISPLAY_TEST, MAX7219_DISPLAY_TEST_OFF);
    max7219_send_command(MAX7219_SHUTDOWN, MAX7219_SHUTDOWN_OFF);
    max7219_send_command(MAX7219_INTENSITY, MAX7219_INTENSITY_MID);
}

inline void max7219_send_command(uint8_t address, uint8_t data) {
    PORTB &= ~(1u << MAX7219_CS);
    send_byte(address);
    send_byte(data);
    PORTB |= (1u << MAX7219_CS);
} 
