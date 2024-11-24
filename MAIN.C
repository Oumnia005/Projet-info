#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "jeu.h"

// Dimensions du plateau
#define TAILLE 9

// Barrieres
#define MAX_BARRIERES 20

int main() {
    // Plateau de jeu (barrières)
    char plateau[TAILLE][TAILLE];
    char barriers_h[TAILLE - 1][TAILLE]; // Barrières horizontales
    char barriers_v[TAILLE][TAILLE - 1]; // Barrières verticales
    int nb_barrieres;
    int choix;
    int nj;
    Joueur joueurs[nj];

    do {
        system("cls");
        printf("        _________________________________________         \n");
        printf("       |                 -MENU-                  |       \n");
        printf("       |_________________________________________|        \n");
        printf("       |   1. LANCER UNE NOUVELLE PARTIE         |       \n");
        printf("       |   2. VOIR LES REGLES                    |       \n");
        printf("       |   3. REPRENDRE UNE PARTIE SAUVEGARDEE   |       \n");
        printf("       |   4. SCORES                             |       \n");
        printf("       |   5. QUITTER                            |       \n");
        printf("       |_________________________________________|       \n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nombre de joueurs (2 ou 4) : ");
                scanf("%d", &nj);
                if (nj != 2 && nj != 4) {
                    printf("Nombre de joueurs invalide ! Retour au menu.\n");
                    break;
                }
                lancerpartie(nj, plateau, joueurs);
                break;
            case 2:
                afficher_regles();
                break;
            case 3:
                anciennepartie(nj, plateau);
                break;
            case 4:
                printf("Les scores seront bientôt disponibles !\n");
                getchar();
                getchar();
                break;
            case 5:
                printf("Merci d'avoir joué !\n");
                exit(0);
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    } while (1);

    return 0;

}
