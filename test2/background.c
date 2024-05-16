#include "background.h"
#include <allegro.h>
#include <stdio.h>



Level loadLevelFromFile(const char *filename) {
    BITMAP *poubelle = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\poubelle.bmp", NULL);

    Level level;
    FILE *file = fopen(filename, "r");
    if (file) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                int tileId;
                if (fscanf(file, "%d", &tileId) == 1) {
                    switch (tileId) {
                        case 0:
                            blit(poubelle, screen, 0, 0, 0, 0, poubelle->w, poubelle->h);
                            break;

                        default:
                            // Gestion des valeurs inconnues
                            break;
                    }
                } else {
                    // Gestion des erreurs de lecture du fichier
                    // Peut-être un format incorrect du fichier
                }
            }
        }
        fclose(file);
    } else {
        // Gestion des erreurs d'ouverture de fichier
    }
    return level;
}
