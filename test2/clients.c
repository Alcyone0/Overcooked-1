#include "clients.h"
#include "plat.h"
#include <allegro.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600

// Variables de position des cercles
int cercle_vert_x= 0;
int cercle_vert_y = 105;
int cercle_rose_x= 0;
int cercle_rose_y = 105;
int cercle_orange_x= 0;
int cercle_orange_y = 105;

// variables pour la jauge de temps au dessus des clients
int temps_ecouleR = 0;
int temps_ecouleV = 0;
int temps_ecouleO = 0;
int jauge_xR = 370;
int jauge_xV = 570;
int jauge_xO= 170;


void dessinerclients(BITMAP *buffer, BITMAP *plat_rose, BITMAP *plat_vert, BITMAP *plat_jaune, bool *flag_rose, bool *flag_vert, bool *flag_jaune){

    BITMAP *client1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\client1.bmp", NULL);
    BITMAP *client2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cliente1g.bmp", NULL);
    BITMAP *client3 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\client5.bmp", NULL);

// clients
    masked_blit(client1, buffer, 0, 0, cercle_vert_x,cercle_vert_y, client1->w, client1->h);
    masked_blit(client2, buffer, 0, 0, cercle_rose_x,cercle_rose_y, client2->w, client2->h);
    masked_blit(client3, buffer, 0, 0, cercle_orange_x,cercle_orange_y, client2->w, client2->h);

    if (cercle_rose_x >= 370) {
        temps_ecouleR += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
        masked_blit(plat_rose, buffer, 0, 0, 375, 0, plat_rose->w, plat_rose->h);
        *flag_rose = true;
    }
    if (temps_ecouleR < 30000) { // Si moins de 30 secondes se sont écoulées
        rectfill(buffer, jauge_xR, 165, jauge_xR + (temps_ecouleR / 500), 180,
                 makecol(255, 0, 255)); // Dessinez une partie de la jauge
    }

// Dessinez la jauge de temps boule verte
    if (cercle_vert_x >= 570) {
        temps_ecouleV += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
        masked_blit(plat_vert, buffer, 0, 0, 575, 0, plat_vert->w, plat_vert->h);
        *flag_vert = true;
    }
    if (temps_ecouleV < 30000) { // Si moins de 30 secondes se sont écoulées
        rectfill(buffer, jauge_xV, 165, jauge_xV + (temps_ecouleV / 500), 180,
                 makecol(0, 255, 0)); // Dessinez une partie de la jauge
    }

// Dessinez la jauge de temps boule orange
    if (cercle_orange_x >= 170) {
        temps_ecouleO += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
        masked_blit(plat_jaune, buffer, 0, 0, 175, 0, plat_jaune->w, plat_jaune->h);
        *flag_jaune = true;
    }
    if (temps_ecouleO < 30000) { // Si moins de 30 secondes se sont écoulées
        rectfill(buffer, jauge_xO, 165, jauge_xO + (temps_ecouleO / 500), 180,
                 makecol(255, 255, 0)); // Dessinez une partie de la jauge
    }
    destroy_bitmap(client1);
    destroy_bitmap(client2);
    destroy_bitmap(client3);
}

void avancerclients(int *delay_vert, int *delay_rose, int *delay_orange) {
//Déplacement des clients
// déplacement automatique du cercle vert (client)

    if (*delay_vert <= 0 && cercle_vert_x < 600) {
        cercle_vert_x += VITESSE_DEPLACEMENT;
    } else {
        *delay_vert -= 20; // Décrémente le délai
    }

// déplacement automatique du cercle rose (client)
    if (*delay_rose <= 0 && cercle_rose_x < 400) {
        cercle_rose_x += VITESSE_DEPLACEMENT;
    } else {
        *delay_rose -= 20; // Décrémente le délai
    }

// déplacement automatique du cercle orange (client)
    if (*delay_orange <= 0 && cercle_orange_x < 200) {
        cercle_orange_x += VITESSE_DEPLACEMENT;
    } else {
        *delay_orange -= 20; // Décrémente le délai
    }
}

void revenirclients(bool *flag_vert, bool *flag_rose, bool *flag_jaune, int *delay_vert, int *delay_rose, int *delay_orange) {
//Départ des clients
// condition pour que la boule verte parte
    if (key[KEY_U]) {
        while (cercle_vert_x < 900) {
            cercle_vert_x += VITESSE_DEPLACEMENT;
            usleep(1);
            temps_ecouleV = 0;
            *flag_vert = false;
            if (cercle_vert_x >= 900) {
                scorejoueur1 += 10;
                scorejoueur2 += 10;
            }
        }

        // cercle_vert_x = 0;
    }
    else if (temps_ecouleV >= 30000){
        while (cercle_vert_x < 900) {
            cercle_vert_x += VITESSE_DEPLACEMENT;
            usleep(1);
            temps_ecouleV = 0;
            *flag_vert = false;
        }
        scorejoueur1 -= 5;
        scorejoueur2 -= 5;
        cercle_vert_x = 0;
    }

// condition pour que la boule rose parte
    if (key[KEY_I]) {
        while (cercle_rose_x < 900) {
            cercle_rose_x += VITESSE_DEPLACEMENT;
            usleep(1);
            temps_ecouleR = 0;
            *flag_rose = false;
            if (cercle_rose_x >= 900) {
                scorejoueur1 += 10;
                scorejoueur2 += 10;
            }
        }
    }
    else if (temps_ecouleR >= 30000){
        while (cercle_rose_x < 900) {
            cercle_rose_x += VITESSE_DEPLACEMENT;
            usleep(1);
            temps_ecouleR = 0;
            *flag_rose = false;
        }
        scorejoueur1 -= 5;
        scorejoueur2 -= 5;
        cercle_rose_x = 0;
    }

// condition pour que la boule orange parte
    if (key[KEY_O] ) {
        while (cercle_orange_x < 900) {
            cercle_orange_x += VITESSE_DEPLACEMENT;
            usleep(1);
            temps_ecouleO = 0;
            *flag_jaune = false;
            if (cercle_orange_x >= 900) {
                scorejoueur1 += 10;
                scorejoueur2 += 10;
            }
        }
    }
    else if (temps_ecouleO >= 30000){
        while (cercle_orange_x < 900) {
            cercle_orange_x += VITESSE_DEPLACEMENT;
            usleep(1);
            temps_ecouleO = 0;
            *flag_jaune = false;
        }
        scorejoueur1 -= 5;
        scorejoueur2 -= 5;
        cercle_orange_x = 0;
    }

// Les boules reviennent
// boule verte
    if (cercle_vert_x > LARGEUR_ECRAN) {
        cercle_vert_x = -TAILLE_CERCLE; // Réinitialisation de la position x
        cercle_vert_y = 105;
        *delay_vert = rand() % 4000 + 2000;
    }

//boule rose
    if (cercle_rose_x > LARGEUR_ECRAN) {
        cercle_rose_x = -TAILLE_CERCLE; // Réinitialisation de la position x
        cercle_rose_y = 105;
        *delay_rose = rand() % 3000 + 1500;
    }

//boule orange
    if (cercle_orange_x > LARGEUR_ECRAN) {
        cercle_orange_x = -TAILLE_CERCLE; // Réinitialisation de la position x
        cercle_orange_y = 105;
        *delay_orange = rand() % 2000 + 1000;
    }

}