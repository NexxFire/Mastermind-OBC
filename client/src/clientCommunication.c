#include "clientCommunication.h"


void connexionWithServer(game_t *game) {

    char serverIp[17];
    char serverPortBuffer[7];
    int serverPort;
    char buffer[16];
    char c;

    printf("Entrez l'adresse IP du serveur : ");
    fgets(serverIp, 17, stdin);
    if (strlen(serverIp) > 16) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
    if (strcmp(serverIp, "\n") == 0) {
        strcpy(serverIp, SERVER_IP);
    }
    
    printf("Entrez le port du serveur : ");
    fgets(serverPortBuffer, 7, stdin);
    printf("len : %ld\n", strlen(serverPortBuffer));
    if (strlen(serverPortBuffer) > 6) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    if (strcmp(serverPortBuffer, "\n") == 0) {
        serverPort = SERVER_PORT;
    } else {
        serverPort = atoi(serverPortBuffer);
        
    }
    
    game->socket = connecterClt2Srv(serverIp, serverPort);

    printf("Connected to the server\n");
    printf("type 'ready' when you are ready to play\n");
    do {
        fgets(buffer, 7, stdin);
        if (strlen(buffer) > 6) {
            while ((c = getchar()) != '\n' && c != EOF);
        }
        buffer[strlen(buffer) - 1] = '\0';
    } while (strcmp(buffer, "ready") != 0);
    printf("You are ready to play\n");
    envoyer(&(game->socket), "ready", NULL);
    printf("Waiting for other players to be ready...\n");
    recevoir(&(game->socket), &buffer, NULL);
    game->nbPlayers = buffer[0];
    printf("There are %d players in the game\n", game->nbPlayers);
    printf("Game is starting...\n");
    
}


