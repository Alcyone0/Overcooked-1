//
// Created by ACER on 09/05/2024.
//

#include "deplace.h"
#include <allegro.h>
#include <stdbool.h>
//#include "setup.h"
#include <time.h>
#include <stdlib.h>
#include "clients.h"
#include "plat.h"

// Taille et vitesse de déplacement des cercles
#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5

BITMAP *plat_rose, *plat_vert, *plat_jaune;
BITMAP *plat1 = NULL;
BITMAP *plat2 = NULL;
BITMAP *plat3 = NULL;

int taille;

bool flag_rose=false;
bool flag_vert=false;
bool flag_jaune=false;

// délais aléatoire pour chaque client
int delay_vert;
int delay_rose;
int delay_orange;

int pos_rose ;
int pos_jaune ;
int pos_vert ;


// Déclarations globales des variables de position
int cercle_rouge_x = 200;
int cercle_rouge_y = 400;
int cercle_bleu_x = 500;
int cercle_bleu_y = 400;


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
            //allegro_message("Le joueur est sur l'ingrédient : %s\n", zones[i].nom);
            return true;
        }
    }
    return false; // Le joueur n'est sur aucun ingrédient
}

bool passe_sur_case = false;

int assiette1_x = 455;
int assiette1_y = 320;

BITMAP *assiette1;


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


void deplace(BITMAP *buffer, Position playerPos) {

    srand(time(NULL));

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);


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
    assiette1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    if (!cuisinier1 || !cuisinier2 || !assiette1 ) {
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

    // Vérifie si le cercle rouge passe sur les coordonnées spécifiées
    if (((playerPos.curseur_x >= 462 && playerPos.curseur_x <= 494 &&
          playerPos.curseur_Y >= 319 && playerPos.curseur_Y <= 356) && !passe_sur_case) && (key[KEY_P])){
        passe_sur_case = true;
    }

    if (passe_sur_case) {
        assiette1_x = playerPos.curseur_x - 10;
        assiette1_y = playerPos.curseur_Y - 10;
    }

    masked_blit(assiette1, buffer, 0, 0, assiette1_x, assiette1_y, assiette1->w, assiette1->h);

    chargerimage(&plat1, &plat2, &plat3);
    recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
    dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
    avancerclients(&delay_vert,&delay_rose,&delay_orange);
    revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);


    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (0, 0, 255));
    circlefill(buffer, curseur_X, curseur_y, 7, (0, 12, 12));


    blit(buffer,screen,0,0,0,0,800,600);

    if (plat1) {
        destroy_bitmap(plat1);
        plat1 = NULL;
    }
    if (plat2) {
        destroy_bitmap(plat2);
        plat2 = NULL;
    }
    if (plat3) {
        destroy_bitmap(plat3);
        plat3 = NULL;
    }


}