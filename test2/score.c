//
// Created by ACER on 19/05/2024.
//


#include <allegro.h>
#include "score.h"

void afficher_score(BITMAP *buffer, int score) {
    // Couleur du texte (blanc)
    int text_color = makecol(0, 0, 0);

    // Position du texte
    int text_x = 10;
    int text_y = 10;

    // Affichage du texte
    textprintf_ex(buffer, font, text_x, text_y, text_color, -1, "Score: %d", score);
}