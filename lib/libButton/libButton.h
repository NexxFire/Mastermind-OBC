#ifndef LIBBUTTONMATRIX_H
#define LIBBUTTONMATRIX_H

#include <wiringPi.h>

#define BUTTON_ROWS 4
#define BUTTON_COLS 4

// GPIO pins for the rows and columns
#define BUTTON_ROW_1 2 // Physical pin 13
#define BUTTON_ROW_2 3 // Physical pin 15
#define BUTTON_ROW_3 21 // Physical pin 29
#define BUTTON_ROW_4 22 // Physical pin 31

#define BUTTON_COL_1 6 // Physical pin 22
#define BUTTON_COL_2 25 // Physical pin 37
#define BUTTON_COL_3 24 // Physical pin 35
#define BUTTON_COL_4 23 // Physical pin 33

#define VALIDATION_BUTTON 15
#define HELP_BUTTON 12

// Create array for the rows and columns
extern int buttonRows[BUTTON_ROWS];
extern int buttonCols[BUTTON_COLS];

void initButton();
int readButton();

#endif
