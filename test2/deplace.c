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

bool isInsideZone(int x, int y, Zone zone) {
    return (x >= zone.x_min && x <= zone.x_max && y >= zone.y_min && y <= zone.y_max);
}

bool passe_sur_case = false;
bool passe_sur_case1 = false;
bool passe_sur_case2 = false;
bool passe_sur_case3 = false;
bool passe_sur_case4 = false;


int assiette1_x = 455;
int assiette1_y = 320;

int pate_x = 72;
int pate_y = 255;

int champi_x = 724;
int champi_y = 293;

int tomate_x = 726;
int tomate_y = 566;

int jambon_x = 724;
int jambon_y = 355;


/*int table_x = 568;
int table_y = 612;*/

BITMAP *assiette1, *pate1, *tomate1, *jambon1, *champi1;

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


    Zone assietteZone = {462, 494, 319, 356};
    Zone pateZone = {72, 105, 252, 287};
   Zone tableZone = {568, 609, 183, 219};
   Zone champiZone = {725, 760, 287, 324};
   Zone tomateZone = {725, 760, 568, 600};
   Zone jambonZone = {725, 760, 357, 393};


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
    if (assiette1){
        destroy_bitmap(assiette1);
        assiette1 = NULL;
    }
    if (pate1){
        destroy_bitmap(pate1);
        pate1 = NULL;
    }
    if (tomate1) {
        destroy_bitmap(tomate1);
        tomate1 = NULL;
    }
    if (jambon1){
        destroy_bitmap(jambon1);
        jambon1 = NULL;
    }
    if (champi1){
        destroy_bitmap(champi1);
        champi1 = NULL;
    }

    cuisinier2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier2.bmp", NULL);
    cuisinier1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier1.bmp", NULL);
    assiette1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    pate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    champi1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\champi.bmp", NULL);
    tomate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    jambon1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\jambon.bmp", NULL);

    if (!cuisinier1 || !cuisinier2 || !assiette1 || !pate1 || !jambon1 || !champi1 || !tomate1) {
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

    //circlefill(buffer, cercle_rouge_x + TAILLE_CERCLE / 2, cercle_rouge_y + TAILLE_CERCLE / 2, 7, makecol(0, 0, 255)); // Utilisez makecol pour définir la couleur

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

    if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, assietteZone)) {
        passe_sur_case = true;
    }
    if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, pateZone)) {
        passe_sur_case1 = true;
    }
    if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, champiZone)) {
        passe_sur_case2 = true;
    }
    if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tomateZone)) {
        passe_sur_case3 = true;
    }
    if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, jambonZone)) {
        passe_sur_case4 = true;
    }
   if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone) && key[KEY_U]){
       allegro_message("BRAVO VOUS AVEZ COMPLETE UNE COMMANDE");
        passe_sur_case = false;
        passe_sur_case1 = false;
        passe_sur_case4 = false;
        passe_sur_case3 = false;
        passe_sur_case2 = false;
    }

   /* if (!passe_sur_case){
        assiette1_x = 568;
        assiette1_y = 183;
    }
    if (!passe_sur_case1){
        pate_x = table_x;
        pate_y = table_y;
    }*/

    if (passe_sur_case) {
        assiette1_x = playerPos.curseur_x - 10;
        assiette1_y = playerPos.curseur_Y - 10;
    }
    if (passe_sur_case1) {
        pate_x = playerPos.curseur_x - 10;
        pate_y = playerPos.curseur_Y - 10;
    }
    if (passe_sur_case2) {
        champi_x = playerPos.curseur_x - 10;
        champi_y = playerPos.curseur_Y - 10;
    }
    if (passe_sur_case3) {
        tomate_x = playerPos.curseur_x - 10;
        tomate_y = playerPos.curseur_Y - 10;
    }
    if (passe_sur_case4) {
        jambon_x = playerPos.curseur_x - 10;
        jambon_y = playerPos.curseur_Y - 10;
    }

   /* if ((tomate_x == champi_x == jambon_x == pate_x == assiette1_x) && (tomate_y == champi_y == assiette1_y == jambon_y == pate_y)){
        allegro_message("BRAVO VOUS AVEZ COMPLETE UNE COMMANDE");
    }*/
  /* if (passe_sur_case1 && passe_sur_case &&passe_sur_case2 && passe_sur_case3 && passe_sur_case4){
       allegro_message("BRAVO VOUS AVEZ COMPLETE UNE COMMANDE");
       passe_sur_case4 = false;
   }*/



    //----------------------------------------------------------CODE ESTELLE----------------------------------------------------------------

    chargerimage(&plat1, &plat2, &plat3);
    recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
    dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
    avancerclients(&delay_vert,&delay_rose,&delay_orange);
    revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);

    //--------------------------------------------------FIN CODE ESTELLE-----------------------------------------------------------


    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (0, 0, 255));
    circlefill(buffer, curseur_X, curseur_y, 7, (0, 12, 12));

    masked_blit(assiette1, buffer, 0, 0, assiette1_x, assiette1_y, assiette1->w, assiette1->h);
    masked_blit(pate1, buffer, 0, 0, pate_x, pate_y, pate1->w, pate1->h);
    masked_blit(tomate1, buffer, 0, 0, tomate_x, tomate_y, tomate1->w, tomate1->h);
    masked_blit(champi1, buffer, 0, 0, champi_x, champi_y, champi1->w, champi1->h);
    masked_blit(jambon1, buffer, 0, 0, jambon_x, jambon_y, jambon1->w, jambon1->h);


    blit(buffer,screen,0,0,0,0,800,600);


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


}