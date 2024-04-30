#include "client.h" // client/include/client.h
#include "communication.h" 

int main() {
    //game structure
    game_t game;
    connexionWithServer(&game); //send and receive data from server
    initGame(&game); //initialize game
    showGame(game); //show game

    while (1) {
    _sendCombination(&game); //send combination to server
    fetchOtherClientsData(&game); //fetch data from other clients
    }

    return 0;
}

sendCombination(game_t *game) {

    char colors[] = "BVRJNO"; // Possible colors
    char secretCombination[COMBINATION_LENGTH + 1]; // Secret combination
    char player1Guess[COMBINATION_LENGTH + 1];
    char player2Guess[COMBINATION_LENGTH + 1];
    int attempt, correctColors, correctPositions;

    srand(time(NULL)); // Initialize the random number generator

    char colors[] = "BVRJNO"; // Possible colors
    char secretCombination[COMBINATION_LENGTH + 1]; // Secret combination
    char player[COMBINATION_LENGTH + 1];
    int attempt, correctColors, correctPositions;

    srand(time(NULL)); // Initialize the random number generator

    // Generate a random secret combination
    for (int i = 0; i < COMBINATION_LENGTH; i++) {
        secretCombination[i] = colors[rand() % strlen(colors)];
    }
    secretCombination[COMBINATION_LENGTH] = '\0'; // Add the end of string character
    printf("The secret combination is %s\n", secretCombination); // Display the secret combination (for testing)

    printf("Welcome to the Mastermind game\n");
    printf("You have to guess a color combination. The possible colors are B, V, R, J, N, and O.\n");

    for (attempt = 0; attempt < NBATTEMPTS; attempt++) {

        do {
            printf("Player, enter your guess: ");
            scanf("%s", player);
            if (strlen(player) != COMBINATION_LENGTH) {
                printf("Error: you must enter exactly 4 colors. Please try again.\n");
            }
        } while (strlen(player) != COMBINATION_LENGTH);

        compareCombinations(secretCombination, player, &correctColors, &correctPositions);
        printf("Player, you have %d correct color(s) and %d correct position(s)\n", correctColors, correctPositions);

        if (correctColors == COMBINATION_LENGTH) {
            printf("Congratulations Player, you found the secret combination in %d attempts\n", attempt + 1);
            break;
        }

    }

    if (attempt == NBATTEMPTS) {
        printf("Sorry, you have exhausted your %d attempts\n", NBATTEMPTS);
    }

    return 0;

}

