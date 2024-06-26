/**
 *	\file		clientShow.c
 *	\brief		Handles the display of the game state for the client.
 *
 *	\details	This file contains the functions necessary for displaying the game state on the client side.
 */
#include "clientShow.h" // client/include/show.h

void initialize_ncurses() {
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();
    // Define background color
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    // Define text color
    init_pair(8, COLOR_RED, -1);
    init_pair(9, COLOR_GREEN, -1);
    init_pair(10, COLOR_BLUE, -1);
    init_pair(11, COLOR_YELLOW, -1);
    init_pair(12, COLOR_CYAN, -1);
    init_pair(13, COLOR_MAGENTA, -1);
    init_pair(14, COLOR_WHITE, -1);
}

void finalize_ncurses() {
    endwin();
}

void showMenu() {
    clear();
    mvprintw(0, 0, "Welcome to Mastermind!");
    mvprintw(0, 0, "Welcome to the Mastermind contest");
    mvprintw(1, 0, "This is a Mastermind game with multiple players.");
    mvprintw(2, 0, "You have to guess a color combination. The possible colors are R, G, B, C, Y, and M.");
    mvprintw(3, 0, "You have %d rounds to find the combination.", MAX_ROUND);
    mvprintw(4, 0, "The first to find the combination win. Good luck!\n\n");
    mvprintw(5, 0, "Press the help (Down-Left on matrix) button to show help for rules and how to play.");
    mvprintw(6, 0, "Press the validation (Down-Right on matrix) button to start the game.");
    refresh();
    int read = readButton();
    while (read != VALIDATION_BUTTON) {
        printf("Button pressed: %d\n", read);
        read = readButton();
    }
    
}

void showHelp() {
    clear();
    mvprintw(0, 0, "Rules:");
    mvprintw(1, 0, "The game is played with 1 to 4 players.");
    mvprintw(2, 0, "Each player has to guess a color combination.");
    mvprintw(3, 0, "The possible colors are R, G, B, C, Y, and M.");
    mvprintw(4, 0, "The first player to find the combination wins.");
    mvprintw(5, 0, "Each player has %d rounds to find the combination.", MAX_ROUND);
    mvprintw(6, 0, "A color can be used multiple times in the combination.");

    mvprintw(8, 0, "How to play:");
    mvprintw(9, 0, "Use the Down-Right button on the matrix to validate any interaction.");
    mvprintw(10, 0, "Use the Down-Left buttonon the matrix to show this help.");
    mvprintw(11, 0, "Use the first 4 button of the Matrix to change the color in the current row.");
    
    mvprintw(13, 0, "Press the help button again to exit the help and go back to game.");
    refresh();
}

void showGame(game_t game) {
    clear();
    showBoard(game);
    for(int i = 0; i < MAX_ROUND; i++) {
        showRow(game.board[MAX_ROUND - i - 1], game.result[MAX_ROUND - i - 1], MAX_ROUND - i - 1);
    }
    for (int i = 0, j = 0; i < game.nbPlayers; i++) {
        if (game.playerIndex != i) {
            showOtherUser(game.otherPlayers[j].nbRound, game.otherPlayers[j].nbGoodPlace, game.otherPlayers[j].nbGoodColor, STARTY + 6*(j + 1), STARTX + WIDTH + 14);
            j++;
        }
    }

    displayCharMatrix(game.playerIndex + 1 + '0');
    
    if (game.nbRound > 0) {
        displayDigit(DIGIT_1, segment_value[game.result[game.nbRound - 1][0]]);
        displayColon(COLON_ON);
        displayDigit(DIGIT_4, segment_value[game.result[game.nbRound - 1][1]]);    
    }
    

    refresh();
}

void showBoard(game_t game) {
    attron(COLOR_PAIR(9));
    mvprintw(STARTY + 2, STARTX - 28, "Good color, good place");
    attroff(COLOR_PAIR(9));
    attron(COLOR_PAIR(11));
    mvprintw(STARTY + 2, STARTX + WIDTH + 5, "Good color, wrong place");
    attroff(COLOR_PAIR(11));
    mvprintw(STARTY - 1, STARTX + (WIDTH-8)/2, "Player %d", game.playerIndex + 1);
    mvprintw(STARTY, STARTX, "┌───┬─────────────┬───┐");
    for (int i = 0; i < HEIGHT - 2; i++) {
        mvprintw(STARTY + i + 1, STARTX, "│   │             │   │");
    }
    mvprintw(STARTY + HEIGHT -1, STARTX, "└───┴─────────────┴───┘");

    // Printing other players
    for (int i = 0, j = 0; i < game.nbPlayers; i++) {
        if (game.playerIndex != i) {
            mvprintw(STARTY + 6*(j + 1), STARTX + WIDTH + 10, "Player %d", i + 1);
            mvprintw(STARTY + 6*(j + 1) + 1, STARTX + WIDTH + 14, "Round: ");
            attron(COLOR_PAIR(9));
            mvprintw(STARTY + 6*(j + 1) + 2, STARTX + WIDTH + 14, "Good color, good place:");
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(11));
            mvprintw(STARTY + 6*(j + 1) + 3, STARTX + WIDTH + 14, "Good color, wrong place:");
            attroff(COLOR_PAIR(4));
            j++;
        }
    }
    refresh();
}

void showRow(signed char row[BOARD_WIDTH], signed char result[RESULT_WIDTH], int round) {
    round = MAX_ROUND - round - 1;
    showChar(result[0], STARTY + (round)*2 + 1, STARTX + 2);
    for (int j = 0; j < BOARD_WIDTH; j++) {
        showChar(row[j], STARTY + round*2 + 1, STARTX + 5 + j * 3 + 1);
    }
    showChar(result[1], STARTY + round*2 + 1, STARTX + 5 + BOARD_WIDTH * 3 + 3);
}

void showOtherUser(int round, int goodPlace, int goodColor, int starty, int startx) {
    mvprintw(starty + 1, startx + 7, "%d", round);
    attron(COLOR_PAIR(9));
    mvprintw(starty + 2, startx + 24, "%d", goodPlace);
    attroff(COLOR_PAIR(9));
    attron(COLOR_PAIR(11));
    mvprintw(starty + 3, startx + 25, "%d", goodColor);
    attroff(COLOR_PAIR(11));
}


void showChar(signed char c, int y, int x) {
    if (c == 'R') {
        attron(COLOR_PAIR(1));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(1));
    }
    else if (c == 'G') {
        attron(COLOR_PAIR(2));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(2));
    }
    else if (c == 'B') {
        attron(COLOR_PAIR(3));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(3));
    }
    else if (c == 'Y') {
        attron(COLOR_PAIR(4));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(4));
    }
    else if (c == 'C') {
        attron(COLOR_PAIR(5));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(5));
    }
    else if (c == 'M') {
        attron(COLOR_PAIR(6));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(6));
    }
    else if (c == EMPTY) {
        attron(COLOR_PAIR(7));
        mvprintw(y, x, "  ");
        attroff(COLOR_PAIR(7));
    }
    else if (c == EMPTY_SCORE) {
        mvprintw(y, x, " ");
    }
    else {
        mvprintw(y, x, "%d", c);
    }
}

void showEndGame(game_t game) {
    clear();
    char buffer[10];
    int winner = EMPTY;
    if (game.nbRound == MAX_ROUND) {
        mvprintw(0, 0, "Waiting for other players to finish the game...\n");
    }
    else {
        mvprintw(0, 0, "You found the secret combination in %d rounds!\n", game.nbRound);
        mvprintw(1, 0, "Waiting for other players to finish the game...\n");
    }
    refresh();
    receiveData(&(game.socket), buffer, 6);
    if (strcmp(buffer, "win") == 0) {
        winner = game.playerIndex;
        mvprintw(3, 0, "Congradulation, you won the game!\n");
        displayScrollTextMatrix("Winner");
        displayLcd("Congradulation, you won the game");
    } else {
        sscanf(buffer, "loose:%d", &winner);
        mvprintw(3, 0, "Sorry, player %d won the game.\n", winner + 1);
        displayScrollTextMatrix("Looser");
        displayLcd("Sorry, player %d won the game");
    }
    receiveData(&(game.socket), buffer, 7);
    mvprintw(4, 0, "The secret combination was: %s\n", buffer);

}