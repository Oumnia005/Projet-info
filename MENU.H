//
// Created by samdj on 24/11/2024.
//
#include "stdbool.h"
#include "jeu.h"

#ifndef MENU_H
#define MENU_H



// Dimensions du plateau
#define TAILLE 9

// Barrieres
#define MAX_BARRIERES 20

// Positions des joueurs

void initialiserplateau(int nj, char plateau[TAILLE][TAILLE], Joueur joueurs[]);
void afficher_regles();
void initialiserjoueurs(int nj, Joueur joueurs[]);
bool symbole_unique(char pion, int index, Joueur joueurs[]);
void lancerpartie(int nj, char plateau[TAILLE][TAILLE],Joueur joueurs[]);
void afficherplateau(char plateau[TAILLE][TAILLE]);

#endif //MENU_H
