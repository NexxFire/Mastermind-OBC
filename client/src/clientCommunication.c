#include "clientCommunication.h"


void connexionWithServer(game_t *game) {

    char serverIp[17];
    char serverPortBuffer[7];
    int serverPort;
    char buffer[16];

    printf("Entrez l'adresse IP du serveur : ");
    getUserInput(serverIp, sizeof(serverIp));
    if (strcmp(serverIp, "\n") == 0) {
        strcpy(serverIp, SERVER_IP);
    }

    printf("Entrez le port du serveur : ");
    getUserInput(serverPortBuffer, sizeof(serverPortBuffer));
    if (strcmp(serverPortBuffer, "\n") == 0) {
        serverPort = SERVER_PORT;
    } else {
        serverPort = atoi(serverPortBuffer);
    }
    
    game->socket = connecterClt2Srv(serverIp, serverPort);

    printf("Connected to the server\n");
    printf("type 'ready' when you are ready to play\n");
    do {
        getUserInput(buffer, sizeof(buffer));
    } while (strcmp(buffer, "ready") != 0);
    printf("You are ready to play\n");
    sendData(&(game->socket), "ready", 1);
    printf("Waiting for other players to be ready...\n");
    receiveData(&(game->socket), buffer, 2);
    game->nbPlayers = buffer[0];
    printf("\nThere are %d players in the game\n", game->nbPlayers);
    receiveData(&(game->socket), buffer, 8);
    game->playerIndex = buffer[0];
    printf("You are player %d\n", game->playerIndex +1);
    printf("Game is starting...\n");
    
}


void getResult(game_t *game) {
    char buffer[RESULT_WIDTH + 1] = {0};
    receiveData(&(game->socket), buffer, 4);
    for (int i = 0; i < RESULT_WIDTH; i++) {
        game->result[game->nbRound][i] = buffer[i] - '0';
    }
}

void fetchOtherClientsData(game_t *game) {
    char buffer[RESULT_WIDTH + 2];
    for (int i = 0; i < game->nbPlayers - 1; i++) {
        receiveData(&(game->socket), buffer, 5);
        game->otherPlayers[i].nbGoodPlace = buffer[0] - '0';
        game->otherPlayers[i].nbGoodColor = buffer[1] - '0';
        game->otherPlayers[i].nbRound = buffer[2] - '0';
    }
}


