//
//CREATION D UN MASTERMIND
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NBESSAIS 5
#define COMBINAISON_LENGTH 4

void comparerCombinaisons(const char* combinaisonSecrete, const char* propositionJoueur, int* bonnesCouleurs, int* bonnesPositions) {
    *bonnesCouleurs = 0;
    *bonnesPositions = 0;
    int positionCorrecte[COMBINAISON_LENGTH] = {0};
    int couleurComptee[COMBINAISON_LENGTH] = {0};

    // Vérifier si une couleur est à la bonne position
    for (int i = 0; i < COMBINAISON_LENGTH; i++) {
        if (propositionJoueur[i] == combinaisonSecrete[i]) {
            (*bonnesPositions)++;
            positionCorrecte[i] = 1;
            couleurComptee[i] = 1;
        }
    }

    // Vérifier si une couleur est présente dans la combinaison secrète
    for (int i = 0; i < COMBINAISON_LENGTH; i++) {
        if (!positionCorrecte[i] && strchr(combinaisonSecrete, propositionJoueur[i]) != NULL) {
            int dejaComptee = 0;
            for (int j = 0; j < COMBINAISON_LENGTH; j++) {
                if (propositionJoueur[i] == combinaisonSecrete[j] && couleurComptee[j]) {
                    dejaComptee = 1;
                    break;
                }
            }
            if (!dejaComptee) {
                (*bonnesCouleurs)++;
                couleurComptee[i] = 1;
            }
        }
    }
}

int main() {
    char couleurs[] = "BVRJNO"; // Les couleurs possibles
    char combinaisonSecrete[COMBINAISON_LENGTH + 1]; // Combinaison secrète
    char propositionJoueur1[COMBINAISON_LENGTH + 1];
    char propositionJoueur2[COMBINAISON_LENGTH + 1];
    int essai, bonnesCouleurs, bonnesPositions;

    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    // Générer une combinaison secrète aléatoire
    for (int i = 0; i < COMBINAISON_LENGTH; i++) {
        combinaisonSecrete[i] = couleurs[rand() % strlen(couleurs)];
    }
    combinaisonSecrete[COMBINAISON_LENGTH] = '\0'; // Ajouter le caractère de fin de chaîne
    printf("La combinaison secrète est %s\n", combinaisonSecrete); // Afficher la combinaison secrète (pour les tests

    printf("Bienvenue dans le jeu du Mastermind\n");
    printf("Vous devez deviner une combinaison de couleurs. Les couleurs possibles sont B, V, R, J, N, et O.\n");

    for (essai = 0; essai < NBESSAIS; essai++) {
        do {
            printf("Joueur 1, entrez votre proposition : ");
            scanf("%s", propositionJoueur1);
            if (strlen(propositionJoueur1) != COMBINAISON_LENGTH) {
                printf("Erreur : vous devez entrer exactement 4 couleurs. Veuillez réessayer.\n");
            }
        } while (strlen(propositionJoueur1) != COMBINAISON_LENGTH);

        comparerCombinaisons(combinaisonSecrete, propositionJoueur1, &bonnesCouleurs, &bonnesPositions);
        printf("Joueur 1, vous avez %d bonne(s) couleur(s) et %d  bonne(s) position(s)\n", bonnesCouleurs, bonnesPositions);

        if (bonnesCouleurs == COMBINAISON_LENGTH) {
            printf("Bravo Joueur 1, vous avez trouvé la combinaison secrète en %d essais\n", essai + 1);
            break;
        }

        do {
            printf("Joueur 2, entrez votre proposition : ");
            scanf("%s", propositionJoueur2);
            if (strlen(propositionJoueur2) != COMBINAISON_LENGTH) {
                printf("Erreur : vous devez entrer exactement 4 couleurs. Veuillez réessayer.\n");
            }
        } while (strlen(propositionJoueur2) != COMBINAISON_LENGTH);

        comparerCombinaisons(combinaisonSecrete, propositionJoueur2, &bonnesCouleurs, &bonnesPositions);
        printf("Joueur 2, vous avez %d bonne(s) couleur(s) et %d  bonne(s) position(s)\n", bonnesCouleurs, bonnesPositions);

        if (bonnesCouleurs == COMBINAISON_LENGTH) {
            printf("Bravo Joueur 2, vous avez trouvé la combinaison secrète en %d essais\n", essai + 1);
            break;
        }
    }

    if (essai == NBESSAIS) {
        printf("Désolé, vous avez épuisé vos %d essais\n", NBESSAIS);
    }

    return 0;
}