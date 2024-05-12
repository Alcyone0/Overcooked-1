//
// Created by ACER on 09/05/2024.
//

#ifndef TEST2_DEPLACE_H
#define TEST2_DEPLACE_H
#include <allegro.h>

typedef struct {
    int curseur_x;
    int curseur_Y;
} Position;

void deplace(BITMAP *buffer, Position playerPos, Position playerPos1) ;
#endif //TEST2_DEPLACE_H
