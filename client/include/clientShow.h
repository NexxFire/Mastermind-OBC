/**
 *	\file		clientShow.c
 *	\brief		Handles the display of the game state for the client.
 *
 *	\details	This file contains the functions necessary for displaying the game state on the client side.
 */
#ifndef CLIENT_SHOW_H
#define CLIENT_SHOW_H

#include "clientData.h" 
#include "utils.h"
#include "libButton.h"
#include "libLCD.h"
#include "libLedMatrix.h"
#include "libSegments.h"
#include <stdio.h> 
#include <ncursesw/ncurses.h>
#include <locale.h>


#define HEIGHT MAX_ROUND * 2 + 1
#define WIDTH BOARD_WIDTH * 3 + 3 + 4*2
#define STARTX 30
#define STARTY 1


void initialize_ncurses();
void finalize_ncurses();
void showMenu();
void showHelp();
void showGame(game_t game);
void showBoard(game_t game);
void showRow(char row[BOARD_WIDTH], char result[RESULT_WIDTH], int round);
void showOtherUser(int round, int goodPlace, int goodColor, int starty, int startx);
void showChar(signed char c, int y, int x);
void showEndGame(game_t game);


#endif