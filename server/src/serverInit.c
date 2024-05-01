#include "serverInit.h"

void serverInit(gameData_t *gameData) {
    gameData->playerList.nbPlayers = 0;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        _playerInit(&gameData->playerList.players[i]);
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        gameData->secretCode[i] = EMPTY;
    }
    
}


void _playerInit(player_t *player) {
    player->ready = 0;
    for (int i = 0; i < MAX_ROUND; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            player->board[i][j] = EMPTY;
        }
        for (int j = 0; j < RESULT_WIDTH; j++) {
            player->result[i][j] = EMPTY;
        }
    }
}