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
#include "saisirpseudo.h"
#include <stdio.h>

#define MAX_IMAGES 15

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


char pseudo1[50], pseudo2[50];

int pos_rose ;
int pos_jaune ;
int pos_vert ;


void loadImagesFromFile(ImageInfo images[], int* numImages) {
    FILE* file = fopen("nv1.txt", "r");
    if (!file) {
        allegro_message("Erreur lors de l'ouverture du fichier.");
        exit(EXIT_FAILURE);
    }

    *numImages = 0;
    while (fscanf(file, "%s %d %d", images[*numImages].path, &images[*numImages].x, &images[*numImages].y) == 3) {
        (*numImages)++;
        if (*numImages >= MAX_IMAGES) {
            allegro_message("Trop d'images dans le fichier.");
            break;
        }
    }

    fclose(file);
}
void drawImages(BITMAP* buffer, ImageInfo images[], int numImages) {
    for (int i = 0; i < numImages; ++i) {
        BITMAP* bmp = load_bitmap(images[i].path, NULL);
        if (!bmp) {
            allegro_message("Erreur lors du chargement de l'image.");
            continue;
        }

        masked_blit(bmp, buffer, 0, 0, images[i].x, images[i].y, bmp->w, bmp->h);
        destroy_bitmap(bmp);
    }
}


// Déclarations globales des variables de position
int cercle_rouge_x = 200;
int cercle_rouge_y = 400;
int cercle_bleu_x = 500;
int cercle_bleu_y = 400;
/*int curseur_X = 500;
int curseur_y = 410;*/

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
    srand(time(NULL));

    ImageInfo images[MAX_IMAGES];
    int numImages = 0;

    loadImagesFromFile(images, &numImages);
    BITMAP **loadedImages = malloc(numImages * sizeof(BITMAP *));
    if (!loadedImages) {
        allegro_message("Erreur d'allocation de mémoire pour les images.");
        exit(EXIT_FAILURE);
    }

    // Charger les images et les stocker dans un tableau de pointeurs
    for (int i = 0; i < numImages; ++i) {
        loadedImages[i] = load_bitmap(images[i].path, NULL);
        if (!loadedImages[i]) {
            allegro_message("Erreur lors du chargement de l'image %d.", i);
            exit(EXIT_FAILURE);
        }
    }

    install_keyboard();

    makecol(255, 0, 255);

    BITMAP  *buffer;
    buffer = create_bitmap(800, 600);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        exit(EXIT_FAILURE);
    }
    BITMAP *cuisinier1 = NULL;
    BITMAP *cuisinier2 = NULL;



    cuisinier1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier1.bmp", NULL);
    cuisinier2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier2.bmp", NULL);

    if (!cuisinier1 || !cuisinier2) {
        allegro_message("Erreur lors du chargement de l'image1.");
        exit(EXIT_FAILURE);
    }



    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);

    saisie_pseudos(pseudo1, pseudo2);

    Position playerPos;
    playerPos.curseur_x = cercle_rouge_x; // Par exemple, utilisez la position du cercle rouge
    playerPos.curseur_Y = cercle_rouge_y;

    Position playerPos1;
    playerPos1.curseur_x = cercle_bleu_x; // Par exemple, utilisez la position du cercle rouge
    playerPos1.curseur_Y = cercle_bleu_y;


    // Boucle de jeu
    while (!key[KEY_ESC]) {


        clear_to_color(buffer, makecol(255, 255, 255));
        //drawImages(buffer, images, numImages);

        for (int i = 0; i < numImages; ++i) {
            masked_blit(loadedImages[i], buffer, 0, 0, images[i].x, images[i].y, loadedImages[i]->w, loadedImages[i]->h);
        }

        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);
        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);


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
    // Libérer la mémoire allouée pour les images
    for (int i = 0; i < numImages; ++i) {
        destroy_bitmap(loadedImages[i]);
    }
    free(loadedImages);

    // Libérer les ressources Allegro
    destroy_bitmap(buffer);
    destroy_bitmap(cuisinier1);
    destroy_bitmap(cuisinier2);


}