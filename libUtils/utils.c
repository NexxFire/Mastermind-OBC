#include "utils.h"



void getUserInput(char *buffer, size_t size) {
    fgets(buffer, size, stdin);
    if (strlen(buffer) == size - 1 && buffer[size - 2] != '\n') {
        clearBuffer();
    }
    strtok(buffer, "\n");
}

void clearBuffer () {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void sendData(socket_t *socket, char *data, int expectedCode) {
    char buffer[10];
    int receivedCode;
    envoyer(socket, data, NULL);
    recevoir(socket, buffer, NULL);
    sscanf(buffer, "ok:%d", &receivedCode);
    CHECK((receivedCode == expectedCode) -1, "Error: code received from server is not the expected one. Bad client-server synchronization.");
}

void receiveData(socket_t *socket, char *data, int validationCode) {
    char buffer[10];
    recevoir(socket, data, NULL);
    sprintf(buffer, "ok:%d", validationCode);
    envoyer(socket, buffer, NULL);
}