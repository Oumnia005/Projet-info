#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueur.h"

struct joueur {
    char nom[50];
    int score;
    int nb_bariere;
    struct Crosshaire {
        char type;
        int cor_x;
        int cor_y;
    } crosshaire;
    int chrono;
};

// Fonction pour créer un joueur
struct joueur creeJoueur(void) {
    struct joueur j;
    j.nb_bariere = 0;
    printf("Entrez votre pseudo (50 caractères max) : ");
    scanf("%49s", j.nom);

    j.score = getScore(j.nom);
    j.crosshaire.type = 'A';  // Valeur par défaut pour le crosshaire
    j.crosshaire.cor_x = 0;
    j.crosshaire.cor_y = 0;
    j.chrono = 0;

    return j;
}

// Fonction pour afficher un joueur
void affichierJoueur(struct joueur j) {
    printf("Pseudo : %s\n", j.nom);
    printf("Score : %d\n", j.score);
    printf("Barrières restantes : %d\n", j.nb_bariere);
    printf("Crosshair : %c en coordonnée x=%d et y=%d\n", j.crosshaire.type, j.crosshaire.cor_x, j.crosshaire.cor_y);
}

// Fonction pour obtenir le score à partir d'un pseudo
int getScore(char *pseudo) {
    FILE *f;
    char ligne[70];
    char pseudoLue[50];
    int score = 0;

    f = fopen("joueur.txt", "r");
    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return 0; // Score initialisé à 0 si fichier inaccessible
    }

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%49[^,],%d", pseudoLue, &score);
        if (strcmp(pseudoLue, pseudo) == 0) {
            fclose(f);
            return score;
        }
    }

    fclose(f);

    f = fopen("joueur.txt", "a");
    if (f == NULL) {
        printf("Erreur ouverture fichier pour écriture\n");
        return 0;
    }

    fprintf(f, "%s,0\n", pseudo);
    fclose(f);

    return 0;
}

// Fonction pour mettre à jour le score
void setScore(char *pseudo, int score) {
    FILE *f;
    char ligne[70];
    char pseudoLue[50];
    int scoreLu;
    int found = 0;

    f = fopen("joueur.txt", "r+");
    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    long pos;
    while (fgets(ligne, sizeof(ligne), f)) {
        pos = ftell(f);
        sscanf(ligne, "%49[^,],%d", pseudoLue, &scoreLu);
        if (strcmp(pseudoLue, pseudo) == 0) {
            fseek(f, pos - strlen(ligne), SEEK_SET);
            fprintf(f, "%s,%d\n", pseudo, score);
            found = 1;
            break;
        }
    }

    if (!found) {
        fseek(f, 0, SEEK_END);
        fprintf(f, "%s,%d\n", pseudo, score);
    }

    fclose(f);
}
