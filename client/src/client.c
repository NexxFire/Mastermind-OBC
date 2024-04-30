#include "client.h" // client/include/client.h
#include "communication.h" 
#include "data.h"

int main() {
    //game structure
    game_t game;
    connexionWithServer(&game); //send and receive data from server
    initGame(&game); //initialize game
    showGame(game); //show game

    while (1) {
    _sendCombination(&game); //send combination to server
    fetchOtherClientsData(&game); //fetch data from other clients
    }

    return 0;
}

void sendCombination(game_t *game) {

    char colors[] = "RGBCYM"; // Possible colors
    char playerCombination[BOARD_WIDTH + 1];

    printf("Welcome to the Mastermind game\n");
    printf("You have to guess a color combination. The possible colors are B, V, R, J, N, and O.\n");

    do {
        printf("Player, enter your guess > ");
        fgets
        if (strlen(playerCombination) != BOARD_WIDTH) {
            printf("Error: you must enter exactly 4 colors. Please try again.\n");
        }
    } while (strlen(playerCombination) != BOARD_WIDTH);

    envoyer(game->socket, playerCombination, NULL)




    return 0;
}

