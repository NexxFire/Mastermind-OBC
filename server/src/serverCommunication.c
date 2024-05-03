#include "serverCommunication.h"



void clientRegistration(gameData_t *gameData) {
    LOG(1, "Waiting for players to connect...\n");
    pthread_t threadListenning;
    pthread_t threadClients[MAX_PLAYERS];
    int gameStarted = 0;
    char buffer[6];
    listenningThreadHandlerArgs_t listenningThreadHandlerArgs;
    listenningThreadHandlerArgs.gameData = gameData;
    listenningThreadHandlerArgs.threadClients = threadClients;
    listenningThreadHandlerArgs.gameStarted = &gameStarted;
    pthread_create(&threadListenning, 
                    NULL, 
                    _listenningThreadHandler, 
                    &listenningThreadHandlerArgs);
    
    while (gameData->playerList.nbPlayers == 0){
        sleep(1);
    }
    LOG(1, "At least one player is connected. Game can start.\n");
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        pthread_join(threadClients[i], NULL);
        LOG(1, "Thread for player %d joined.\n", i);
        LOG(1, "nbPlayers: %d\n", gameData->playerList.nbPlayers);
    }
    gameStarted = 1;
    connecterClt2Srv(SERVER_IP, SERVER_PORT);
    pthread_join(threadListenning, NULL);
    LOG(1, "All players are ready.\n");
    buffer[0] = gameData->playerList.nbPlayers;
    buffer[1] = '\0';
    buffer[3] = '\0';
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        sendData(&gameData->playerList.players[i].socket, buffer, 2);
        buffer[2] = i;
        sendData(&gameData->playerList.players[i].socket, buffer+2, 8);
    }
}


void getPlayerChoice(gameData_t *gameData, int playerIndex) {
    gameData->playerList.players[playerIndex].board[MAX_ROUND-1][0] = 16;
    LOG(1, "Waiting for player %d to send his choice...\n", playerIndex);
    receiveData(&gameData->playerList.players[playerIndex].socket, gameData->playerList.players[playerIndex].board[gameData->playerList.players[playerIndex].nbRound], 3);
    LOG(1, "Player %d sent his choice :%s\n", playerIndex, gameData->playerList.players[playerIndex].board[gameData->playerList.players[playerIndex].nbRound]);
}

void sendResult(gameData_t *gameData, int playerIndex) {
    LOG(1, "Sending result to player %d...\n", playerIndex);
    //send result to the player and send other player result to the player
    char buffer[RESULT_WIDTH+2];
    
    for (int i = 0; i < RESULT_WIDTH; i++) {
        buffer[i] = gameData->playerList.players[playerIndex].result[gameData->playerList.players[playerIndex].nbRound][i]+'0';
    }
    buffer[RESULT_WIDTH] = '\0';
    sendData(&gameData->playerList.players[playerIndex].socket, buffer, 4);
    LOG(1, "Result sent to player %d : good place %c, good color %c\n", playerIndex, buffer[0], buffer[1]);
    LOG(1, "Sending other players result to player %d...\n", playerIndex);
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        if (i != playerIndex) {
            if (gameData->playerList.players[i].nbRound == 0) {
                buffer[0] = '0';
                buffer[1] = '0';
                buffer[2] = '0';
                buffer[3] = '\0';
                sendData(&gameData->playerList.players[playerIndex].socket, buffer, 5);
            } else {
                for (int j = 0; j < RESULT_WIDTH; j++) {
                    buffer[j] = gameData->playerList.players[i].result[gameData->playerList.players[i].nbRound-1][j]+'0';
                }
                buffer[RESULT_WIDTH] = gameData->playerList.players[i].nbRound+'0';
                buffer[RESULT_WIDTH+1] = '\0';
                sendData(&gameData->playerList.players[playerIndex].socket, buffer, 5);
            }
        }
    }
    LOG(1, "Other players result sent to player %d.\n", playerIndex);
}





void *_listenningThreadHandler(void *args) {
    LOG(1, "Listening for players on %s:%d\n", SERVER_IP, SERVER_PORT);
    listenningThreadHandlerArgs_t *listenningThreadHandlerArgs = (listenningThreadHandlerArgs_t *)args;
    socket_t serverListenningSocket = creerSocketEcoute(SERVER_IP, SERVER_PORT);
    while (listenningThreadHandlerArgs->gameData->playerList.nbPlayers < MAX_PLAYERS && !*listenningThreadHandlerArgs->gameStarted) {
        LOG(1, "nbPlayers: %d\n", listenningThreadHandlerArgs->gameData->playerList.nbPlayers);
        LOG(1, "gameStarted: %d\n", *listenningThreadHandlerArgs->gameStarted);
        listenningThreadHandlerArgs->gameData->playerList.players[listenningThreadHandlerArgs->gameData->playerList.nbPlayers].socket = accepterClt(serverListenningSocket);
        if (*listenningThreadHandlerArgs->gameStarted) {
            LOG(1, "Stop listening\n");
            break;
        }
        clientReadyThreadHandlerArgs_t clientReadyThreadHandlerArgs;
        clientReadyThreadHandlerArgs.gameData = listenningThreadHandlerArgs->gameData;
        clientReadyThreadHandlerArgs.playerIndex = listenningThreadHandlerArgs->gameData->playerList.nbPlayers;
        pthread_create(&listenningThreadHandlerArgs->threadClients[listenningThreadHandlerArgs->gameData->playerList.nbPlayers], 
                        NULL, 
                        _clientReadyThreadHandler, 
                        &clientReadyThreadHandlerArgs);
        LOG(1, "Player %d connected.\n", listenningThreadHandlerArgs->gameData->playerList.nbPlayers);
        listenningThreadHandlerArgs->gameData->playerList.nbPlayers++;

    }
    LOG(1, "All players are connected.\n");
    shutdown(serverListenningSocket.fd, SHUT_RDWR);
    close(serverListenningSocket.fd);
    pthread_exit(NULL);
}


void *_clientReadyThreadHandler(void *args) {
    clientReadyThreadHandlerArgs_t *clientReadyThreadHandlerArgs = (clientReadyThreadHandlerArgs_t *) args;
    LOG(1, "Waiting for player %d to be ready...\n", clientReadyThreadHandlerArgs->playerIndex);
    char buffer[1024];
    while (!clientReadyThreadHandlerArgs->gameData->playerList.players[clientReadyThreadHandlerArgs->playerIndex].ready) {
        receiveData(&clientReadyThreadHandlerArgs->gameData->playerList.players[clientReadyThreadHandlerArgs->playerIndex].socket, buffer, 1);
        if (strcmp(buffer, "ready") == 0) {
            clientReadyThreadHandlerArgs->gameData->playerList.players[clientReadyThreadHandlerArgs->playerIndex].ready = 1;
        }
    }
    LOG(1, "Player %d is ready.\n", clientReadyThreadHandlerArgs->playerIndex);
    pthread_exit(NULL);
}

