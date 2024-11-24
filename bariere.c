#include "bariere.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

t_bariere creerBariere(void) {
    t_bariere barriere = {0};
    barriere.active = 0;
    barriere.cord_x1 = 0;
    barriere.cord_y1 = 0;
    barriere.cord_x2 = 0;
    barriere.cord_y2 = 0;
    barriere.id = 0;
    barriere.sens = 'h';
    return barriere;
}

void afficherBarriereTexte(t_bariere barriere) {
    printf("Barriere n°%d, active: %d, coord x1 = %d, y1 = %d, x2 = %d, y2 = %d, sens: %c\n",
           barriere.id, barriere.active, barriere.cord_x1, barriere.cord_y1, barriere.cord_x2, barriere.cord_y2, barriere.sens);
}

void changerCouleur(int texteCouleur, int fondCouleur) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, fondCouleur * 16 + texteCouleur);
}
