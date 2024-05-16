//
// Created by ACER on 09/05/2024.
//

#include "deplace.h"
#include <allegro.h>
#include <stdbool.h>
//#include "setup.h"
//#include <time.h>
#include <stdlib.h>
//#include "plat.h"
//#include <stdio.h>
#include "nv1.h"
#define MAX_INGREDIENTS 8

typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
} Zone;

typedef struct {
    BITMAP *image;
    int x;
    int y;
    bool picked;
    Zone zone; // Zone pour la détection de ramassage
} Ingredient;

Ingredient ingredients[MAX_INGREDIENTS];


bool isInsideZone(int x, int y, Zone zone) {
    return (x >= zone.x_min && x <= zone.x_max && y >= zone.y_min && y <= zone.y_max);
}

BITMAP *champi1, *tomate1, *assiette1, *pate1, *jambon1, *mozza1, *piZ1, *olive1;


void initIngredients() {

    // Initialiser chaque ingrédient avec son image, sa position et sa zone de ramassage
    ingredients[0].image = champi1;
    ingredients[0].x = 724;
    ingredients[0].y = 293;
    ingredients[0].picked = false;
    ingredients[0].zone = (Zone){724, 760, 287, 324}; // Champignon

    ingredients[1].image = tomate1;
    ingredients[1].x = 726;
    ingredients[1].y = 566;
    ingredients[1].picked = false;
    ingredients[1].zone = (Zone){726, 760, 568, 600}; // Tomate

    ingredients[2].image = assiette1;
    ingredients[2].x = 455;
    ingredients[2].y = 320;
    ingredients[2].picked = false;
    ingredients[2].zone = (Zone){462, 494, 319,356}; // ASSIETTE

    ingredients[3].image = pate1;
    ingredients[3].x = 72;
    ingredients[3].y = 105;
    ingredients[3].picked = false;
    ingredients[3].zone = (Zone){72,105, 252,287}; // Tomate

    ingredients[4].image = mozza1;
    ingredients[4].x = 72;
    ingredients[4].y = 420;
    ingredients[4].picked = false;
    ingredients[4].zone = (Zone){72,105,463,500}; // Tomate

    ingredients[5].image = olive1;
    ingredients[5].x = 724;
    ingredients[5].y = 432;
    ingredients[5].picked = false;
    ingredients[5].zone = (Zone){725,760,428,465}; // Tomate

    ingredients[6].image = jambon1;
    ingredients[6].x = 724;
    ingredients[6].y = 355;
    ingredients[6].picked = false;
    ingredients[6].zone = (Zone){725, 760, 357,393}; // Tomate

    ingredients[7].image = piZ1;
    ingredients[7].x = 72;
    ingredients[7].y = 535;
    ingredients[7].picked = false;
    ingredients[7].zone = (Zone){72, 105, 531, 569}; // Tomate

}

bool passe_sur_case = false;
bool passe_sur_case1 = false;


int table_x = 568;
int table_y = 612;


int ingredientRamasse = -1;
int ingredientRamasse1 = -1;


void deplace(BITMAP *buffer, Position playerPos, Position playerPos1) {


    Zone tableZone = {568, 609, 183, 219};
    Zone poubelleZone = {338, 379, 322, 360};


    assiette1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    pate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    champi1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\champi.bmp", NULL);
    tomate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    jambon1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\jambon.bmp", NULL);
    olive1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\olive.bmp", NULL);
    piZ1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\piz.bmp", NULL);
    mozza1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);


    if (!assiette1 || !pate1 || !jambon1 || !champi1 || !tomate1 || !piZ1 || !mozza1 || !olive1 ) {
        allegro_message("Erreur lors du chargement de l'image.");
        exit(EXIT_FAILURE);
    }

    // Initialiser les ingrédients au début du jeu
    initIngredients();

    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (255));
    circlefill(buffer, playerPos1.curseur_x, playerPos1.curseur_Y, 7, (12));

    for (int i = 0; i < MAX_INGREDIENTS; i++) {

        if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, ingredients[i].zone)) && key[KEY_V]) {
            ingredients[i].picked = true;
            ingredientRamasse1 = i;
            passe_sur_case1 = true;
        }
        if (passe_sur_case1 && i == ingredientRamasse1) {

            masked_blit(ingredients[i].image, buffer, 0, 0, playerPos1.curseur_x - 10, playerPos1.curseur_Y - 10,
                        ingredients[i].image->w, ingredients[i].image->h);

        }
        if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone )) && key[KEY_V]){
            passe_sur_case1 = false;
            //ingredients[i].picked = false;

        }
        if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone )) && key[KEY_V]){
            passe_sur_case1 = false;
            //ingredients[i].picked = false;

            masked_blit(ingredients[i].image, buffer, 0, 0, table_x, table_y,
                        ingredients[i].image->w, ingredients[i].image->h);

        }

    }


    for (int i = 0; i < MAX_INGREDIENTS; i++) {

        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, ingredients[i].zone)) && key[KEY_L]) {
            ingredients[i].picked = true;
            ingredientRamasse = i;
            passe_sur_case = true;
        }

        if (passe_sur_case && i == ingredientRamasse) {

                masked_blit(ingredients[i].image, buffer, 0, 0, playerPos.curseur_x - 10, playerPos.curseur_Y - 10,
                            ingredients[i].image->w, ingredients[i].image->h);

        }
        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone )) && key[KEY_K]){
            passe_sur_case = false;
            ingredients[i].picked = false;

        }
        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone )) && key[KEY_M]){
            passe_sur_case = false;
            ingredients[i].picked = false;

            masked_blit(ingredients[i].image, buffer, 0, 0, table_x, table_y,
                        ingredients[i].image->w, ingredients[i].image->h);

        }

    }

    blit(buffer,screen,0,0,0,0,800,600);

    for (int i = 0; i < MAX_INGREDIENTS; i++) {
        if (ingredients[i].image) {
            destroy_bitmap(ingredients[i].image);
            ingredients[i].image = NULL;
        }
    }

}