#ifndef INIT_H
#define INIT_H

#include "clientData.h" // client/include/clientData.h

void _initBoard(char board[MAX_ROUND][BOARD_WIDTH]);
void _initResult(char result[MAX_ROUND][RESULT_WIDTH]);
void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS]);
void initGame(game_t *game);

#endif