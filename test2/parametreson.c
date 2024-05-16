//
// Created by ACER on 16/05/2024.
//

#include "parametreson.h"
#include <stdio.h>
#include <allegro.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void parametreson() {
    if (allegro_init() != 0) {
        fprintf(stderr, "Erreur lors de l'installation d'Allegro\n");
        return;
    }

    if (install_keyboard()) {
        fprintf(stderr, "Erreur lors de l'installation du clavier\n");
        return;
    }

    set_color_depth(32);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation des graphismes\n");
        return;
    }

    int vert = makecol(0, 216, 0);
    int rouge = makecol(255, 0, 0);
    int blanc = makecol(255, 255, 255);

    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    circlefill(screen, centerX, centerY, 60, vert);

    int textX = 10;
    int textY = 10;

    char text[] = "Sound on";

    while (!key[KEY_ESC]) {
        clear_to_color(screen, makecol(0, 0, 0));

        if (key[KEY_P]) {
            if (strcmp(text, "Sound on") == 0) {
                strcpy(text, "Sound off");
            } else {
                strcpy(text, "Sound on");
            }
            while (key[KEY_P]) rest(10);
        }

        if (strcmp(text, "Sound on") == 0) {
            //Remplacer ça par une image de son on
            //Ajouter la fonction qui active la musique
            circlefill(screen, centerX, centerY, 60, vert);
        } else {
            //Remplacer ça par une image de son off
            //Ajouter la fonction qui désactive la musique
            circlefill(screen, centerX, centerY, 60, rouge);
        }

        textout_ex(screen, font, text, textX, textY, blanc, -1);
        rest(10);
    }

}