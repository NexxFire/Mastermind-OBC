#ifndef INIT_H
#define INIT_H

#include "data.h" // client/include/data.h

void _initBoard(char board[MAX_ROUND][BOARD_WIDTH]);
void _initResult(char result[MAX_ROUND][RESULT_WIDTH]);
void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS]);
void initGame(game_t *game);

#endif