#include "show.h" // client/include/show.h
#include <stdio.h> // printf

void showGame(game_t game) {
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            
            printf("%c ", game.board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < RESULT_WIDTH; j++) {
            printf("%c ", game.result[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("Player %d\n", i);
        printf("Round: %d\n", game.otherPlayers[i].nbRound);
        printf("Good place: %d\n", game.otherPlayers[i].nbGoodPlace);
        printf("Good color: %d\n", game.otherPlayers[i].nbGoodColor);
        printf("\n");
    }
}

void showChar(char c) {
    if (c == 'R') {
        printf(ANSI_BACKGROUND_RED"  "ANSI_RESET_ALL);
    }
    if (c == 'G') {
        printf(ANSI_BACKGROUND_GREEN"  "ANSI_RESET_ALL);
    }
    if (c == 'B') {
        printf(ANSI_BACKGROUND_BLUE"  "ANSI_RESET_ALL);
    }
    if (c == 'Y') {
        printf(ANSI_BACKGROUND_YELLOW"  "ANSI_RESET_ALL);
    }
    if (c == 'C') {
        printf(ANSI_BACKGROUND_CYAN"  "ANSI_RESET_ALL);
    }
    if (c == 'M') {
        printf(ANSI_BACKGROUND_MAGENTA"  "ANSI_RESET_ALL);
    }
    if (c == EMPTY) {
        printf("  ");
    }
}