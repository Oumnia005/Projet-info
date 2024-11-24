#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include <windows.h>

void initialiserJeu(struct jeu *partie);
t_joueur* joueurSuivant(t_jeu *jeu);
void choixActionJoueur(t_joueur *joueur, t_jeu *jeu);
void bougerJoueur(t_joueur *joueur, t_jeu *jeu);
void installerBarriere(t_jeu *jeu, t_joueur *joueur);
char lireInputUtilisateur();
void lancerJeu(t_jeu *jeu);

int main() {
    struct jeu partie = creeJeu();
    initialiserJeu(&partie);
    lancerJeu(&partie);
    return 0;
}

void initialiserJeu(struct jeu *partie) {
    partie->etat = 0;
    partie->nbjoueur = 2;
    printf("Initialisation du jeu avec %d joueurs.\n", partie->nbjoueur);
    t_joueur* joueurCourant = &partie->j1;
    for (int i = 0; i < partie->nbjoueur; ++i) {
        printf("Entrez le pseudo pour le joueur %d: ", i + 1);
        scanf("%49s", joueurCourant->nom);
        joueurCourant->nb_bariere = 10;
        joueurCourant = joueurCourant->next;
    }
    printf("Jeu initialisé. Prêt à commencer!\n");
}

t_joueur* joueurSuivant(t_jeu *jeu) {
    return jeu->ordrejeu.j;
}

void choixActionJoueur(t_joueur *joueur, t_jeu *jeu) {
    char choix;
    do {
        printf("%s, choisissez votre action (z: Bouger, b: Barrière, q: Quitter):\n", joueur->nom);
        choix = lireInputUtilisateur();
    } while (!(choix == 'z' || choix == 'b' || choix == 'q'));

    switch (choix) {
        case 'z':
            bougerJoueur(joueur, jeu);
            break;
        case 'b':
            if (joueur->nb_bariere > 0) {
                installerBarriere(jeu, joueur);
            } else {
                printf("Pas de barrières restantes!\n");
            }
            break;
        case 'q':
            jeu->etat = 3;
            break;
    }
}

void bougerJoueur(t_joueur *joueur, t_jeu *jeu) {
    printf("%s bouge!\n", joueur->nom);
}

void installerBarriere(t_jeu *jeu, t_joueur *joueur) {
    printf("%s installe une barrière.\n", joueur->nom);
    joueur->nb_bariere--;
}

char lireInputUtilisateur() {
    char input;
    input = getchar();
    while (getchar() != '\n');
    return input;
}

void lancerJeu(t_jeu *jeu) {
    printf("Bienvenue au Jeu de Barrières!\n");
    while (jeu->etat != 3) {
        t_joueur *joueur = joueurSuivant(jeu);
        printf("C'est au tour de %s\n", joueur->nom);
        choixActionJoueur(joueur, jeu);
        jeu->ordrejeu.j = jeu->ordrejeu.j->next;
    }
    printf("Merci d'avoir joué! À la prochaine!\n");
}
