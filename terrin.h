#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <stdbool.h>

typedef struct CaseBonus {
    int x;
    int y;
    int valeur;
    bool active;
} t_CaseBonus;

typedef struct terrain {
    char grille[20][40];
    t_CaseBonus case_bonus[7];
    int largeur;
    int hauteur;
} t_terrain;

t_terrain creerTerrain(void);
void afficherTerrain(t_terrain terrain);
bool verifierMouvement(t_terrain terrain, int x, int y);
int verifierCase(int x, int y, t_terrain *terrain);
void afficherCasesBonus(t_terrain terrain);
void reinitialiserCase(t_terrain *terrain, int x, int y);
void activerCaseBonus(t_CaseBonus *case_bonus);

#endif // TERRAIN_H_INCLUDED
