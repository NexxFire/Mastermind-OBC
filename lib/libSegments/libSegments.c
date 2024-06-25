#include "libSegments.h"

const char digit[4] = {DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4};
const char segment[8] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP};
const char segment_value[10] = {SEG_VALUE_0, SEG_VALUE_1, SEG_VALUE_2, SEG_VALUE_3, SEG_VALUE_4, SEG_VALUE_5, SEG_VALUE_6, SEG_VALUE_7, SEG_VALUE_8, SEG_VALUE_9};

int fd;

void init7Segment(){
    wiringPiI2CSetup(ADDRESS_7SEGMENT);
    wiringPiI2CWriteReg8(fd, 0x21, 0x01);
    wiringPiI2CWriteReg8(fd, 0x81, 0x00); 
    wiringPiI2CWriteReg8(fd, 0xef, 0x00);
}

void displayDigit(int digit, int value){
    wiringPiI2CWriteReg8(fd, digit, value);
}

void displayNumber(int number){
    int i;
    for(i=0;i<4;i++){
        displayDigit(digit[i], segment_value[number%10]);
        number /= 10;
    }
}

void displayColon(int value){
    wiringPiI2CWriteReg8(fd, DIGIT_COLON, value);
}

void displayClear(){
    int i;
    for(i=0;i<4;i++){
        displayClearDigit(digit[i]);
    }
    displayColon(COLON_OFF);
}

void displayClearDigit(int digit){
    displayDigit(digit, 0x00);
}

