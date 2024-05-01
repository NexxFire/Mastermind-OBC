#ifndef SERVERDATA_H
#define SERVERDATA_H


#include "socketSession.h"
#include "clientData.h"

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

#define SERVER_IP ""
#define SERVER_PORT 58392


struct player
{
    char board[MAX_ROUND][BOARD_WIDTH];
    char result[MAX_ROUND][RESULT_WIDTH];
    socket_t socket;
    int ready;
};
typedef struct player player_t;


struct playerList
{
    player_t players[MAX_PLAYERS];
    int nbPlayers;
};
typedef struct playerList playerList_t;


struct gameData {
    playerList_t playerList;
    char secretCode[BOARD_WIDTH];
    int gameFinished; 
};
typedef struct gameData gameData_t;


#endif