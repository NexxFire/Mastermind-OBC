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
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        sendData(&gameData->playerList.players[i].socket, buffer, 2);
    }
}


void getPlayerChoice(gameData_t *gameData, int playerIndex) {
    LOG(1, "Waiting for player %d to send his choice...\n", playerIndex);
    player_t *player = &gameData->playerList.players[playerIndex];
    receiveData(&player->socket, player->board[player->nbRound], 3);
    LOG(1, "Player %d sent his choice :%s\n", playerIndex, player->board[player->nbRound]);
}

void sendResult(gameData_t *gameData, int playerIndex) {
    LOG(1, "Sending result to player %d...\n", playerIndex);
    //send result to the player and send other player result to the player
    char buffer[RESULT_WIDTH+2];
    player_t *player = &gameData->playerList.players[playerIndex];
    
    for (int i = 0; i < RESULT_WIDTH; i++) {
        buffer[i] = player->result[player->nbRound][i]+'0';
    }
    buffer[RESULT_WIDTH] = '\0';
    sendData(&player->socket, buffer, 4);
    LOG(1, "Result sent to player %d : good place %c, good color %c\n", playerIndex, buffer[0], buffer[1]);
    LOG(1, "Sending other players result to player %d...\n", playerIndex);
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        if (i != playerIndex) {
            for (int j = 0; j < RESULT_WIDTH; j++) {
                printf("Player %d result: %d\n", i, gameData->playerList.players[i].result[gameData->playerList.players[i].nbRound][j]);
                buffer[j] = gameData->playerList.players[i].result[gameData->playerList.players[i].nbRound][j]+'0';
            }
            buffer[RESULT_WIDTH] = gameData->playerList.players[i].nbRound+'0';
            buffer[RESULT_WIDTH+1] = '\0';
            printf("Sending: %s\n", buffer);
            sendData(&player->socket, buffer, 5);
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
        pthread_create(&listenningThreadHandlerArgs->threadClients[listenningThreadHandlerArgs->gameData->playerList.nbPlayers], 
                        NULL, 
                        _clientReadyThreadHandler, 
                        &listenningThreadHandlerArgs->gameData->playerList.players[listenningThreadHandlerArgs->gameData->playerList.nbPlayers]);
        listenningThreadHandlerArgs->gameData->playerList.nbPlayers++;
        LOG(1, "Player %d connected.\n", listenningThreadHandlerArgs->gameData->playerList.nbPlayers);
    }
    LOG(1, "All players are connected.\n");
    shutdown(serverListenningSocket.fd, SHUT_RDWR);
    close(serverListenningSocket.fd);
    pthread_exit(NULL);
}


void *_clientReadyThreadHandler(void *args) {
    LOG(1, "%s\n", "Waiting for player to be ready...");
    player_t *player = (player_t *)args;
    char buffer[1024];
    while (!player->ready) {
        receiveData(&player->socket, buffer, 1);
        printf("Received: %s\n", buffer);
        if (strcmp(buffer, "ready") == 0) {
            player->ready = 1;
        }
    }
    LOG(1, "%s\n", "Player is ready.");
    pthread_exit(NULL);
}

