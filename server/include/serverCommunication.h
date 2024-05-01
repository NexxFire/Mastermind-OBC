#ifndef SERVERCOMMUNICATION_H
#define SERVERCOMMUNICATION_H

#include "serverData.h"
#include "socketData.h"
#include "socketSession.h"
#include <pthread.h>
#include <unistd.h>

struct threadListenningArgs {
    gameData_t *gameData;
    pthread_t *threadClients;
};
typedef struct threadListenningArgs threadListenningArgs_t;

void clientRegistration(gameData_t *gameData);

#endif