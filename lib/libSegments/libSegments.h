#ifndef LIBSEGMENTS_H
#define LIBSEGMENTS_H

#include <wiringPi.h>
#include <wiringPiI2C.h>


#define ADDRESS_7SEGMENT 0x70

#define DIGIT_1 0x00
#define DIGIT_2 0x02
#define DIGIT_3 0x06
#define DIGIT_4 0x08
#define DIGIT_COLON 0x04
extern const char digit[4];

#define SEG_A 0x01
#define SEG_B 0x02
#define SEG_C 0x04
#define SEG_D 0x08
#define SEG_E 0x10
#define SEG_F 0x20
#define SEG_G 0x40
#define SEG_DP 0x80
extern const char segment[8];
#define COLON_ON 0x02
#define COLON_OFF 0x00

// Définir les registres
#define SYSTEM_SETUP_REG 0x21
#define ROW_INT_REG 0x01
#define DISPLAY_SETUP_REG 0x80
#define DIMMING_REG 0xE0
#define DISPLAY_DATA_ADDR_POINTER 0x00


#define SEG_VALUE_1 (SEG_B | SEG_C)
#define SEG_VALUE_2 (SEG_A | SEG_B | SEG_G | SEG_E | SEG_D)
#define SEG_VALUE_3 (SEG_A | SEG_B | SEG_G | SEG_C | SEG_D)
#define SEG_VALUE_4 (SEG_F | SEG_G | SEG_B | SEG_C)
#define SEG_VALUE_5 (SEG_A | SEG_F | SEG_G | SEG_C | SEG_D)
#define SEG_VALUE_6 (SEG_A | SEG_F | SEG_G | SEG_C | SEG_D | SEG_E)
#define SEG_VALUE_7 (SEG_A | SEG_B | SEG_C)
#define SEG_VALUE_8 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define SEG_VALUE_9 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)
#define SEG_VALUE_0 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
extern const char segment_value[10];

void init7Segment();
void displayDigit(int digit, int value);
void displayNumber(int number);
void displayColon(int value);
void displayClear();
void displayClearDigit(int digit);




#endif