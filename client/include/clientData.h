#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include "socketSession.h"

#define MAX_ROUND 12
#define BOARD_WIDTH 4
#define RESULT_WIDTH 2
#define MAX_PLAYERS 4
#define EMPTY -1
#define EMPTY_SCORE -2
#define RED 'R'
#define GREEN 'G'
#define BLUE 'B'
#define YELLOW 'Y'
#define CYAN 'C'
#define MAGENTA 'M'

#define LOG_LEVEL 1
#define LOG(level, fmt, ...) if (level <= LOG_LEVEL) fprintf(stdout, fmt, ##__VA_ARGS__)


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
    int nbRound;
    otherPlayer_t otherPlayers[MAX_PLAYERS -1];
    int nbPlayers;
    socket_t socket;
};
typedef struct game game_t;


#endif


