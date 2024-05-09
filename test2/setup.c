//
// Created by ACER on 26/03/2024.
//
#include <stdlib.h>
#include <time.h>
#include "setup.h"
#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>
#include "deplace.h"

// Dimensions de la fenêtre
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600





BITMAP *image, *assiette, *mozza, *pate, *poivron, *olive, *fromage, *champi, *tomate, *piz, *creme, *bacon;
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

    if (assiette) {
        destroy_bitmap(assiette);
        assiette = NULL;
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
}

void loadImages() {
    buffer = create_bitmap(LARGEUR_ECRAN, HAUTEUR_ECRAN);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        exit(EXIT_FAILURE);
    }
    image = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fond.bmp", NULL);
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

    if (!image || !poivron || !assiette || !champi || !olive|| !mozza || !pate || !fromage || !tomate || !piz || !creme || !bacon ) {
        allegro_message("Erreur lors du chargement de l'image1.");
        exit(EXIT_FAILURE);
    }
}


void setup(){

    loadImages();

    install_keyboard();

    makecol(255, 0, 255);

    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche


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

        deplace();

        blit(buffer,screen,0,0,0,0,800,600);

        // Rafraîchir l'écran
        rest(20);
    }

    // Attente de l'appui sur la touche Échap pour quitter
    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }
    cleanupp();

}