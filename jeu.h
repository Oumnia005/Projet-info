#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS
#include "joueur.h"
#include "terrain.h"
#include "bariere.h"

typedef struct liste {
    t_joueur *tete;
} t_liste;

typedef struct dernier_mouvement {
    t_joueur joueurs[4];
    t_bariere barrieres[20];
    int actif;
} t_dernier_mouvement;

typedef struct jeu {
    t_terrain surfaceJeu;
    t_joueur joueurs[4];
    t_liste ordreJoueurs;
    t_bariere barrieres[20];
    int etat; // 0: pas commencé, 1: en cours, 2: fini
    int nombreJoueurs;
    t_dernier_mouvement dernierMouvement;
} t_jeu;

t_jeu creerJeu(void);
t_dernier_mouvement creerDernierMouvement(void);
void initialiserNouvellePartie(t_jeu *jeu);
void chargerAnciennePartie(t_jeu *jeu);
void commencerPartie(int charger);
int faireTour(t_joueur *joueur, t_jeu *jeu);
void deplacerJoueur(t_joueur *joueur, t_jeu *jeu);
int estDeplacementPossible(t_jeu jeu, t_joueur joueur, int x, int y, char sens);
int estJoueurPresent(t_jeu jeu, t_joueur joueur, int x, int y);
void poserBarriere(t_jeu *jeu, t_joueur *joueur);
void bougerBarriere(t_jeu *jeu, int nb, int x, int y, int direction);
int verifierFinJeu(t_joueur *joueur);
void afficherInfosJoueur(t_jeu jeu);
void dessinerBarriere(t_jeu jeu);
void afficherJeu(t_jeu jeu, t_joueur joueur);
int estToucheAppuyee(void);

#endif // JEU_H_INCLUDED
