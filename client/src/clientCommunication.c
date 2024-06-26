/**
 *	\file		clientCommunication.c
 *	\brief		Handles the client-side communication for the game.
 *
 *	\details	This file contains the functions necessary for the client-side communication of the game.
 *				It includes functions for connecting to the server, receiving game results, and fetching data from other clients.
 */


#include "clientCommunication.h"

/**
 *	\fn			void connectionWithServer(game_t *game)
 *	\brief		Establishes a connection with the server.
 *	\param 		game : The game structure that contains the game's state.
 *  \details    The player is prompted to enter the server's IP and port. If no input is given, default values are used. The player is then prompted to enter 'ready' to indicate that they are ready to play. The number of players and the player's index are then received from the server.
 */
void connexionWithServer(game_t *game) {

    char serverIp[17];
    char serverPortBuffer[7];
    int serverPort;
    char buffer[16];
    clear();
    echo();
    nocbreak();

    mvprintw(0, 0, "Enter the server IP : ");
    refresh();
    getstr(serverIp);
    if (strcmp(serverIp, "") == 0) strcpy(serverIp, SERVER_IP);  
    else if (strcmp(serverIp, "localhost") == 0) strcpy(serverIp, "127.0.0.1");
    //printf("serverIp : %s\n", serverIp);

    mvprintw(1, 0, "Enter the server port : ");
    refresh();
    getstr(serverPortBuffer);
    if (strcmp(serverPortBuffer, "") == 0) serverPort = SERVER_PORT;
    else serverPort = atoi(serverPortBuffer);
    //printf("serverPort : %d\n", serverPort);

    game->socket = connecterClt2Srv(serverIp, serverPort);

    mvprintw(3, 0, "You are connected to the server\n");
    mvprintw(4, 0, "Press the validation button when you are ready to play\n");
    refresh();
    while (readButton() != VALIDATION_BUTTON);

    mvprintw(5, 0, "You are ready to play\n");
    sendData(&(game->socket), "ready", 1);
    mvprintw(6, 0, "Waiting for other players...\n");
    refresh();
    receiveData(&(game->socket), buffer, 2);
    game->nbPlayers = buffer[0];
    receiveData(&(game->socket), buffer, 8);
    game->playerIndex = buffer[0];

    char * lcdMessage = malloc(50);
    sprintf(lcdMessage, "There are %d players in the game", game->nbPlayers);
    displayLcd(lcdMessage);
    free(lcdMessage);
    noecho();
    cbreak();
}

/**
 *	\fn			void sendCombination(game_t *game)
 *	\brief		Sends the player's color combination to the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\details    The player is prompted to enter a combination of colors. The combination is validated before being sent.
 */
void sendCombination(game_t *game) {

    unsigned char colors[] = "RGBCYM"; // Possible colors
    unsigned char playerCombination[BOARD_WIDTH + 1] = {-1, -1, -1, -1, -1};
    int pressedButton = -1;
    while (pressedButton != VALIDATION_BUTTON)
    {
        pressedButton = readButton();
        if (pressedButton < 4) {
            if (playerCombination[pressedButton] == 5) {
                playerCombination[pressedButton] = 0;
            } else {
                playerCombination[pressedButton]++;
            }
            game->board[game->nbRound][pressedButton] = (int) colors[playerCombination[pressedButton]];
            //showRow(game->board[game->nbRound], game->result[game->nbRound], game->nbRound);
            showGame(*game);
        }
        if (pressedButton == HELP_BUTTON) {
            showHelp();
            while (readButton() != HELP_BUTTON);
            showGame(*game);
        }
        if (pressedButton == VALIDATION_BUTTON) {
            for (int i = 0; i < BOARD_WIDTH; i++) {
                if (game->board[game->nbRound][i] == EMPTY) pressedButton = -1;
            }
        }
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        playerCombination[i] = game->board[game->nbRound][i];
    }
    playerCombination[BOARD_WIDTH] = '\0';
    sendData(&(game->socket), (char *) playerCombination, 3);
}

/**
 *	\fn			void getResult(game_t *game)
 *	\brief		Gets the result of the current round from the server.
 *	\param 		game : The game structure that contains the game's state.
 *  \details    The result of the current round is received from the server and stored in the game's result array.
 */
void getResult(game_t *game) {
    char buffer[RESULT_WIDTH + 1] = {0};
    receiveData(&(game->socket), buffer, 4);
    for (int i = 0; i < RESULT_WIDTH; i++) {
        game->result[game->nbRound][i] = buffer[i] - '0';
    }
}

/**
 *	\fn			void fetchOtherClientsData(game_t *game)
 *	\brief		Fetches data from other clients connected to the server.
 *	\param 		game : The game structure that contains the game's state.
 *	\details    The data of the other clients is received from the server and stored in the game's otherPlayers array.
 */
void fetchOtherClientsData(game_t *game) {
    char buffer[RESULT_WIDTH + 2];
    for (int i = 0; i < game->nbPlayers - 1; i++) {
        receiveData(&(game->socket), buffer, 5);
        game->otherPlayers[i].nbGoodPlace = buffer[0] - '0';
        game->otherPlayers[i].nbGoodColor = buffer[1] - '0';
        game->otherPlayers[i].nbRound = buffer[2] - '0';
    }
}


