##include <stdio.h>
#include <stdbool.h>

#define TAILLE 9

// Structure pour un pion
typedef struct {
    int x;
    int y;
} Pion;

// Structure pour un mur
typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} Mur;

// Initialiser le plateau avec des cases vides
void initPlateau(char plateau[TAILLE][TAILLE]) {
    int i, j;
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            plateau[i][j] = '.'; // Le point représente les cases vides
        }
    }
}

// Afficher le plateau avec les pions
void afficherPlateau(char plateau[TAILLE][TAILLE], Pion p1, Pion p2) {
    int i, j;
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            if (p1.x == i && p1.y == j) {
                printf("1 "); // Affiche "1" pour le pion du joueur 1
            } else if (p2.x == i && p2.y == j) {
                printf("2 "); // Affiche "2" pour le pion du joueur 2
            } else {
                printf("%c ", plateau[i][j]); // Affiche la case vide
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Vérifier si une position est dans les limites du plateau
bool estDansLesLimites(int x, int y) {
    if (x >= 0 && x < TAILLE && y >= 0 && y < TAILLE) {
        return true;
    } else {
        return false;
    }
}

// Déplacer un pion 
bool deplacerPion(Pion *pion, int dx, int dy) {
    int nouvelleX = pion->x + dx;
    int nouvelleY = pion->y + dy;

    if (estDansLesLimites(nouvelleX, nouvelleY)) {
        pion->x = nouvelleX;
        pion->y = nouvelleY;
        return true;
    } else {
        printf("Déplacement invalide! Hors limites.\n");
        return false;
    }
}

// Fonction principale
int main() {
    char plateau[TAILLE][TAILLE];
    initPlateau(plateau);

    Pion p1 = {0, TAILLE / 2}; // Position de départ du pion 1
    Pion p2 = {TAILLE - 1, TAILLE / 2}; // Position de départ du pion 2

    afficherPlateau(plateau, p1, p2);

  
    printf("Déplacement du pion 1 vers le bas:\n");
    deplacerPion(&p1, 1, 0); // Déplacer pion 1 vers le bas
    afficherPlateau(plateau, p1, p2);

    return 0;
}
