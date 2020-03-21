
#ifndef MAX7219_DRIVER_H
#define MAX7219_DRIVER_H

#include <inttypes.h>

//pins
#define MAX7219_SCK PB2
#define MAX7219_DO PB1
#define MAX7219_CS PB0

//register address map
#define MAX7219_NO_OP           0x0
#define MAX7219_DIGIT_0         0x1
#define MAX7219_DIGIT_1         0x2
#define MAX7219_DIGIT_2         0x3
#define MAX7219_DIGIT_3         0x4
#define MAX7219_DIGIT_4         0x5
#define MAX7219_DIGIT_5         0x6
#define MAX7219_DIGIT_6         0x7
#define MAX7219_DIGIT_7         0x8
#define MAX7219_DECODE_MODE     0x9
#define MAX7219_INTENSITY       0xA
#define MAX7219_SCAN_LIMIT      0xB
#define MAX7219_SHUTDOWN        0xC
#define MAX7219_DISPLAY_TEST    0xF

//register data
#define MAX7219_SCAN_LIMIT_0    0x0
#define MAX7219_SCAN_LIMIT_1    0x1
#define MAX7219_SCAN_LIMIT_2    0x2
#define MAX7219_SCAN_LIMIT_3    0x3
#define MAX7219_SCAN_LIMIT_4    0x4
#define MAX7219_SCAN_LIMIT_5    0x5
#define MAX7219_SCAN_LIMIT_6    0x6
#define MAX7219_SCAN_LIMIT_7    0x7
#define MAX7219_SHUTDOWN_ON     0x0
#define MAX7219_SHUTDOWN_OFF    0x1
#define MAX7219_DISPLAY_TEST_ON 0x1
#define MAX7219_DISPLAY_TEST_OFF 0x0

//functions
void max7219_init(void);
void max7219_send_command(uint8_t address,uint8_t data);

#endif //MAX7219_DRIVER_H
