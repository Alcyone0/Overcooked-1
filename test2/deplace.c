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
#include <stdio.h>


//--------------------------------------------------CODE ESTELLE ------------------------------------------------

// Taille et vitesse de déplacement des cercles
#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5
#define MAX_INGREDIENTS 8
#define MAX_INGREDIENTS_RAMASSES 4

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

//--------------------------------------------------------------------FIN CODE ESTELLE ---------------------------------------



// Déclarations globales des variables de position
int cercle_rouge_x = 200;
int cercle_rouge_y = 400;
int cercle_bleu_x = 500;
int cercle_bleu_y = 400;


int curseur_X = 500;
int curseur_y = 410;

int ingredientsRamasses[MAX_INGREDIENTS_RAMASSES]; // Tableau pour les indices des ingrédients ramassés
int nbIngredientsRamasses = 0; // Nombre d'ingrédients actuellement ramassés


typedef struct {
    int curseur_x;
    int curseur_Y;
} Position;

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


int table_x = 568;
int table_y = 612;


int ingredientRamasse = -1;

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



    Zone tableZone = {568, 609, 183, 219};
    Zone poubelleZone = {338, 379, 322, 360};

    //--------------------------------------------------CODE ESTELLE----------------------------------------------------

    srand(time(NULL)); //CODE ESTELLE

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);

    //------------------------------------------------FIN CODE ESTELLE-----------------------------------------------------


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
    pate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    champi1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\champi.bmp", NULL);
    tomate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    jambon1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\jambon.bmp", NULL);
    olive1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\olive.bmp", NULL);
    piZ1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\piz.bmp", NULL);
    mozza1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);

    if (!cuisinier1 || !cuisinier2 || !assiette1 || !pate1 || !jambon1 || !champi1 || !tomate1 || !piZ1 || !mozza1 || !olive1 ) {
        allegro_message("Erreur lors du chargement de l'image.");
        exit(EXIT_FAILURE);
    }

    // Initialiser les ingrédients au début du jeu
    initIngredients();

    // Déplacer et dessiner le cercle rouge (cuisinier 2)
    if (key[KEY_LEFT] && cercle_rouge_x - VITESSE_DEPLACEMENT >= 105 &&
        !isInsideRectangle2(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) &&
        !isInsideRectangle3(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y)) {
        cercle_rouge_x -= VITESSE_DEPLACEMENT;
        directionX_cuisinier2 = -1; // Gauche
        playerPos.curseur_Y = cercle_rouge_y + 40;
        playerPos.curseur_x = cercle_rouge_x - 10;

    }
    if (key[KEY_RIGHT] && cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 725 &&
        !isInsideRectangle2(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y) &&
        !isInsideRectangle3(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)) {
        cercle_rouge_x += VITESSE_DEPLACEMENT;
        directionX_cuisinier2 = 1; // Droite
        playerPos.curseur_Y = cercle_rouge_y + 40;
        playerPos.curseur_x = cercle_rouge_x + 50;

    }
    if (key[KEY_UP] && cercle_rouge_y - VITESSE_DEPLACEMENT >= 180 &&
        !isInsideRectangle2(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT) &&
        !isInsideRectangle3(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)) {
        cercle_rouge_y -= VITESSE_DEPLACEMENT;
        playerPos.curseur_Y = cercle_rouge_y - 10;
        playerPos.curseur_x = cercle_rouge_x + 20;

    }
    if (key[KEY_DOWN] && cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
        !isInsideRectangle2(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
        !isInsideRectangle3(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
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
    if (key[KEY_A] && cercle_bleu_x - VITESSE_DEPLACEMENT >= 105 &&
        !isInsideRectangle1(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y) &&
        !isInsideRectangle4(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)) {
        cercle_bleu_x -= VITESSE_DEPLACEMENT;
        directionX_cuisinier1 = -1; // Gauche
        curseur_y = cercle_bleu_y + 40;
        curseur_X = cercle_bleu_x - 10;
    }
    if (key[KEY_D] && cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 705 &&
        !isInsideRectangle1(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y) &&
        !isInsideRectangle4(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)) {
        cercle_bleu_x += VITESSE_DEPLACEMENT;
        directionX_cuisinier1 = 1; // Droite
        curseur_y = cercle_bleu_y + 35;
        curseur_X = cercle_bleu_x + 70;
    }
    if (key[KEY_W] && cercle_bleu_y - VITESSE_DEPLACEMENT >= 180 &&
        !isInsideRectangle1(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT) &&
        !isInsideRectangle4(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)) {
        cercle_bleu_y -= VITESSE_DEPLACEMENT;
        curseur_y = cercle_bleu_y - 10;
        curseur_X = cercle_bleu_x + 20;
    }
    if (key[KEY_S] && cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
        !isInsideRectangle1(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
        !isInsideRectangle4(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
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


    //----------------------------------------------------------CODE ESTELLE----------------------------------------------------------------

    chargerimage(&plat1, &plat2, &plat3);
    recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,
                   &pos_rose, &pos_vert, &pos_jaune);
    dessinerclients(buffer, plat_rose, plat_vert, plat_jaune, &flag_rose, &flag_vert, &flag_jaune);
    avancerclients(&delay_vert, &delay_rose, &delay_orange);
    revenirclients(&flag_vert, &flag_rose, &flag_jaune, &delay_vert, &delay_rose, &delay_orange);

    //--------------------------------------------------FIN CODE ESTELLE-----------------------------------------------------------


    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (0, 0, 255));
    circlefill(buffer, curseur_X, curseur_y, 7, (0, 12, 12));

    /*for (int i = 0; i < MAX_INGREDIENTS; i++) {
        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, ingredients[i].zone)) && key[KEY_P]) {
            if (nbIngredientsRamasses < MAX_INGREDIENTS_RAMASSES) {
                // Ramasser l'ingrédient en ajoutant son index à la liste des ingrédients ramassés
                ingredientsRamasses[nbIngredientsRamasses++] = i;
                ingredients[i].picked = true;
                passe_sur_case = true;
            }
        }
    }*/

    /*/ Dessiner les ingrédients ramassés à la position du curseur
    for (int j = 0; j < nbIngredientsRamasses; j++) {
        int index = ingredientsRamasses[j];
        if (passe_sur_case && index < MAX_INGREDIENTS && ingredients[index].picked) {
            // Dessiner l'image de l'ingrédient à côté du curseur, en décalant légèrement pour chaque ingrédient empilé
            //int offsetX = j * 20; // Ajustez la valeur de décalage selon vos besoins
            masked_blit(ingredients[index].image, buffer, 0, 0, playerPos.curseur_x - 10 + offsetX, playerPos.curseur_Y - 10,
                        ingredients[index].image->w, ingredients[index].image->h);
        }
    }*/



    for (int i = 0; i < MAX_INGREDIENTS; i++) {

        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, ingredients[i].zone)) && key[KEY_P]) {
            ingredients[i].picked = true;
            ingredientRamasse = i;
            passe_sur_case = true;
        }
        if (passe_sur_case && i == ingredientRamasse) {

                masked_blit(ingredients[i].image, buffer, 0, 0, playerPos.curseur_x - 10, playerPos.curseur_Y - 10,
                            ingredients[i].image->w, ingredients[i].image->h);

        }
        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone )) && key[KEY_P]){
            passe_sur_case = false;
            //ingredients[i].picked = false;

        }
        if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone )) && key[KEY_P]){
            passe_sur_case = false;
            //ingredients[i].picked = false;

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


    //---------------------------------------------------------CODE ESTELLE---------------------------------------------------
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

    //-----------------------------------------------------------FIN CODE ESTELLE----------------------------------------------------
    nbIngredientsRamasses = 0;

}