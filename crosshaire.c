#include "crosshaire.h"
#include <stdlib.h>

char choisirType(void) {
    int nb = rand() % 8;
    switch (nb) {
        case 0: return '@';
        case 1: return '*';
        case 2: return '#';
        case 3: return '&';
        case 4: return '%';
        case 5: return '?';
        case 6: return 0xBE;
        case 7: return '$';
        default: return '@';
    }
}

t_crosshaire creerCrosshaire(void) {
    t_crosshaire cross = {0};
    cross.type = choisirType();
    cross.cor_x = -1;
    cross.cor_y = -1;
    return cross;
}

int obtenirX(t_crosshaire cross) {
    return cross.cor_x;
}

int obtenirY(t_crosshaire cross) {
    return cross.cor_y;
}

char obtenirType(t_crosshaire cross) {
    return cross.type;
}
