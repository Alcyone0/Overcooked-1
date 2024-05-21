//
// Created by ACER on 09/05/2024.
//

#ifndef TEST2_DEPLACE_H
#define TEST2_DEPLACE_H
#include <allegro.h>
#include "clients.h"
#include "score.h"

typedef struct {
    int curseur_x;
    int curseur_Y;
} Position;

void deplace(BITMAP *buffer, Position playerPos, Position playerPos1) ;
void deplace2(BITMAP *buffer, Position playerPos, Position playerPos1) ;
void deplace3(BITMAP *buffer, Position playerPos, Position playerPos1);
void anime_couteau(BITMAP *couteau, BITMAP* buffer);
#endif //TEST2_DEPLACE_H
