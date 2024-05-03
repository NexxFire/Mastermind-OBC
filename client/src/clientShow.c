#include "clientShow.h" // client/include/show.h

void showMenu() {
    printf("Welcome to the Mastermind contest\n");
    printf("This is a Mastermind game with multiple players.\n");
    printf("You have to guess a color combination. The possible colors are R, G, B, C, Y, and M.\n");
    printf("You have %d rounds to find the combination.\n", MAX_ROUND);
    printf("The first to find the combination win. Good luck!\n\n");
}


void showGame(game_t game) {

    printf("\n\n\n\tPlayer %d\n", game.playerIndex+1);
    printf("┌───┬─────────────┬───┐\n");
    for (int i = 0; i < MAX_ROUND; i++) {
        printf("│");
        printf(" ");
        showChar(game.result[MAX_ROUND - i-1][0]);
        printf(" ");
        printf("│");
        printf(" ");
        for (int j = 0; j < BOARD_WIDTH; j++) {
            
            showChar(game.board[MAX_ROUND - i-1][j]);
            printf(" ");
        }
        printf("│");
        printf(" ");
        showChar(game.result[MAX_ROUND - i-1][1]);
        printf(" ");
        printf("│\n");
        if (i < MAX_ROUND-1) {
            printf("│   │             │   │\n");
        }
    }
    printf("└───┴─────────────┴───┘\n");
    printf("\tRound: %d\n\n", game.nbRound);
    for (int i = 0, j = 0; i < game.nbPlayers; i++) {
        if (game.playerIndex != i) {
            printf("Player %d\n", i+1);
            printf("\tRound: %d\n", game.otherPlayers[j].nbRound);
            printf(ANSI_COLOR_GREEN"\tGood place: %d\n"ANSI_RESET_ALL, game.otherPlayers[j].nbGoodPlace);
            printf(ANSI_COLOR_YELLOW"\tGood color: %d\n\n"ANSI_RESET_ALL, game.otherPlayers[j].nbGoodColor);
            printf("\n");
            j++;
        }
    }
}

void showChar(char c) {
    if (c == 'R') {
        printf(ANSI_BACKGROUND_RED"  "ANSI_RESET_ALL);
    }
    else if (c == 'G') {
        printf(ANSI_BACKGROUND_GREEN"  "ANSI_RESET_ALL);
    }
    else if (c == 'B') {
        printf(ANSI_BACKGROUND_BLUE"  "ANSI_RESET_ALL);
    }
    else if (c == 'Y') {
        printf(ANSI_BACKGROUND_YELLOW"  "ANSI_RESET_ALL);
    }
    else if (c == 'C') {
        printf(ANSI_BACKGROUND_CYAN"  "ANSI_RESET_ALL);
    }
    else if (c == 'M') {
        printf(ANSI_BACKGROUND_MAGENTA"  "ANSI_RESET_ALL);
    }
    else if (c == EMPTY) {
        printf(ANSI_BACKGROUND_WHITE"  "ANSI_RESET_ALL);
    }
    else if (c == EMPTY_SCORE) {
        printf(" ");
    }
    else {
        printf("%d", c);
    }
}