//
// Created by ACER on 09/05/2024.
//

#include "deplace.h"
#include <allegro.h>
#include <stdbool.h>

// Taille et vitesse de déplacement des cercles
#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5

// Déclarations globales des variables de position
int cercle_rouge_x = 200;
int cercle_rouge_y = 400;
int cercle_bleu_x = 500;
int cercle_bleu_y = 400;

/*int curseur_x = 220;
int curseur_Y = 410;*/

int curseur_X = 500;
int curseur_y = 410;

typedef struct {
    int curseur_x;
    int curseur_Y;
} Position;

typedef struct {
    int x1; // Coordonnée x du coin supérieur gauche
    int y1; // Coordonnée y du coin supérieur gauche
    int x2; // Coordonnée x du coin inférieur droit
    int y2; // Coordonnée y du coin inférieur droit
    const char* nom; // Nom de l'ingrédient
} ZoneIngredient;

ZoneIngredient zonesIngredients[] = {
        {462, 319, 494, 356, "assiette"},   // Exemple pour une tomate
        {70, 249, 107, 280, "pates"},  // Ajoutez les autres ingrédients ici
        // Ajoutez d'autres zones d'ingrédients selon vos besoins
};

bool isInsideIngredient(Position playerPos, ZoneIngredient zones[], int numZones) {
    for (int i = 0; i < numZones; i++) {
        if (playerPos.curseur_x >= zones[i].x1 && playerPos.curseur_x <= zones[i].x2 &&
            playerPos.curseur_Y >= zones[i].y1 && playerPos.curseur_Y <= zones[i].y2 && key[KEY_P]) {
            allegro_message("Le joueur est sur l'ingrédient : %s\n", zones[i].nom);
            return true;
        }
    }
    return false; // Le joueur n'est sur aucun ingrédient
}


int directionX_cuisinier2 = 1;
int directionX_cuisinier1 = 1; // 1 pour droite, -1 pour gauche

BITMAP *cuisinier2, *cuisinier1;

// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle1(int x, int y) {
    return (x >= 328 && x <= 490 && y >= 220 && y <= 405);
}
// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle2(int x, int y) {
    return (x >= 338 && x <= 490 && y >= 220 && y <= 390);
}
// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle3(int x, int y) {
    return (x >= 260 && x <= 570 && y >= 500 && y <= 600);
}
// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle4(int x, int y) {
    return (x >= 235 && x <= 570 && y >= 510 && y <= 600);
}


void deplace(BITMAP *buffer, Position playerPos, BITMAP *assiette) {

    if (cuisinier2) {
        destroy_bitmap(cuisinier2);
        cuisinier2 = NULL;
    }
    if (cuisinier1) {
        destroy_bitmap(cuisinier1);
        cuisinier1 = NULL;
    }
    cuisinier2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier2.bmp", NULL);
    cuisinier1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier1.bmp", NULL);
    if (!cuisinier1 || !cuisinier2) {
        allegro_message("Erreur lors du chargement de l'image.");
        exit(EXIT_FAILURE);
    }

    // Déplacer et dessiner le cercle rouge (cuisinier 2)
    if (key[KEY_LEFT] && cercle_rouge_x - VITESSE_DEPLACEMENT >= 105 && !isInsideRectangle2(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) && !isInsideRectangle3(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y)) {
        cercle_rouge_x -= VITESSE_DEPLACEMENT;
        directionX_cuisinier2 = -1; // Gauche
        playerPos.curseur_Y = cercle_rouge_y + 40;
        playerPos.curseur_x = cercle_rouge_x - 10;

    }
    if (key[KEY_RIGHT] && cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 725 && !isInsideRectangle2(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y) && !isInsideRectangle3(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)) {
        cercle_rouge_x += VITESSE_DEPLACEMENT;
        directionX_cuisinier2 = 1; // Droite
        playerPos.curseur_Y = cercle_rouge_y + 40;
        playerPos.curseur_x = cercle_rouge_x + 50;

    }
    if (key[KEY_UP] && cercle_rouge_y - VITESSE_DEPLACEMENT >= 180 && !isInsideRectangle2(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT) && !isInsideRectangle3(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)) {
        cercle_rouge_y -= VITESSE_DEPLACEMENT;
        playerPos.curseur_Y = cercle_rouge_y - 10;
        playerPos.curseur_x = cercle_rouge_x + 20;

    }
    if (key[KEY_DOWN] && cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 && !isInsideRectangle2(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) && !isInsideRectangle3(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
        cercle_rouge_y += VITESSE_DEPLACEMENT;
        playerPos.curseur_Y = cercle_rouge_y + 70;
        playerPos.curseur_x = cercle_rouge_x + 20;
    }


    if (directionX_cuisinier2 == 1) {
        // Dessiner normalement (droite)
        draw_sprite(buffer, cuisinier2, cercle_rouge_x, cercle_rouge_y);
    } else {
        // Dessiner en miroir horizontal (gauche)
        draw_sprite_h_flip(buffer, cuisinier2, cercle_rouge_x, cercle_rouge_y);
    }

    // Déplacer et dessiner le cercle bleu (cuisinier 1)
    if (key[KEY_A] && cercle_bleu_x - VITESSE_DEPLACEMENT >= 105 && !isInsideRectangle1(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y) && !isInsideRectangle4(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)) {
        cercle_bleu_x -= VITESSE_DEPLACEMENT;
        directionX_cuisinier1 = -1; // Gauche
        curseur_y = cercle_bleu_y + 40;
        curseur_X = cercle_bleu_x - 10;
    }
    if (key[KEY_D] && cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 705 && !isInsideRectangle1(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y) && !isInsideRectangle4(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)) {
        cercle_bleu_x += VITESSE_DEPLACEMENT;
        directionX_cuisinier1 = 1; // Droite
        curseur_y = cercle_bleu_y + 35;
        curseur_X = cercle_bleu_x + 70;
    }
    if (key[KEY_W] && cercle_bleu_y - VITESSE_DEPLACEMENT >= 180 && !isInsideRectangle1(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT) && !isInsideRectangle4(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)) {
        cercle_bleu_y -= VITESSE_DEPLACEMENT;
        curseur_y = cercle_bleu_y - 10;
        curseur_X = cercle_bleu_x + 20;
    }
    if (key[KEY_S] && cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 && !isInsideRectangle1(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) && !isInsideRectangle4(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
        cercle_bleu_y += VITESSE_DEPLACEMENT;
        curseur_y = cercle_bleu_y + 70;
        curseur_X = cercle_bleu_x + 20;
    }

    if (directionX_cuisinier1 == 1) {
        // Dessiner normalement (droite)
        draw_sprite_vh_flip(buffer, cuisinier1, cercle_bleu_x, cercle_bleu_y);
    } else {
        // Dessiner en miroir horizontal (gauche)
        draw_sprite_v_flip(buffer, cuisinier1, cercle_bleu_x, cercle_bleu_y);
    }

    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (0, 0, 255));
    circlefill(buffer, curseur_X, curseur_y, 7, (0, 12, 12));

    if ((isInsideIngredient(playerPos, zonesIngredients, sizeof(zonesIngredients) / sizeof(ZoneIngredient))) && key[KEY_P]) {
        masked_blit(assiette, buffer, 0, 0, playerPos.curseur_x, playerPos.curseur_Y, assiette->w, assiette->h);

    }


}


