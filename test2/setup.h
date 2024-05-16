//
// Created by ACER on 26/03/2024.
//

#ifndef TEST2_SETUP_H
#define TEST2_SETUP_H
#include <allegro.h>
typedef struct {
    char path[100]; // Chemin de l'image
    int x, y;       // Position x, y
} ImageInfo;
void setup();
#endif //TEST2_SETUP_H
