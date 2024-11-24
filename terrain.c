#include "terrain.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

t_CaseBonus creerCaseAleatoire() {
    t_CaseBonus caseBonus;
    caseBonus.x = 1 + rand() % 7;
    caseBonus.y = 1 + rand() % 7;
    caseBonus.valeur = 1 + rand() % 3;
    caseBonus.active = 1;
    return caseBonus;
}

t_terrain creerTerrain() {
    t_terrain grille = {0};

    for (int i = 0; i < 7; i++) {
        grille.case_bonus[i] = creerCaseAleatoire();
    }

    char chiffres[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 9; i++) {
        grille.grille[i * 2 + 2][0] = chiffres[i];
    }

    char lettres[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    for (int i = 0; i < 9; i++) {
        grille.grille[0][i * 4 + 6] = lettres[i];
    }

    for (int i = 0; i < 19; i++) {
        if (i % 2 == 1) {
            for (int j = 0; j < 4; j++) {
                grille.grille[i][j] = 0xC4;
            }
        }
    }

    for (int j = 4; j < 40; j++) {
        grille.grille[1][j] = (j % 4 == 0) ? 0xC5 : 0xC4;
    }

    for (int i = 2; i < 19; i++) {
        for (int j = 4; j < 40; j++) {
            if (i % 2 != 0) {
                grille.grille[i][j] = (j % 4 == 0) ? 0xC5 : 0xC4;
            } else {
                grille.grille[i][j] = (j % 4 == 0) ? 0xB3 : 0x00;
            }
        }
    }

    return grille;
}

void affichageTerrain(t_terrain terrain) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            gotoligcol(i, j);
            printf("%c", terrain.grille[i][j]);
        }
    }
}

int verifierCase(int x, int y, t_terrain *terrain) {
    for (int i = 0; i < 7; i++) {
        if (terrain->case_bonus[i].x == x && terrain->case_bonus[i].y == y && terrain->case_bonus[i].active == 1) {
            int valeur = terrain->case_bonus[i].valeur;
            terrain->case_bonus[i].active = 0;
            return valeur;
        }
    }
    return 0;
}

void afficherCase(t_terrain terrain) {
    for (int i = 0; i < 7; i++) {
        if (terrain.case_bonus[i].active == 1) {
            gotoligcol(terrain.case_bonus[i].y * 2 + 2, terrain.case_bonus[i].x * 4 + 6);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            printf("%d", terrain.case_bonus[i].valeur);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
    }
}
