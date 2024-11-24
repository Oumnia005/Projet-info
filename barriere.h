#ifndef BARIERE_H_INCLUDED
#define BARIERE_H_INCLUDED

typedef struct bariere {
    int cord_x1;
    int cord_y1;
    int cord_x2;
    int cord_y2;
    int id;
    char sens;
    int active;
} t_bariere;

t_bariere creerBariere(void);
void afficherBarriereTexte(t_bariere barriere);
void changerCouleur(int texteCouleur, int fondCouleur);
void deplacerBariere(t_bariere *barriere, int new_x1, int new_y1, int new_x2, int new_y2);
void activerBariere(t_bariere *barriere);
void desactiverBariere(t_bariere *barriere);

#endif // BARIERE_H_INCLUDED
