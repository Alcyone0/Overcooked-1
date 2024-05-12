//
// Created by ACER on 11/05/2024.
//

#ifndef TEST2_PLAT_H
#define TEST2_PLAT_H

#include <allegro.h>
#include <stdbool.h>

// Déclaration des variables globales pour les positions des plats


// Déclaration des fonctions
int chargerimage(BITMAP *plat1, BITMAP *plat2, BITMAP *plat3);
void recupererimage(BITMAP *plat1, BITMAP *plat2, BITMAP *plat3, BITMAP **plat_rose, BITMAP **plat_vert, BITMAP **plat_jaune, bool *flag_rose, bool *flag_vert, bool *flag_jaune,int *pos_rose, int *pos_vert, int *pos_jaune);

#endif //TEST2_PLAT_H
