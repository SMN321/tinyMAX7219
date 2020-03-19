
#ifndef MAX7219_DRIVER_H
#define MAX7219_DRIVER_H

#include <inttypes.h>

void sendByte(uint8_t data);
void sendWord(uint16_t data);

uint8_t receiveByte(void);


#endif
