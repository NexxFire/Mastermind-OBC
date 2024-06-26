#include "libButton.h"
#include <stdio.h>

int buttonRows[BUTTON_ROWS] = {BUTTON_ROW_1, BUTTON_ROW_2, BUTTON_ROW_3, BUTTON_ROW_4};
int buttonCols[BUTTON_COLS] = {BUTTON_COL_1, BUTTON_COL_2, BUTTON_COL_3, BUTTON_COL_4};


void initButton(){
    wiringPiSetup();
    // Set the buttonRows as inputs and columns as outputs
    for (int i = 0; i < BUTTON_ROWS; i++) {
        pinMode(buttonRows[i], OUTPUT);
        //pullUpDnControl(buttonRows[i], PUD_UP);
        digitalWrite(buttonRows[i], HIGH);
    }

    for (int i = 0; i < BUTTON_COLS; i++) {
        pinMode(buttonCols[i], INPUT);
        //pullUpDnControl(buttonCols[i], PUD_UP);
    }

}

int readButton(){
    
    while (1) {
        for (int i = 0; i < BUTTON_ROWS; i++) {
            digitalWrite(buttonRows[i], LOW);
            for (int j = 0; j < BUTTON_COLS; j++) {
                if (digitalRead(buttonCols[j]) == LOW) {
                    delay(150);
                    digitalWrite(buttonRows[i], HIGH);
                    return i * BUTTON_COLS + j;
                }
            }
            digitalWrite(buttonRows[i], HIGH);
        }
    }
}