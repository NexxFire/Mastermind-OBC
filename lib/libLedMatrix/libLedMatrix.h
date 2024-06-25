#ifndef LIBLEDMATRIX_H
#define LIBLEDMATRIX_H

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>
#include <unistd.h>

#pragma GCC diagnostic ignored "-Wchar-subscripts"

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

#define EMPTY_MATRIX 0x00

void initSPI();
void __writeSPI(int addr, int data);
void __setRow(int row, int value);
void __displayMatrix(const char matrix[8]);
void resetMatrix();
void displayCharMatrix(char c);
void displayScrollTextMatrix(const char* text);

extern const char ascii[128][8];

#endif // LIBLEDMATRIX_H