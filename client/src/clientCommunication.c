#include "clientCommunication.h"


void connexionWithServer(game_t *game) {

    char server_ip[16];
    int server_port;

    printf("Entrez l'adresse IP du serveur : ");
    scanf("%s", server_ip);
    printf("Entrez le port du serveur : ");
    scanf("%d", &server_port);

    game->socket = connecterClt2Srv(server_ip, server_port);
}


