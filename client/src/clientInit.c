#include "clientInit.h" // client/include/init.h


void _initBoard(char board[MAX_ROUND][BOARD_WIDTH]) {
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void _initResult(char result[MAX_ROUND][RESULT_WIDTH]) {
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < RESULT_WIDTH; j++) {
            result[i][j] = EMPTY;
        }
    }
}

void _initOtherPlayers(otherPlayer_t otherPlayers[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        otherPlayers[i].nbRound = 0;
        otherPlayers[i].nbGoodPlace = 0;
        otherPlayers[i].nbGoodColor = 0;
    }
}



void initGame(game_t *game) {
    _initBoard(game->board);
    _initResult(game->result);
    _initOtherPlayers(game->otherPlayers);
}