#include "clients.h"
#include "plat.h"
#include <allegro.h>
#include <time.h>
#include <stdlib.h>

#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600

// Variables de position des cercles
int cercle_vert_x= 0;
int cercle_vert_y = 150;
int cercle_rose_x= 0;
int cercle_rose_y = 150;
int cercle_orange_x= 0;
int cercle_orange_y = 150;

// variables pour la jauge de temps au dessus des clients
int temps_ecouleR = 0;
int temps_ecouleV = 0;
int temps_ecouleO = 0;
int jauge_xR = 370;
int jauge_xV = 570;
int jauge_xO= 170;

void dessinerclients(BITMAP *buffer, BITMAP *plat_rose, BITMAP *plat_vert, BITMAP *plat_jaune, bool *flag_rose, bool *flag_vert, bool *flag_jaune){


// clients
    circlefill(buffer, cercle_vert_x, cercle_vert_y, TAILLE_CERCLE, makecol(0, 255, 0));
    circlefill(buffer, cercle_rose_x, cercle_rose_y, TAILLE_CERCLE, makecol(255, 0, 255));
    circlefill(buffer, cercle_orange_x, cercle_orange_y, TAILLE_CERCLE, makecol(255, 255, 0));

//Dessin des jauges de temps
// Dessiner la jauge de temps boule rose
    if (cercle_rose_x >= 370) {
        temps_ecouleR += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
        masked_blit(plat_rose, buffer, 0, 0, 255, 0, plat_rose->w, plat_rose->h);
        *flag_rose = true;
    }
    if (temps_ecouleR < 30000) { // Si moins de 30 secondes se sont écoulées
        rectfill(buffer, jauge_xR, 190, jauge_xR + (temps_ecouleR / 500), 205,
                 makecol(255, 0, 255)); // Dessinez une partie de la jauge
    }

// Dessinez la jauge de temps boule verte
    if (cercle_vert_x >= 570) {
        temps_ecouleV += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
        masked_blit(plat_vert, buffer, 0, 0, 455, 0, plat_vert->w, plat_vert->h);
        *flag_vert = true;
    }
    if (temps_ecouleV < 30000) { // Si moins de 30 secondes se sont écoulées
        rectfill(buffer, jauge_xV, 190, jauge_xV + (temps_ecouleV / 500), 205,
                 makecol(0, 255, 0)); // Dessinez une partie de la jauge
    }

// Dessinez la jauge de temps boule orange
    if (cercle_orange_x >= 170) {
        temps_ecouleO += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
        masked_blit(plat_jaune, buffer, 0, 0, 55, 0, plat_jaune->w, plat_jaune->h);
        *flag_jaune = true;
    }
    if (temps_ecouleO < 30000) { // Si moins de 30 secondes se sont écoulées
        rectfill(buffer, jauge_xO, 190, jauge_xO + (temps_ecouleO / 500), 205,
                 makecol(255, 255, 0)); // Dessinez une partie de la jauge
    }
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
    if (key[KEY_U] || temps_ecouleV >= 30000)
        while (cercle_vert_x < 900) {
            cercle_vert_x += VITESSE_DEPLACEMENT;
            temps_ecouleV = 0;
            *flag_vert = false;
        }

// condition pour que la boule rose parte
    if (key[KEY_I] || temps_ecouleR >= 30000) {
        while (cercle_rose_x < 900) {
            cercle_rose_x += VITESSE_DEPLACEMENT;
            temps_ecouleR = 0;
            *flag_rose = false;
        }
    }

// condition pour que la boule orange parte
    if (key[KEY_O] || temps_ecouleO >= 30000)
        while (cercle_orange_x < 900) {
            cercle_orange_x += VITESSE_DEPLACEMENT;
            temps_ecouleO = 0;
            *flag_jaune = false;
        }

// Les boules reviennent
// boule verte
    if (cercle_vert_x > LARGEUR_ECRAN) {
        cercle_vert_x = -TAILLE_CERCLE; // Réinitialisation de la position x
        cercle_vert_y = 150;
        *delay_vert = rand() % 4000 + 2000;
    }

//boule rose
    if (cercle_rose_x > LARGEUR_ECRAN) {
        cercle_rose_x = -TAILLE_CERCLE; // Réinitialisation de la position x
        cercle_rose_y = 150;
        *delay_rose = rand() % 3000 + 1500;
    }

//boule orange
    if (cercle_orange_x > LARGEUR_ECRAN) {
        cercle_orange_x = -TAILLE_CERCLE; // Réinitialisation de la position x
        cercle_orange_y = 150;
        *delay_orange = rand() % 2000 + 1000;
    }

}