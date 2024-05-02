#include "serverCommunication.h"



void clientRegistration(gameData_t *gameData) {
    pthread_t threadListenning;
    pthread_t threadClients[MAX_PLAYERS];
    listenningThreadHandlerArgs_t listenningThreadHandlerArgs;
    listenningThreadHandlerArgs.gameData = gameData;
    listenningThreadHandlerArgs.threadClients = threadClients;
    pthread_create(&threadListenning, 
                    NULL, 
                    _listenningThreadHandler, 
                    &listenningThreadHandlerArgs);
    
    while (gameData->playerList.nbPlayers == 0){
        sleep(1);
    }
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        pthread_join(threadClients[i], NULL);
    }
    pthread_join(threadListenning, NULL);
}


void getPlayerChoice(gameData_t *gameData, int playerIndex) {
    player_t *player = &gameData->playerList.players[playerIndex];
    recevoir(&player->socket, player->board[player->nbRound], NULL);
}

void sendResult(gameData_t *gameData, int playerIndex) {
    //send result to the player and send other player result to the player
    char buffer[RESULT_WIDTH+2];
    player_t *player = &gameData->playerList.players[playerIndex];
    
    for (int i = 0; i < RESULT_WIDTH; i++) {
        buffer[i] = player->result[player->nbRound][i];
    }
    buffer[RESULT_WIDTH] = '\0';
    envoyer(&player->socket, buffer, NULL);

    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        if (i != playerIndex) {
            for (int j = 0; j < RESULT_WIDTH; j++) {
                buffer[j] = gameData->playerList.players[i].result[gameData->playerList.players[i].nbRound][j];
            }
            buffer[RESULT_WIDTH] = gameData->playerList.players[i].nbRound;
            buffer[RESULT_WIDTH+1] = '\0';
            envoyer(&player->socket, buffer, NULL);
        }
    }
}





void *_listenningThreadHandler(void *args) {
    listenningThreadHandlerArgs_t *listenningThreadHandlerArgs = (listenningThreadHandlerArgs_t *)args;
    socket_t serverListenningSocket = creerSocketEcoute(SERVER_IP, SERVER_PORT);
    while (listenningThreadHandlerArgs->gameData->playerList.nbPlayers < MAX_PLAYERS) {
        listenningThreadHandlerArgs->gameData->playerList.players[listenningThreadHandlerArgs->gameData->playerList.nbPlayers].socket = accepterClt(serverListenningSocket);
        pthread_create(&listenningThreadHandlerArgs->threadClients[listenningThreadHandlerArgs->gameData->playerList.nbPlayers], 
                        NULL, 
                        _clientReadyThreadHandler, 
                        &listenningThreadHandlerArgs->gameData->playerList.players[listenningThreadHandlerArgs->gameData->playerList.nbPlayers]);
        listenningThreadHandlerArgs->gameData->playerList.nbPlayers++;
    }
    return NULL;
}


void *_clientReadyThreadHandler(void *args) {
    player_t *player = (player_t *)args;
    char buffer[1024];
    while (!player->ready) {
        recevoir(&player->socket, buffer, NULL);
        if (strcmp(buffer, "ready") == 0) {
            player->ready = 1;
        }
    }
    return NULL;
}

