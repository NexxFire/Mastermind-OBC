#ifndef LIBLCD_H
#define LIBLCD_H

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23008.h>
#include <lcd.h>
#include <string.h>


#define ADRESSELCD 0x21
#define AF_BASE 100
#define AF_STRB (AF_BASE+2)
#define AF_RW (AF_BASE+14)
#define AF_RS (AF_BASE+1)
#define AF_DB4 (AF_BASE+3)
#define AF_DB5 (AF_BASE+4)
#define AF_DB6 (AF_BASE+5)
#define AF_DB7 (AF_BASE+6)
#define AF_BLUE (AF_BASE+12)

#define AF_RED (107)


#define AF_BACKLIGHT_PIN (AF_BASE+15)
#define AF_BACKLIGHTGRD_PIN (AF_BASE+16)

#define SDA 3
#define SCL 5
#define ADRESSELCD 0x21
#define MAX_CAR 1000


int initLcd();
void displayLcd(char* msg);

#endif