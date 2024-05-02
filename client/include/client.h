#ifndef CLIENT_H
#define CLIENT_H


#include "clientData.h" 
#include "clientInit.h" 
#include "clientShow.h" 
#include "clientCommunication.h" 
#include "socketData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


void sendCombination(game_t *game);
void getResult(game_t *game);
void fetchOtherClientsData(game_t *game);
int isGameOver(game_t game);
void endGame(game_t game);

#endif