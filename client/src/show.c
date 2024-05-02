#include "show.h" // client/include/show.h
#include <stdio.h> // printf

void showGame(game_t game) {
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
    else if (c == EMPTY_CASE) {
        printf(ANSI_BACKGROUND_WHITE"  "ANSI_RESET_ALL);
    }
    else if (c == EMPTY_SCORE) {
        printf(" ");
    }
    else {
        printf("%d", c);
    }
}