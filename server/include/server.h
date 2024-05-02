#ifndef SERVER_H
#define SERVER_H

#include "serverData.h"
#include "serverCommunication.h"
#include "serverInit.h"
#include <stdlib.h>

//define min function
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

struct clientThreadHandlerArgs
{
    gameData_t *gameData;
    int playerIndex;
};
typedef struct clientThreadHandlerArgs clientThreadHandlerArgs_t;


void createCombinations(gameData_t *gameData);
void startGame(gameData_t *gameData);
void checkChoice(gameData_t *gameData, int playerIndex);
void endGame(gameData_t *gameData);
void *clientThreadHandler(void *args);




#endif