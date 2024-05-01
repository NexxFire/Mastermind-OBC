#include "serverCommunication.h"



void clientRegistration(gameData_t *gameData) {
    pthread_t threadListenning;
    pthread_t threadClients[MAX_PLAYERS];
    threadListenningArgs_t threadListenningArgs;
    threadListenningArgs.gameData = gameData;
    threadListenningArgs.threadClients = threadClients;
    pthread_create(&threadListenning, NULL, listenningThread, &threadListenningArgs);

    while (gameData->playerList.nbPlayers == 0){
        sleep(1);
    }

    
    
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        pthread_join(threadClients[i], NULL);
    }

    pthread_join(threadListenning, NULL);
    
}

void listenningThread(threadListenningArgs_t *threadListenningArgs) {
    socket_t serverListenningSocket = creerSocketEcoute(SERVER_IP, SERVER_PORT);
    while (threadListenningArgs->gameData->playerList.nbPlayers < MAX_PLAYERS) {
        threadListenningArgs->gameData->playerList.players[threadListenningArgs->gameData->playerList.nbPlayers].socket = accepterClt(serverListenningSocket);
        pthread_create(&threadListenningArgs->threadClients[threadListenningArgs->gameData->playerList.nbPlayers], NULL, clientThread, &threadListenningArgs->gameData->playerList.players[threadListenningArgs->gameData->playerList.nbPlayers]);
        threadListenningArgs->gameData->playerList.nbPlayers++;
    }
}

void clientThread(player_t *player) {
    char buffer[1024];
    while (!player->ready) {
        recevoir(&player->socket, buffer, NULL);
        if (strcmp(buffer, "ready") == 0) {
            player->ready = 1;
        }
    }
}