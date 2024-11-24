#ifndef CROSSHAIRE_H_INCLUDED
#define CROSSHAIRE_H_INCLUDED

typedef struct crosshaire {
    char type;
    int cor_x;
    int cor_y;
} t_crosshaire;

char choisirType(void);
t_crosshaire creerCrosshaire(void);
int obtenirX(t_crosshaire cross);
int obtenirY(t_crosshaire cross);
char obtenirType(t_crosshaire cross);

#endif // CROSSHAIRE_H_INCLUDED
