//
// Created by ACER on 26/03/2024.
//
#include <stdlib.h>
#include <time.h>
#include "setup.h"
#include <allegro.h>
#include <stdbool.h>
#include "deplace.h"
#include "plat.h"
#include "clients.h"

// Dimensions de la fenêtre
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600

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


BITMAP *image, *mozza, *pate, *poivron, *olive, *fromage, *champi, *tomate, *piz, *creme, *bacon, *assiette, *cuisinier1, *cuisinier2 ;
BITMAP *buffer;

void cleanupp() {
    // Libération de la mémoire pour les images chargées
    if (image) {
        destroy_bitmap(image);
        image = NULL;
    }

    if (poivron){
        destroy_bitmap(poivron);
        poivron= NULL;
    }

    if (champi) {
        destroy_bitmap(champi);
        champi = NULL;
    }


    if (olive) {
        destroy_bitmap(olive);
        olive = NULL;
    }

    if (mozza) {
        destroy_bitmap(mozza);
        mozza = NULL;
    }

    if (pate) {
        destroy_bitmap(pate);
        pate = NULL;
    }
    if (assiette) {
        destroy_bitmap(assiette);
        assiette = NULL;
    }
    if (fromage) {
        destroy_bitmap(fromage);
        fromage = NULL;
    }

    if (tomate) {
        destroy_bitmap(tomate);
        tomate = NULL;
    }

    if (piz) {
        destroy_bitmap(piz);
        piz = NULL;
    }

    if (creme) {
        destroy_bitmap(creme);
        creme = NULL;
    }
    if (bacon) {
        destroy_bitmap(bacon);
        bacon = NULL;
    }
    if (cuisinier2) {
        destroy_bitmap(cuisinier2);
        cuisinier2 = NULL;
    }

    if (cuisinier1) {
        destroy_bitmap(cuisinier1);
        cuisinier1 = NULL;
    }

    if (buffer) {
        destroy_bitmap(buffer);
        buffer = NULL;
    }
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

void loadImages() {
    buffer = create_bitmap(LARGEUR_ECRAN, HAUTEUR_ECRAN);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        exit(EXIT_FAILURE);
    }
    image = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fondjeu_nv1.bmp", NULL);
    assiette = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    mozza = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);
    pate = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    fromage = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fromage.bmp", NULL);
    tomate = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    piz = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\piz.bmp", NULL);
    creme = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\creme.bmp", NULL);
    bacon = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\jambon.bmp", NULL);
    champi = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\champi.bmp", NULL);
    olive = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\olive.bmp", NULL);
    poivron = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\poivron.bmp", NULL);
    cuisinier1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier1.bmp", NULL);
    cuisinier2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier2.bmp", NULL);


    if (!image || !poivron || !assiette || !champi || !olive|| !mozza || !pate || !fromage || !tomate || !piz || !creme || !bacon || !cuisinier1 || !cuisinier2) {
        allegro_message("Erreur lors du chargement de l'image1.");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

}

// Déclarations globales des variables de position
int cercle_rouge_x = 200;
int cercle_rouge_y = 400;
int cercle_bleu_x = 500;
int cercle_bleu_y = 400;
int curseur_X = 500;
int curseur_y = 410;

int directionX_cuisinier2 = 1;
int directionX_cuisinier1 = 1; // 1 pour droite, -1 pour gauche

//Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle2(int x, int y) {
    return (x >= 338 && x <= 490 && y >= 220 && y <= 390);
}
// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle3(int x, int y) {
    return (x >= 260 && x <= 570 && y >= 500 && y <= 600);
}
// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle1(int x, int y) {
    return (x >= 328 && x <= 490 && y >= 220 && y <= 405);
}

// Fonction pour vérifier si une position est à l'intérieur du rectangle interdit
bool isInsideRectangle4(int x, int y) {
    return (x >= 235 && x <= 570 && y >= 510 && y <= 600);
}



void setup(){


    loadImages();

    install_keyboard();

    makecol(255, 0, 255);

    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);

    Position playerPos;
    playerPos.curseur_x = cercle_rouge_x; // Par exemple, utilisez la position du cercle rouge
    playerPos.curseur_Y = cercle_rouge_y;

    Position playerPos1;
    playerPos1.curseur_x = cercle_bleu_x; // Par exemple, utilisez la position du cercle rouge
    playerPos1.curseur_Y = cercle_bleu_y;


    // Boucle de jeu
    while (!key[KEY_ESC]) {


        clear_to_color(buffer, makecol(255, 255, 255));

        blit(image, buffer, 0, 0, 0, 0, image->w, image->h);

        masked_blit(assiette, buffer, 0, 0, 455, 320, assiette->w, assiette->h);

        masked_blit(pate, buffer, 0, 0, 72, 255, pate->w, pate->h);
        masked_blit(piz, buffer, 0, 0, 72, 535, piz->w, piz->w);
        masked_blit(mozza, buffer, 0, 0, 72, 470, mozza->w, mozza->h);
        masked_blit(creme, buffer, 0, 0, 72, 400, creme->w, creme->h);
        masked_blit(fromage, buffer, 0, 0, 72, 325, fromage->w, fromage->h);

        masked_blit(tomate, buffer, 0, 0, 726, 566, tomate->w, tomate->w);
        masked_blit(champi, buffer, 0, 0, 724, 293, champi->w, champi->h);
        masked_blit(bacon, buffer, 0, 0, 724, 355, bacon->w, bacon->h);
        masked_blit(olive, buffer, 0, 0, 724, 432, olive->w, olive->h);
        masked_blit(poivron, buffer, 0, 0, 730, 498, poivron->w, poivron->h);

        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);



        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);

       /* if (plat1) {
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
        }*/


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
            playerPos1.curseur_Y= cercle_bleu_y + 40;
            playerPos1.curseur_x = cercle_bleu_x - 10;
        }
        if (key[KEY_D] && cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 705 &&
            !isInsideRectangle1(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y) &&
            !isInsideRectangle4(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)) {
            cercle_bleu_x += VITESSE_DEPLACEMENT;
            directionX_cuisinier1 = 1; // Droite
            playerPos1.curseur_Y = cercle_bleu_y + 35;
            playerPos1.curseur_x = cercle_bleu_x + 70;
        }
        if (key[KEY_W] && cercle_bleu_y - VITESSE_DEPLACEMENT >= 180 &&
            !isInsideRectangle1(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT) &&
            !isInsideRectangle4(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)) {
            cercle_bleu_y -= VITESSE_DEPLACEMENT;
            playerPos1.curseur_Y = cercle_bleu_y - 10;
            playerPos1.curseur_x = cercle_bleu_x + 20;
        }
        if (key[KEY_S] && cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
            !isInsideRectangle1(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle4(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
            cercle_bleu_y += VITESSE_DEPLACEMENT;
            playerPos1.curseur_Y = cercle_bleu_y + 70;
            playerPos1.curseur_x = cercle_bleu_x + 20;
        }

        if (directionX_cuisinier1 == 1) {
            // Dessiner normalement (droite)
            draw_sprite_vh_flip(buffer, cuisinier1, cercle_bleu_x, cercle_bleu_y);
        } else {
            // Dessiner en miroir horizontal (gauche)
            draw_sprite_v_flip(buffer, cuisinier1, cercle_bleu_x, cercle_bleu_y);
        }

        deplace(buffer, playerPos, playerPos1);




        // Rafraîchir l'écran
        rest(20);

    }

    // Attente de l'appui sur la touche Échap pour quitter
    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }

    cleanupp();


}