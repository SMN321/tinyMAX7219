
#ifndef MAX7219_DRIVER_H
#define MAX7219_DRIVER_H

#include <inttypes.h>

#define SCK PB2
#define DO PB1
#define CS PB0

void driver_init(void);

void sendByte(uint8_t data);
void sendWord(uint16_t data);

#endif
