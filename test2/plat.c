//
// Created by ACER on 11/05/2024.
//

#include "plat.h"
#include <allegro.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


// sous programme aléatoire pour le plat choisi par les clients
BITMAP* choisir_image(BITMAP *plat1, BITMAP *plat2, BITMAP *plat3, int *taille) {
    int index_choisi = rand() % 3; // Choix aléatoire d'un index entre 0 et 2
    switch (index_choisi) {
        case 0:
            *taille = 275/2;
            return plat1;
        case 1:
            *taille = 275/2;
            return plat2;
        case 2:
            *taille = 302/2;
            return plat3;
    }
}

int chargerimage(BITMAP *plat1,BITMAP *plat2,BITMAP *plat3) {
    plat1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\plat1.bmp", NULL);
    if (!plat1) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }

    plat2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\plat2.bmp", NULL);
    if (!plat2) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }

    plat3 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\plat3.bmp", NULL);
    if (!plat3) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }


}

void recupererimage(BITMAP *plat1, BITMAP *plat2, BITMAP *plat3, BITMAP **plat_rose, BITMAP **plat_vert, BITMAP **plat_jaune, bool *flag_rose, bool *flag_vert, bool *flag_jaune,int *pos_rose, int *pos_vert, int *pos_jaune) {
    // Recuperation d'une image aléatoire si le Flag est levé
    int taille;
    if (!(*flag_rose)) {
        *plat_rose = choisir_image(plat1, plat2, plat3, &taille);
        *pos_rose = 370 - taille;
    }
    if (!(*flag_vert)) {
        *plat_vert = choisir_image(plat1, plat2, plat3, &taille);
        *pos_vert = 170 - taille;
    }
    if (!(*flag_jaune)) {
        *plat_jaune = choisir_image(plat1, plat2, plat3, &taille);
        *pos_jaune = 570 - taille;
    }
}

