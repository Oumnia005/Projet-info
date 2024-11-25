#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "jeu.h"

// Dimensions du plateau
#define TAILLE 9

// Barrieres
#define MAX_BARRIERES 20

// VERIFIE SI LA CASE DU DEPLACEMENT DU PION OU DE LA BARRIERE EST VALIDE
bool case_valide(int x, int y) {
    return x >= 0 && x < TAILLE && y >= 0 && y < TAILLE;
}

// DEPLACE LE PION
bool deplacer_joueur(Joueur *joueur,Joueur joueurs[], char direction,char plateau[TAILLE][TAILLE],int nj) {
    int nv_x = joueur->x, nv_y = joueur->y;//NOUVELLES COORDONNES

    switch (direction) { //DIFFERENTES DIRECTION DE DEPLACEMENT PR LE PION
        case 'H': nv_x=nv_x-1; break; // H
        case 'B': nv_x=nv_x+1; break; // B
        case 'G': nv_y=nv_y-1; break; // G
        case 'D': nv_y=nv_y+1; break; // D
        default: return false;
    }


    if (!case_valide(nv_x, nv_y))   //SI
        return false;
    //EFFECTUE LE DEPLACEMENT
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

            // PASSE AU DESSUS DU JOUEUR SI C POSSIBLE
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
    if (joueur->nb_barrieres_restantes <= 0) {//VERIFIE LE NB DE BARRIERES
        printf("Vous n'avez plus de barrières.\n");//AFFICHE AVERTISSEMENT 
        return false;
    }

    int x, y;
    char orientation;
    printf("Entrez les coordonnées pour poser la barrière (x y) : ");// DEMANDE AU JOUEUR DE RENTRER LES COORDONNEES DE LA BARRIERE QU'IL SOUHAITE POSER
    scanf("%d %d", &x, &y);// LE JOUEUR RENTRE LES COORDONNEES 

    if (!case_valide(x, y)) {
        printf("Position invalide.\n");//VERIFIE SI LES COORDONNES EXISTENT
        return false;
    }

    printf("Orientation (H pour horizontal, V pour vertical) : ");// DEMANDE DE CHOISIR LE SENS DES BARRIERES
    scanf(" %c", &orientation);// LE JOUEUR RENTRE LE SENS 
    //SI TT EST CORRECT ALORS POSE DE LA BARRIERE
    if (orientation == 'H' && case_valide(x, y + 1) && plateau[x][y] == ' ' && plateau[x][y + 1] == ' ') {// CONDITION DE DEPOSE DE BARRIERE
        plateau[x][y] = '-'; 
        plateau[x][y + 1] = '-';
    } else if (orientation == 'V' && case_valide(x + 1, y) && plateau[x][y] == ' ' && plateau[x + 1][y] == ' ') {
        plateau[x][y] = '|';
        plateau[x + 1][y] = '|';
    } else {
        printf("Impossible de poser une barrière ici.\n");// AFFFICHE MESSAGE D'ERREUR 
        return false;
    }

    joueur->nb_barrieres_restantes--;// MOINS 1 SUR LE NOMBRE DE BARRIERE DU JOUEUR
    return true;
}

// Vérifie si un joueur a gagné
bool verifvictoire(Joueur joueurs[], int nj) {
    // LE CAS OU IL Y A 2 JOUEURS
    if (nj==2){
        if (joueurs[0].x == TAILLE - 1) { // LIGNE D ARRIVE PR JOUEUR 1
            return true;
        }
        if (joueurs[1].x == 0) {    // LIGNE D ARRIVE PR JOUEUR 2
            return true;
        }
    }
    // LE CAS OU IL Y A 4 JOUEURS
    if (nj==4){
        if (joueurs[0].x == TAILLE - 1) {   // LIGNE D ARRIVE PR JOUEUR 1
            return true;
        }
        if (joueurs[1].x == 0) {    // LIGNE D ARRIVE PR JOUEUR 2
            return true;
        }
        if (joueurs[2].y == TAILLE - 1) {   // LIGNE D ARRIVE PR JOUEUR 3
            return true;
        }
        if (joueurs[3].y == 0) {    // LIGNE D ARRIVE PR JOUEUR 4
            return true;
        }
    }

    return false;
}

void enregistrement(int nj,Joueur joueurs[],int tour)//methode pour enregister une partie
{
    FILE *f=NULL;
    f=fopen("Game.txt","w");//ouverture du fichier
    if(f==NULL)//verif de l'ouverture
    {
        printf("Erreur ouverture fichier");
    }

    fprintf(f,"%d\n",nj);//on enregistre le nb de joueur
    for(int i=0;i<nj;i++)//on enregistre les info de chaque joueur
    {
        fprintf(f,"%s,%c,%d,%d,%d,%d\n",joueurs[i].nom,joueurs[i].pion,joueurs[i].x,joueurs[i].y,joueurs[i].nb_barrieres_restantes,joueurs[i].score);
    }
    fprintf(f,"%d\n", tour);
    fclose(f);
}

void anciennepartie(int nj,char plateau[TAILLE][TAILLE], Joueur joueurs[]) {
    FILE *f = NULL;
    f = fopen("Game.txt", "r"); // LECTURE DU FICHIER
    if (f == NULL) {
        printf("Erreur : Impossible de lire le fichier de sauvegarde.\n");
        return;
    }

    // Lecture du NB JOUEURS
    fscanf(f, "%d\n", &nj);

    // INITIALISE PLATEAU
    initialiserplateau(nj, plateau, joueurs);

    // REINITIALISE PLATEAU
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j] = ' ';
        }
    }

    // LECTURE INFO
    for (int i = 0; i < nj; i++) {
        char nom[20];
        char pion;
        int nb_barrieres;
        int score;
        int x, y;

        // Lecture des informations d'un joueur
        fscanf(f, "%[^,],%c,%d,%d,%d,%d\n", nom, &pion, &x, &y,&nb_barrieres, &score);

        // ATTRIBUE LES COORDOONES ET INFOS AU PION
        strcpy(joueurs[i].nom, nom);
        joueurs[i].pion = pion;
        joueurs[i].x = x;
        joueurs[i].y = y;
        joueurs[i].nb_barrieres_restantes = nb_barrieres;
        joueurs[i].score = score;


        // PLACE PION
        plateau[x][y] = pion;
    }

    fclose(f); // Fermer le fichier
    printf("Partie chargée avec succès !\n");
    afficherplateau(plateau);
    getchar();
    getchar();
}

/*void relancepartie(int nj,char plateau[TAILLE][TAILLE], Joueur joueurs[]) {
    while (1) {
        afficherplateau(plateau);

        // VERIF DE LA VICTOIRE
        if (verifvictoire(joueurs, nj)) {
            printf("\nLe joueur %s a remporte la partie !\n", joueurs[tour-1].nom);
            joueurs[tour-1].score+= 5;
            enregistrement(nj, joueurs);
            getchar();
            getchar();
            break;
        }
        //CHOIX DES ACTIONS
        printf("\n %s, Que vous voulez faire:\n ", joueurs[tour].nom);
        printf("1.Bouger mon pion\n");
        printf(" 2.Poser une barriere (%d barrieres restantes)\n", joueurs[tour].nb_barrieres_restantes);
        printf(" 3.Passer mon tour\n");
        printf(" 4.Annuler le dernier tour\n");
        printf(" 5.Retour au menu\n");
        int choix;
        char commande;
        scanf(" %d", &choix);

        switch (choix) {
            case 1:
                printf("Quelle direction ?(H/B/G/D)");// AFFICHAGE DE DEMANDE DE LA DIRECTION
            scanf(" %c", &commande);// JOUEUR RENTRE LA DIRECTION QU'IL SOUHAITE
            if (!deplacer_joueur(&joueurs[tour],joueurs, commande, plateau, nj)) {
                printf("Déplacement invalide !\n");//MESSAGE D'ERREUR DE LA DIRECTION
                continue;
            }

            tour = (tour + 1) % nj; // Tour suivant
            break;
            case 2:
                if (!poser_barriere(&joueurs[tour], plateau)) {
                    continue;
                }
            tour = (tour + 1) % nj;
            break;
            case 3:
                tour = (tour + 1) % nj;
            break;
            case 4:
                printf("Pas encore codé");
            break;
            case 5:
                enregistrement(nj, joueurs);
            system("cls");//EFFACE LA PAGE AFFICHE ET REVIENS AU MENU
            menu(nj, plateau, joueurs);
            default:
                printf("Veuillez choisir un des numero proposes");// DEMANDE DE CHOISIR PARMI LES OPTIONS DU MENU
            break;
        }

    }
}
*/
