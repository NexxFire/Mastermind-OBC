#include "client.h"

int main() {
    game_t game;
    showMenu();
    connexionWithServer(&game);
    initGame(&game);
    showGame(game); 

    while (!isGameOver(game)){
        sendCombination(&game);
        getResult(&game);
        fetchOtherClientsData(&game);
        showGame(game); //show game
        game.nbRound++;
    }
    endGame(game); //end game

    return 0;
}

void sendCombination(game_t *game) {

    char colors[] = "RGBCYM"; // Possible colors
    char playerCombination[BOARD_WIDTH + 1];
    int validCombination = 0;

    do {
        validCombination = 1;
        printf("Player, enter your guess, possible colors are R, G, B, C, Y, and M > ");
        fgets(playerCombination, BOARD_WIDTH + 1, stdin);
        for (int i = 0; i < BOARD_WIDTH; i++) {
            playerCombination[i] = toupper(playerCombination[i]);
        }
        if (strlen(playerCombination) != BOARD_WIDTH) {
            printf("Error: you must enter exactly 4 colors. Please try again.\n");
            validCombination = 0;
        }
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (strchr(colors, playerCombination[i]) == NULL) {
                printf("Error: the color %c is not valid. Please try again.\n", playerCombination[i]);
                validCombination = 0;
                break;
            }
        }
    } while (!validCombination);
    
    for (int i = 0; i < BOARD_WIDTH; i++) {
        game->board[game->nbRound][i] = playerCombination[i];
    }

    envoyer(&(game->socket), playerCombination, NULL);

}

void getResult(game_t *game) {
    char buffer[RESULT_WIDTH + 1];
    recevoir(&(game->socket), buffer, NULL);
    for (int i = 0; i < RESULT_WIDTH; i++) {
        game->result[game->nbRound][i] = buffer[i];
    }
}

void fetchOtherClientsData(game_t *game) {
    char buffer[RESULT_WIDTH + 2];
    for (int i = 0; i < game->nbPlayers - 1; i++) {
        recevoir(&(game->socket), buffer, NULL);
        game->otherPlayers[i].nbGoodPlace = buffer[0];
        game->otherPlayers[i].nbGoodColor = buffer[1];
        game->otherPlayers[i].nbRound = buffer[2];
    }
}

int isGameOver(game_t game) {
    if (game.result[game.nbRound][0] == BOARD_WIDTH) {
        return 1;
    } else if (game.nbRound == MAX_ROUND) {
        return 1;
    } else {
        for (int i = 0; i < game.nbPlayers - 1; i++) {
            if (game.otherPlayers[i].nbGoodPlace == BOARD_WIDTH) {
                return 1;
            }
        }
    }
    return 0;
}

void endGame(game_t game) {
    char buffer[10];
    int winner = EMPTY;
    if (game.nbRound == MAX_ROUND) {
        printf("Waiting for other players to finish the game...\n");
    }
    recevoir(&(game.socket), buffer, NULL);
    if (strcmp(buffer, "win") == 0) {
        printf("Congratulations! You won the game!\n");
    } else {
        sscanf(buffer, "loose:%d", &winner);
        if (winner == EMPTY) {
            printf("Sorry, you lost the game. Nobody found the secret combination.\n");
        } else {
            printf("Sorry, you lost the game. The winner is player %d.\n", winner);
        }
    }
    recevoir(&(game.socket), buffer, NULL);
    printf("The secret combination was %s.\n", buffer);
}



