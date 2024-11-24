#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "crosshaire.h"

typedef struct joueur {
    char nom[50];
    int score;
    t_crosshaire crosshaire;
    int nb_bariere;
    char startside;
    struct joueur *next;
    int chrono;
} t_joueur;

t_joueur creeJoueur(void);
void afficherJoueur(t_joueur joueur);
int getScore(const char *pseudo);
void setScore(t_joueur *joueur, int score);
void incrementerBarrieres(t_joueur *joueur);
void decrementerBarrieres(t_joueur *joueur);
void resetChrono(t_joueur *joueur);

#endif // JOUEUR_H_INCLUDED
