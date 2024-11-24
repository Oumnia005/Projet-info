#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "jeu.h"

// Dimensions du plateau
#define TAILLE 9

// Barrieres
#define MAX_BARRIERES 20

// Vérifie si une case est valide (dans les limites du plateau)
bool case_valide(int x, int y) {
    return x >= 0 && x < TAILLE && y >= 0 && y < TAILLE;
}

// Déplace un joueur
bool deplacer_joueur(Joueur *joueur, char direction,char plateau[TAILLE][TAILLE],int nj) {
    Joueur joueurs[4];
    int nv_x = joueur->x, nv_y = joueur->y;

    switch (direction) {
        case 'h': nv_x--; break; // Haut
        case 'b': nv_x++; break; // Bas
        case 'g': nv_y--; break; // Gauche
        case 'd': nv_y++; break; // Droite
        default: return false;
    }


    if (!case_valide(nv_x, nv_y))
        return false;

    if (plateau[nv_x][nv_y] == ' ') {
        plateau[joueur->x][joueur->y] = ' ';
        joueur->x = nv_x;
        joueur->y = nv_y;
        plateau[joueur->x][joueur->y] = joueur->pion;
        return true;
    }

    for (int i = 0; i < nj; i++) {
        if (joueurs[i].x == nv_x && joueurs[i].y == nv_y) {
            int saut_x = nv_x + (nv_x - joueur->x); // Case derrière
            int saut_y = nv_y + (nv_y - joueur->y);

            // Si la case derrière est valide et libre, effectuer le saut
            if (case_valide(saut_x, saut_y) && plateau[saut_x][saut_y] == ' ') {
                plateau[joueur->x][joueur->y] = ' ';
                joueur->x = saut_x;
                joueur->y = saut_y;
                plateau[joueur->x][joueur->y] = joueur->pion;
                return true;
            }
        }
    }

    return false;
}

bool poser_barriere(Joueur *joueur, char plateau[TAILLE][TAILLE]) {
    if (joueur->nb_barrieres_restantes <= 0) {
        printf("Vous n'avez plus de barrières.\n");
        return false;
    }

    int x, y;
    char orientation;
    printf("Entrez les coordonnées pour poser la barrière (x y) : ");
    scanf("%d %d", &x, &y);

    if (!case_valide(x, y)) {
        printf("Position invalide.\n");
        return false;
    }

    printf("Orientation (h pour horizontal, v pour vertical) : ");
    scanf(" %c", &orientation);

    if (orientation == 'h' && case_valide(x, y + 1) && plateau[x][y] == ' ' && plateau[x][y + 1] == ' ') {
        plateau[x][y] = '-';
        plateau[x][y + 1] = '-';
    } else if (orientation == 'v' && case_valide(x + 1, y) && plateau[x][y] == ' ' && plateau[x + 1][y] == ' ') {
        plateau[x][y] = '|';
        plateau[x + 1][y] = '|';
    } else {
        printf("Impossible de poser une barrière ici.\n");
        return false;
    }

    joueur->nb_barrieres_restantes--;
    return true;
}

// Vérifie si un joueur a gagné
bool verifvictoire(Joueur joueur, int nj) {
    Joueur joueurs[4];
    if (nj==2){
        if (joueurs[0].x == TAILLE - 1) {
            return true;
        }
        if (joueurs[1].x == 0) {
            return true;
        }
    }
    if (nj==4){
        if (joueurs[0].x == TAILLE - 1) {
            return true;
        }
        if (joueurs[1].x == 0) {
            return true;
        }
        if (joueurs[2].y == TAILLE - 1) {
            return true;
        }
        if (joueurs[3].y == 0) {
            return true;
        }
    }

    return false;
}

void enregistrement(int nj)//methode pour enregister une partie
{
    Joueur joueurs[4];
    FILE *f=NULL;
    f=fopen("Game.txt","w");//ouverture du fichier
    if(f==NULL)//verif de l'ouverture
    {
        printf("Erreur ouverture fichier");
    }

    fprintf(f,"%d\n",nj);//on enregistre le nb de joueur
    for(int i=0;i<nj;i++)//on enregistre les info de chaque joueur
    {
        fprintf(f,"%s,%c,%d,%d,%d\n",joueurs[i].nom,joueurs[i].pion,joueurs[i].x,joueurs[i].y,joueurs[i].nb_barrieres_restantes);
    }

    fclose(f);
}

void anciennepartie(int nj,char plateau[TAILLE][TAILLE]) {
    Joueur joueurs[4];
    FILE *f = NULL;
    f = fopen("Game.txt", "r"); // Ouverture du fichier en mode lecture
    if (f == NULL) {
        printf("Erreur : Impossible de lire le fichier de sauvegarde.\n");
        return;
    }

    // Lecture du nombre de joueurs
    fscanf(f, "%d\n", &nj);

    // Initialiser le plateau
    initialiserplateau(nj, plateau, joueurs);

    // Lire les informations des joueurs
    for (int i = 0; i < nj; i++) {
        char nom[20];
        char pion;
        int x, y;

        // Lecture des informations d'un joueur
        fscanf(f, "%s,%c,%d,%d\n", nom, &pion, &x, &y);

        // Mise à jour des informations du joueur
        strcpy(joueurs[i].nom, nom);
        joueurs[i].pion = pion;
        joueurs[i].x = x;
        joueurs[i].y = y;

        // Réinitialise le plateau
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                plateau[i][j] = ' ';
            }
        }

        // Placer le pion du joueur sur le plateau
        plateau[x][y] = pion;
    }

    fclose(f); // Fermer le fichier
    printf("Partie chargée avec succès !\n");
    afficherplateau(plateau[TAILLE][TAILLE]);
}
