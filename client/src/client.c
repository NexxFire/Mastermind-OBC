#include "client.h"

int main() {
    //game structure
    game_t game;
    connexionWithServer(&game); //send and receive data from server
    initGame(&game); //initialize game
    showGame(game); //show game

    while (1) {
        sendCombination(&game); //send combination to server
        fetchOtherClientsData(&game); //fetch data from other clients
    }

    return 0;
}

void sendCombination(game_t *game) {

    char colors[] = "RGBCYM"; // Possible colors
    char playerCombination[BOARD_WIDTH + 1];
    int validCombination = 0;

    printf("Welcome to the Mastermind game\n");
    printf("You have to guess a color combination. The possible colors are B, V, R, J, N, and O.\n");

    do {
        validCombination = 1;
        printf("Player, enter your guess > ");
        fgets(playerCombination, BOARD_WIDTH + 1, stdin);
        if (strlen(playerCombination) != BOARD_WIDTH) {
            printf("Error: you must enter exactly 4 colors. Please try again.\n");
        }
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (strchr(colors, playerCombination[i]) == NULL) {
                printf("Error: the color %c is not valid. Please try again.\n", playerCombination[i]);
                validCombination = 0;
                break;
            }
        }
    } while (!validCombination);

    envoyer(&(game->socket), playerCombination, NULL);

}

