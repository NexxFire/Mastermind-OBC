#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H

#include "serverData.h"
#include "socketData.h"
#include "socketSession.h"
#include <pthread.h>
#include <unistd.h>

struct listenningThreadHandlerArgs {
    gameData_t *gameData;
    pthread_t *threadClients;
    int *gameStarted;
};
typedef struct listenningThreadHandlerArgs listenningThreadHandlerArgs_t;

void clientRegistration(gameData_t *gameData);
void getPlayerChoice(gameData_t *gameData, int playerIndex);
void sendResult(gameData_t *gameData, int playerIndex);
void *_listenningThreadHandler(void *args);
void *_clientReadyThreadHandler(void *args);

#endif