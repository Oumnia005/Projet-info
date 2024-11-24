#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jeu.h"

// Dimensions du plateau
#define TAILLE 9

// Barrieres
#define MAX_BARRIERES 20
#include "menu.h"

// Affiche les règles
void afficher_regles() {
    system("cls");
    printf("   ______________________________________________________________________         \n");
    printf("  |                                                                      |        \n");
    printf("  |                            |REGLES DU JEU|                           |        \n");
    printf("  |______________________________________________________________________|        \n");
    printf("  |                                                                      |        \n");
    printf("  |                            --BUT DU JEU--                            |        \n");
    printf("  |                                                                      |        \n");
    printf("  |             Deux modes de jeu possibles : 2 ou 4 joueurs.            |        \n");
    printf("  |  Etre le premier a atteindre la ligne opposee depuis sa ligne de     |        \n");
    printf("  |  depart.                                                             |        \n");
    printf("  |     Un tirage au sort de facon aleatoire determine qui commence.     |        \n");
    printf("  |    Les barrieres sont reparties equitablement entre les joueurs.     |        \n");
    printf("  |        Pour 2 joueurs : chaque joueur dispose de 10 barrieres        |        \n");
    printf("  |        Pour 4 joueurs : chaque joueur dispose de 5 barrieres         |        \n");
    printf("  |                                                                      |        \n");
    printf("  |                                                                      |        \n");
    printf("  |                           --DEPLACEMENTS--                           |        \n");
    printf("  |                                                                      |        \n");
    printf("  |                A tour de role chaque joueur choisi de :              |        \n");
    printf("  |  1) Deplacer son pion d'une case (Gauche/Droite/Devant/Derriere)     |        \n");
    printf("  |  2) Poser une de ses barrieres. Une barriere doit etre posee entre 2 |        \n");
    printf("  |   blocs de 2 cases. Lorsqu'il n'a plus de barrieres, un joueur est   |        \n");
    printf("  |                     oblige de deplacer son pion.                     |        \n");
    printf("  |  => Objectif : creer son propre chemin ou ralentir son adversaire    |        \n");
    printf("  |                                                                      |        \n");
    printf("  |                          --SPECIFICATIONS--                          |        \n");
    printf("  |                                                                      |        \n");
    printf("  |         /!\\  Interdiction de fermer totalement l'acces  /!\\          |      \n");
    printf("  |  Si 2 pions se retrouvent face a face le joueur a le droit de sauter |        \n");
    printf("  |                      par dessus sont adversaire.                     |        \n");
    printf("  |  Si une barriere se trouve derrière le pion saute, le joueur peut   |        \n");
    printf("  |       se deplacer sur le cote droit ou gauche du pion saute.         |        \n");
    printf("  |______________________________________________________________________|      \n\n");
    printf("APPUYEZ SUR ENTREE POUR RETOURNER AU MENU");
    getchar();
    getchar();
}

void lancerpartie(int nj, char plateau[TAILLE][TAILLE], Joueur joueurs[]) {
    initialiserjoueurs(nj, joueurs);
    initialiserplateau(nj, plateau, joueurs);
    // Initialisation du générateur aléatoire
    srand(time(NULL));

    // Sélection du joueur de départ
    int tour = rand() % nj; // Numéro aléatoire entre 0 et nb_joueurs - 1

    while (1) {
        afficherplateau(plateau);

        // Vérifie la victoire
        if (verifvictoire(joueurs[tour], nj)) {
            printf("\nLe joueur %s a remporte la partie !\n", joueurs[tour-1].nom);
            getchar();
            getchar();
            break;
        }

        printf("\n %s, Que vous voulez faire:\n ", joueurs[tour].nom);
        printf("1.Bouger mon pion\n");
        printf(" 2.Poser une barriere (%d barrieres restantes)\n", joueurs[tour].nb_barrieres_restantes);
        printf(" 3.Passer mon tour\n");
        printf(" 4.Annuler le dernier tour\n");
        printf(" 5.Retour au menu\n");
        int choix;
        char commande;
        scanf(" %d", &choix);

        switch (choix) {
            case 1:
                printf("Quelle direction ?(h/b/g/d)");
                scanf(" %c", &commande);
                if (!deplacer_joueur(&joueurs[tour], commande, plateau, nj)) {
                    printf("Déplacement invalide !\n");
                    continue;
                }

                tour = (tour + 1) % nj; // Tour suivant
                break;
            case 2:
                if (!poser_barriere(&joueurs[tour], plateau)) {
                    continue;
                }
                tour = (tour + 1) % nj;
                break;
            case 3:
                tour = (tour + 1) % nj;
                break;
            case 4:
                printf("Pas encore codé");
                break;
            case 5:
                enregistrement(nj);
                system("cls");
            default:
                printf("Veuillez choisir un des numero proposes");
            break;
        }

    }
}

// Fonction pour vérifier si un symbole est unique
bool symbole_unique(char pion, int index, Joueur joueurs[]) {
    for (int i = 0; i < index; i++) {
        if (joueurs[i].pion == pion) {
            return false;
        }
    }
    return true;
}

// Affiche le plateau
void afficherplateau(char plateau[TAILLE][TAILLE]) {
    system("cls");
    printf("\n");

    // Affichage du plateau avec les barrières
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < TAILLE; j++) {
            printf("|");
            if (plateau[i][j] != ' ') {
                printf(" %c ", plateau[i][j]);
            } else {
                printf("   ");
            }
        }
        printf("|\n");
    }

    for (int j = 0; j < TAILLE; j++) {
        printf("+---");
    }
    printf("+\n");
}




// Initialisation des joueurs
void initialiserjoueurs(int nj, Joueur joueurs[]) {
    for (int i = 0; i < nj; i++) {
        printf("Joueur %d, entrez votre nom : ", i + 1);
        scanf("%s", joueurs[i].nom);

        char pion;
        do {
            printf("Joueur %s, choisissez un symbole unique pour votre pion : ", joueurs[i].nom);
            scanf(" %c", &pion);

            if (!symbole_unique(pion, i, joueurs)) {
                printf("Ce symbole est déjà utilisé. Choisissez-en un autre.\n");
            } else {
                joueurs[i].pion = pion; // Affecte le symbole au joueur
            }
            joueurs[i].nb_barrieres_restantes = MAX_BARRIERES / nj; // Répartition équitable
        } while (!symbole_unique(pion, i, joueurs));
    }
}

// Initialise le plateau
void initialiserplateau(int nj,char plateau[TAILLE][TAILLE], Joueur joueurs[]) {
    // Réinitialise le plateau
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j] = ' ';
        }
    }

    // Initialise les positions des joueurs et place leurs symboles
    joueurs[0].x = 0;
    joueurs[0].y = TAILLE / 2;
    plateau[joueurs[0].x][joueurs[0].y] = joueurs[0].pion;

    joueurs[1].x = TAILLE - 1;
    joueurs[1].y = TAILLE / 2;
    plateau[joueurs[1].x][joueurs[1].y] = joueurs[1].pion;

    if (nj == 4) {
        joueurs[2].x = TAILLE / 2;
        joueurs[2].y = 0;
        plateau[joueurs[2].x][joueurs[2].y] = joueurs[2].pion;

        joueurs[3].x = TAILLE / 2;
        joueurs[3].y = TAILLE - 1;
        plateau[joueurs[3].x][joueurs[3].y] = joueurs[3].pion;
    }
}
