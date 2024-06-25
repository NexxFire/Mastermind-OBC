/**
 *	\file		client.c
 *	\brief		Handles the main game loop for the client.
 *
 *	\details	This file contains the main game loop and the functions for checking if the game is over and ending the game.
 */
#include "client.h"

/**
 *	\fn			int main()
 *	\brief		The main game loop.
 *	\details    Shows the menu, initializes the game, connects to the server, and then enters the main game loop. The main game loop consists of sending the player's combination to the server, receiving the result of the combination, fetching the data of the other players, and showing the game state. The loop continues until the game is over.    
 */
int main() {
    game_t game;
    initGame(&game);
    showMenu();
    connexionWithServer(&game);
    showGame(game); 
    while (!isGameOver(game)){
        sendCombination(&game);
        getResult(&game);
        fetchOtherClientsData(&game);
        showGame(game); //show game
        game.nbRound++;
    }
    showEndGame(game); //end game
    finalize_ncurses();

    return 0;
}

/**
 *	\fn			int isGameOver(game_t game)
 *	\brief		Checks if the game is over.
 *	\param 		game : The game state.
 *	\details		Returns 1 if the game is over (either the player has found the secret combination, the maximum number of rounds has been reached, or another player has found the secret combination), and 0 otherwise.
 */
int isGameOver(game_t game) {
    if (game.result[game.nbRound - 1][0] == BOARD_WIDTH) {
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



