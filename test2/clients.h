//
// Created by ACER on 11/05/2024.
//

#ifndef TEST2_CLIENTS_H
#define TEST2_CLIENTS_H

#include <allegro.h>
#include <stdbool.h>
#include "score.h"

// Déclaration des fonctions
void dessinerclients(BITMAP *buffer, BITMAP *plat_rose, BITMAP *plat_vert, BITMAP *plat_jaune, bool *flag_rose, bool *flag_vert, bool *flag_jaune);
void avancerclients(int *delay_vert, int *delay_rose, int *delay_orange);
void revenirclients(bool *flag_vert, bool *flag_rose, bool *flag_jaune, int *delay_vert, int *delay_rose, int *delay_orange);

#endif //TEST2_CLIENTS_H
