#include "server.h"


void main() {
    gameData_t gameData;
    
    while (1) {
        serverInit(&gameData);
        clientRegistration(&gameData);
        startGame(&gameData);
        endGame(&gameData);
    }
}


    