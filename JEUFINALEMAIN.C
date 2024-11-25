#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "jeu.h"

// Dimensions du plateau
#define TAILLE 9// TAILLE TABLEAU

// Barrieres
#define MAX_BARRIERES 20// NOMBRE BARRIERE

int main() {
    char plateau[TAILLE][TAILLE];//INITALISE PLATEAU DE JEU
    char barriers_h[TAILLE - 1][TAILLE]; // Barrières horizontales
    char barriers_v[TAILLE][TAILLE - 1]; // Barrières verticales
    int nb_barrieres;// NB DE BARRIERE QUI VARIE
    int choix;
    int nj;//NB DE JOUEURS
    Joueur joueurs[4];
    menu(nj, plateau, joueurs);//ON APPELLE LA PROCEDURE MENU PR DEBUTER

    return 0;

}
