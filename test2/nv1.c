//
// Created by ACER on 09/05/2024.
//

#include "nv1.h"
#include "setup.h"
#include <stdio.h>


BITMAP* images[240];

void load_images() {
    images[00] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\sol.bmp", NULL);
    images[01] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mur.bmp", NULL);
    images[02] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\decoupe.bmp", NULL);
    if (!images[00] || !images[01] || !images[02]) {
        fprintf(stderr, "Erreur lors du chargement de l'image assiette.bmp\n");
        // Gérer l'erreur ici (par exemple, retourner ou terminer le programme)
    }
    //images['W'] = load_bitmap("counter.bmp", NULL);

}

void display_kitchen(char** layout, int tile_width, int tile_height) {
    BITMAP* buffer = create_bitmap(800, 600);  // Création d'un tampon double
    BITMAP *fond = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fond.bmp", NULL);
    if (!fond) {
        fprintf(stderr, "Erreur lors du chargement de l'image fondjeu_nv1.bmp\n");
        // Gérer l'erreur ici (par exemple, retourner ou terminer le programme)
    }
    blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);

    // Afficher les éléments de la cuisine sur le tampon
    for (int row = 0; row < 12; ++row) {
        for (int col = 0; col < 20; ++col) {
            char element = layout[row][col];
            //printf("%c", element);  // Débogage : imprimer le caractère de la disposition
            if (images[element]) {
                // Afficher l'image correspondant à l'élément
                BITMAP* image_to_display = images[element];
                draw_sprite(buffer, image_to_display, 40 + (col * tile_width),  180 + (row * tile_height));
            }
        }
        printf("\n");  // Débogage : sauter une ligne après chaque rangée
    }

    // Afficher l'ensemble du tampon sur l'écran
    blit(buffer, screen, 0, 0, 0, 0, 800, 600);
    destroy_bitmap(buffer);
}


void unload_images() {
    if (images[00]) {
        destroy_bitmap(images[00]);
    }
    if (images[01]) {
        destroy_bitmap(images[01]);
    }
    if (images[02]) {
        destroy_bitmap(images[02]);
    }
    // Libérer d'autres images chargées selon les besoins
}

void nv1() {
    install_keyboard();

    load_images();

    // Read the kitchen layout from a text file (e.g., "niveau1.txt")
    FILE* layout_file = fopen("niveau1.txt", "r");
    if (!layout_file) {
        perror("Error opening layout file");
        return;
    }

    // Allocation dynamique pour stocker la disposition de la cuisine en tant que tableau d'entiers
    char** kitchen_layout = malloc(12 * sizeof(int*)); // Allocation dynamique pour 13 lignes
    for (int i = 0; i < 12; ++i) {
        kitchen_layout[i] = malloc(20 * sizeof(int)); // Allocation dynamique pour 21 colonnes

        // Lire chaque entier à partir du fichier
        for (int j = 0; j < 20; ++j) {
            if (fscanf(layout_file, "%d", &kitchen_layout[i][j]) != 1) {
                perror("Error reading layout file");
                fclose(layout_file);
                return;
            }
        }
    }
    fclose(layout_file);

    // Afficher la cuisine à l'écran en utilisant la disposition chargée et les images chargées
    display_kitchen(kitchen_layout, 38, 35);

    rest(5000);

    // Nettoyage de la mémoire allouée pour la disposition de la cuisine
    for (int i = 0; i < 12; ++i) {
        free(kitchen_layout[i]);
    }
    free(kitchen_layout);
    unload_images();
}
