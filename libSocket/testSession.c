#include "session.h"
#include "data.h"

#define PORT_SVC 5000
#define INADDR_SVC "127.0.0.1"

#define MSG "100:Je dis que \"le fond de l’eau est clair par ici ! Où ça ?\""
#define BYE "000:Au revoir et à bientôt ..."
#define ERR "200:Requête ou réponse non reconnue !"
#define OK "OK"
#define NOK "Not OK"

#define MAX_BUFF 1024
char buffer[MAX_BUFF];

int server();
int client();
void dialogueClt (socket_t sockDialogue);
void dialogueSrv (socket_t sockDialogue);



void serialize(void *sock, void *buffer) {
    socket_t *sock_cast = (socket_t *)sock;
    char *buffer_cast = (char *)buffer;
    sprintf(buffer_cast, "%d,%d", sock_cast->fd, sock_cast->mode);
}



int main() {
    #ifdef SERVER
    return server();
    #else
    return client();
    #endif
}


int server() {
    
    socket_t sockEcoute = creerSocketEcoute(INADDR_SVC, PORT_SVC);
    printf("Socket d'écoute créée\n");
    
    // Boucle permanente de service
    while (1) {
        // Attente d’un appel
        socket_t sockDialogue = accepterClt(sockEcoute);
        printf("Client connecté\n");

        // Dialogue avec le client
        dialogueClt (sockDialogue);
        close(sockDialogue.fd);
    }
    
    close(sockEcoute.fd);
    return 0;
}


void dialogueClt (socket_t sockDialogue) {
    char requete[MAX_BUFF];
    do {
        recevoir(&sockDialogue, buffer, NULL);
        sscanf(buffer, "%s:%s",requete, buffer);
        switch (atoi(requete)) {
            case 0 : 
                printf("Au revoir\n"); 
                break;

            case 100 : 
                envoyer(&sockDialogue, OK, NULL);
                printf("OK : message recu %s\n ", buffer); 
                break;

            default : 
                envoyer(&sockDialogue, NOK, NULL);
                printf("NOK : message recu %s\n", buffer); 
                break;
        }
    } while ( atoi(requete) != 0);
}


int client() {
    int sock;
    struct sockaddr_in svc;

    // Création de la socket d’appel et de dialogue
    socket_t sockDialogue = connecterClt2Srv(INADDR_SVC, PORT_SVC);

    // Dialogue avec le serveur
    dialogueSrv (sockDialogue);
    close(sock);
    return 0;
}


void dialogueSrv (socket_t sockDialogue) {
    char reponse[MAX_BUFF];

    // Envoi du message MSG au serveur : la réponse sera OK
    char *buffer[MAX_BUFF];
    serialize(&sockDialogue, buffer);
    printf("Buffer [%s]\n", buffer);
    envoyer(&sockDialogue, &sockDialogue, serialize);


    envoyer(&sockDialogue, MSG, NULL);
    recevoir(&sockDialogue, reponse, NULL);
    printf("Message reçu [%s]\n", reponse);

    // Envoi du message ERR au serveur : la réponse sera NOK
    envoyer(&sockDialogue, ERR, NULL);
    recevoir(&sockDialogue, reponse, NULL);
    printf("Message reçu [%s]\n", reponse);

    // Envoi du message BYE au serveur : la réponse sera la fin du dialogue
    envoyer(&sockDialogue, BYE, NULL);
    //CHECK(read(sd, reponse, sizeof(reponse)), "Can't send");
}

