
#include "MAX7219_driver.h"
#include <avr/io.h>

static inline void send_byte(uint8_t data) {
    USIDR = data;
    asm volatile (
        "ldi r16, %A0"  "\n\t" //load mask
        "ldi r17, %A1"  "\n\t"
        "out %[usicr], r16"   "\n\t" //MSB
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t"
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t"
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t"
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t"
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t"
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t"
        "out %[usicr], r17"   "\n\t"
        "out %[usicr], r16"   "\n\t" //LSB
        "out %[usicr], r17"   "\n\t"
        :
        : [usicr] "I" (_SFR_IO_ADDR(USICR)),
          "n" ((1<<USIWM0)|(0<<USICS0)|(1<<USITC)),
          "n" ((1<<USIWM0)|(0<<USICS0)|(1<<USITC)|(1<<USICLK))
        );
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
