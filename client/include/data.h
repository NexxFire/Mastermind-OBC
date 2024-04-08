#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <stddef.h>

#define MAX_ROUND 12
#define BOARD_WIDTH 4
#define RESULT_WIDTH 2
#define MAX_PLAYERS 4
#define EMPTY -1
#define RED 'R'
#define GREEN 'G'
#define BLUE 'B'
#define YELLOW 'Y'
#define CYAN 'C'
#define MAGENTA 'M'

struct otherPlayer
{
    int nbRound;
    int nbGoodPlace;
    int nbGoodColor;
};
typedef struct otherPlayer otherPlayer_t;

struct game
{
    char board[MAX_ROUND][BOARD_WIDTH];
    char result[MAX_ROUND][RESULT_WIDTH];
    otherPlayer_t otherPlayers[MAX_PLAYERS];
};
typedef struct game game_t;







#endif