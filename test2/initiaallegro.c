//
// Created by ACER on 07/04/2024.
//

#include "initiaallegro.h"
#include <allegro.h>

// Initialisation d'Allegro
void initAllegro() {
    allegro_init();
    install_keyboard();
    install_mouse();

    install_timer();


    // Initialisation du mode graphique
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    // Création du buffer
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Erreur : création du buffer.");
        exit(EXIT_FAILURE);
    }

}