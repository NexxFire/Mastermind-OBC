#include "server.h"


int main() {
    gameData_t gameData;
    while (1) {
        serverInit(&gameData);
        clientRegistration(&gameData);
        createCombinations(&gameData);
        startGame(&gameData);
        endGame(&gameData);
    }
    return 0;
}

void createCombinations(gameData_t *gameData) {
    char * colors = "BVRJNO";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        gameData->secretCode[i] = colors[rand() % strlen(colors)];
    }
}

void startGame(gameData_t *gameData) {
    pthread_t threadClients[MAX_PLAYERS];
    clientThreadHandlerArgs_t clientThreadHandlerArgs[MAX_PLAYERS];
    
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        clientThreadHandlerArgs[i].gameData = gameData;
        clientThreadHandlerArgs[i].playerIndex = i;
        pthread_create(&threadClients[i], 
                        NULL, 
                        clientThreadHandler, 
                        &clientThreadHandlerArgs[i]);
    }
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        pthread_join(threadClients[i], NULL);
    }
    
}

void checkChoice(gameData_t *gameData, int playerIndex) {
    player_t *player = &gameData->playerList.players[playerIndex];
    char colors[6] = "RBGCYM";
    int nbcolorsCombination[6] = {0};
    int nbcolorsPlayer[6] = {0};
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < 6; j++) {
            if (gameData->secretCode[i] == colors[j]) {
                nbcolorsCombination[j]++;
            }
            if (player->board[player->nbRound][i] == colors[j]) {
                nbcolorsPlayer[j]++;
            }
        }
        if (player->board[player->nbRound][i] == gameData->secretCode[i]) {
            player->result[player->nbRound][0]++;
        }
    }
    for (int i = 0; i < 6; i++) {
        player->result[player->nbRound][1] += MIN(nbcolorsCombination[i], nbcolorsPlayer[i]);
    }
    player->result[player->nbRound][1] -= player->result[player->nbRound][0];
    if (player->result[player->nbRound][0] == BOARD_WIDTH) {
        gameData->gameWinner = playerIndex;
    }
}

void endGame(gameData_t *gameData) {
    char buffer[10];
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        if (i == gameData->gameWinner) {
            strcpy(buffer, "win\0");
        } else {
            sprintf(buffer, "loose:%d", gameData->gameWinner);
        }
        envoyer(&gameData->playerList.players[i].socket, buffer, NULL);
        envoyer(&gameData->playerList.players[i].socket, gameData->secretCode, NULL);
    }

}


void *clientThreadHandler(void *args) {
    clientThreadHandlerArgs_t *clientThreadHandlerArgs = (clientThreadHandlerArgs_t *)args;
    while (clientThreadHandlerArgs->gameData->playerList.players[clientThreadHandlerArgs->playerIndex].nbRound < MAX_ROUND && clientThreadHandlerArgs->gameData->gameWinner == EMPTY) {
        getPlayerChoice(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        checkChoice(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        sendResult(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        clientThreadHandlerArgs->gameData->playerList.players[clientThreadHandlerArgs->playerIndex].nbRound++;
    }
    return NULL;
}



    