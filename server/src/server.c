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
    LOG(1, "Creating secret code...\n");
    char * colors = "RGBCYM";
    char * secretStatic = "BYRM";
    srand(time(NULL));
    for (int i = 0; i < BOARD_WIDTH; i++) {
        //gameData->secretCode[i] = colors[rand() % strlen(colors)];
        gameData->secretCode[i] = secretStatic[i];
    }
    LOG(1, "Secret code created.\n");
    LOG(1, "Secret code : ");
    for (int i = 0; i < BOARD_WIDTH; i++) {
        LOG(1, "%c", gameData->secretCode[i]);
    }
    LOG(1, "\n");
}

void startGame(gameData_t *gameData) {
    LOG(1, "Starting game...\n");
    pthread_t threadClients[MAX_PLAYERS];
    clientThreadHandlerArgs_t clientThreadHandlerArgs[MAX_PLAYERS];
    
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        clientThreadHandlerArgs[i].gameData = gameData;
        clientThreadHandlerArgs[i].playerIndex = i;
        pthread_create(&threadClients[i], 
                        NULL, 
                        clientThreadHandler, 
                        &clientThreadHandlerArgs[i]);
        LOG(1, "Thread for player %d created.\n", i);
    }
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        pthread_join(threadClients[i], NULL);
    }
    LOG(1, "All players have ended their game.\n");
    
}

void checkChoice(gameData_t *gameData, int playerIndex) {
    LOG(1, "Checking player %d choice...\n", playerIndex);
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
            LOG(1, "Player %d color %c is at the right place.\n", playerIndex, player->board[player->nbRound][i]);
            LOG(1, "Player %d right place : %d.\n", playerIndex, player->result[player->nbRound][0]);
        }
    }
    for (int i = 0; i < 6; i++) {
        player->result[player->nbRound][1] += MIN(nbcolorsCombination[i], nbcolorsPlayer[i]);
        LOG(1, "Player %d right color : %d.\n", playerIndex, player->result[player->nbRound][1]);
    }
    player->result[player->nbRound][1] -= player->result[player->nbRound][0];
    if (player->result[player->nbRound][0] == BOARD_WIDTH) {
        gameData->gameWinner = playerIndex;
    }
    LOG(1, "Player %d choice checked.\n", playerIndex);
    LOG(1, "Player %d result : %d good place and %d good color.\n", playerIndex, player->result[player->nbRound][0], player->result[player->nbRound][1]);
}

void endGame(gameData_t *gameData) {
    LOG(1, "Ending game...\n");
    char buffer[10];
    for (int i = 0; i < gameData->playerList.nbPlayers; i++) {
        if (i == gameData->gameWinner) {
            strcpy(buffer, "win\0");
        } else {
            sprintf(buffer, "loose:%d", gameData->gameWinner);
        }
        sendData(&gameData->playerList.players[i].socket, buffer, 6);
        sendData(&gameData->playerList.players[i].socket, gameData->secretCode, 7);
    }
    LOG(1, "Winner is player %d.\n", gameData->gameWinner);
    LOG(1, "Result sent. Game ended.\n");

}


void *clientThreadHandler(void *args) {
    clientThreadHandlerArgs_t *clientThreadHandlerArgs = (clientThreadHandlerArgs_t *)args;
    while (clientThreadHandlerArgs->gameData->playerList.players[clientThreadHandlerArgs->playerIndex].nbRound < MAX_ROUND && clientThreadHandlerArgs->gameData->gameWinner == EMPTY) {
        getPlayerChoice(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        checkChoice(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        for (int i = 0; i < clientThreadHandlerArgs->gameData->playerList.nbPlayers; i++) {
            printf("result : %d %d\n", clientThreadHandlerArgs->gameData->playerList.players[i].result[clientThreadHandlerArgs->gameData->playerList.players[i].nbRound][0], clientThreadHandlerArgs->gameData->playerList.players[i].result[clientThreadHandlerArgs->gameData->playerList.players[i].nbRound][1]);
            printf("round : %d\n", clientThreadHandlerArgs->gameData->playerList.players[i].nbRound);
        }
        sendResult(clientThreadHandlerArgs->gameData, clientThreadHandlerArgs->playerIndex);
        clientThreadHandlerArgs->gameData->playerList.players[clientThreadHandlerArgs->playerIndex].nbRound++;
    }
    LOG(1, "Ending thread for player %d.\n", clientThreadHandlerArgs->playerIndex);
    pthread_exit(NULL);
}



    