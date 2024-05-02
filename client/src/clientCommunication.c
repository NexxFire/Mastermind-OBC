#include "clientCommunication.h"


void connexionWithServer(game_t *game) {

    char serverIp[16];
    char serverPortBuffer[6];
    int serverPort;
    char buffer[16];

    printf("Entrez l'adresse IP du serveur : ");
    fgets(serverIp, 16, stdin);
    if (strcmp(serverIp, "\n") == 0) {
        strcpy(serverIp, SERVER_IP);
    }
    printf("Entrez le port du serveur : ");
    fgets(serverPortBuffer, 6, stdin);
    if (strcmp(serverPortBuffer, "\n") == 0) {
        serverPort = SERVER_PORT;
    } else {
        serverPort = atoi(serverPortBuffer);
    }
    game->socket = connecterClt2Srv(serverIp, serverPort);

    printf("Connected to the server\n");
    printf("type 'ready' when you are ready to play\n");
    do {
        fgets(buffer, 6, stdin);
        printf("buffer : %s\n", buffer);
    } while (strcmp(buffer, "ready") != 0);
    printf("You are ready to play\n");
    envoyer(&(game->socket), "ready", NULL);
}


