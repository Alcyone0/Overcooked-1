//
// Created by ACER on 07/04/2024.
//

#include "commandes.h"
#include <allegro.h>

/*
typedef struct Command {
    int type;
    struct Command *next;
} Command;
void enqueueRandomCommand(Command **queue) {
    int randomType = rand() % 3; // Génère un type de commande aléatoire (0: vert, 1: rose, 2: orange)
    enqueue(queue, randomType); // Ajoute la commande à la file
}
void enqueue(Command **queue, int type) {
    Command *newCommand = (Command*)malloc(sizeof(Command));
    if (newCommand == NULL) {
        return;
    }
    newCommand->type = type;
    newCommand->next = NULL;

    if (*queue == NULL) {
        *queue = newCommand;
    } else {
        Command *current = *queue;
        while (current->next != NULL) {
            current = current->next; // Parcours de la file jusqu'à la fin
        }
        current->next = newCommand; // Ajout de la nouvelle commande à la fin de la file
    }
}
typedef struct Command {
    int type;
    struct Command *next;
} Command;
srand(time(NULL));
Command *commandQueue = NULL;

// délai aléatoire pour chauque client
int delay_vert = rand() % 5000;
int delay_rose = rand() % 5000;
int delay_orange = rand() % 5000;

int cercle_vert_x = 0;
int cercle_vert_y = 120;
int cercle_rose_x= 0;
int cercle_rose_y = 120;
int cercle_orange_x= 0;
int cercle_orange_y = 120;

// variables pour la jauge de temps au dessus des clients
int temps_ecouleR = 0;
int temps_ecouleV = 0;
int temps_ecouleO = 0;
int jauge_xR = 370;
int jauge_xV = 470;
int jauge_xO= 270;

static int countdown = -500;
if (countdown <= 0) {
int randomInterval = rand() % 2000 + 1000;
countdown = randomInterval;
int randomType = rand() % 3; // Génère un type de commande aléatoire (0: vert, 1: rose, 2: orange)
enqueue(&commandQueue, randomType); // Ajoute la commande à la file
}
countdown -= 20;

// Dessinez la jauge de temps boule rose
if (cercle_rose_x >= 400) {
temps_ecouleR += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
}
if (temps_ecouleR < 30000) { // Si moins de 30 secondes se sont écoulées
rectfill(buffer, jauge_xR, 60, jauge_xR + (temps_ecouleR / 500), 75, makecol(255, 0, 255)); // Dessinez une partie de la jauge
}

// Dessinez la jauge de temps boule verte
if (cercle_vert_x >= 3000) {
temps_ecouleV += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
}
if (temps_ecouleV < 30000) { // Si moins de 30 secondes se sont écoulées
rectfill(buffer, jauge_xV, 60, jauge_xV + (temps_ecouleV / 500), 75, makecol(0, 255, 0)); // Dessinez une partie de la jauge
}

// Dessinez la jauge de temps boule orange
if (cercle_orange_x >= 300) {
temps_ecouleO += 20; // Comptez le temps écoulé en millisecondes (20 ms à chaque itération de la boucle)
}
if (temps_ecouleO< 30000) { // Si moins de 30 secondes se sont écoulées
rectfill(buffer, jauge_xO, 60, jauge_xO + (temps_ecouleO / 500), 75, makecol(255, 255, 0)); // Dessinez une partie de la jauge
}

// déplacement automatique du cercle vert (client)
if (delay_vert <= 0 && cercle_vert_x < 500) {
cercle_vert_x += VITESSE_DEPLACEMENT;
} else {
delay_vert -= 20; // Décrémente le délai
}

// déplacement automatique du cercle rose (client)
if (delay_rose <= 0 && cercle_rose_x < 400) {
cercle_rose_x += VITESSE_DEPLACEMENT;
} else {
delay_rose -= 20; // Décrémente le délai
}

// déplacement automatique du cercle orange (client)
if (delay_orange <= 0 && cercle_orange_x < 300) {
cercle_orange_x += VITESSE_DEPLACEMENT;
} else {
delay_orange -= 20; // Décrémente le délai
}

// condition pour que la boule verte parte
if (key[KEY_U] ||temps_ecouleV >= 30000)
while ( cercle_vert_x < 900 ){
cercle_vert_x += VITESSE_DEPLACEMENT;
temps_ecouleV = 0;
}

// condition pour que la boule rose parte
if (key[KEY_I] ||temps_ecouleR >= 30000 )
while ( cercle_rose_x < 900 ){
cercle_rose_x+= VITESSE_DEPLACEMENT;
temps_ecouleR = 0;
}

// condition pour que la boule orange parte
if (key[KEY_O] ||temps_ecouleO >= 30000)
while ( cercle_orange_x < 900 ){
cercle_orange_x += VITESSE_DEPLACEMENT;
temps_ecouleO = 0;
}

// pour que les boules reviennent en mode aléatoire
if ( cercle_vert_x > LARGEUR_ECRAN) {
cercle_vert_x = -TAILLE_CERCLE; // Réinitialisation de la position x
cercle_vert_y = 120;
delay_vert = rand() %  4000 + 2000;
}

if (cercle_rose_x > LARGEUR_ECRAN) {
cercle_rose_x = -TAILLE_CERCLE; // Réinitialisation de la position x
cercle_rose_y = 120;
delay_rose = rand() % 3000 + 1500;
}

if ( cercle_orange_x > LARGEUR_ECRAN) {
cercle_orange_x = -TAILLE_CERCLE; // Réinitialisation de la position x
cercle_orange_y = 120;
delay_orange = rand() % 2000+1000;
}

if (cercle_vert_x <500) cercle_vert_x += VITESSE_DEPLACEMENT;

if (key[KEY_U] )
while ( cercle_vert_x < 900 ){
cercle_vert_x += VITESSE_DEPLACEMENT;
}

circlefill(buffer, cercle_vert_x, cercle_vert_y, TAILLE_CERCLE, makecol(0, 255, 0));
circlefill(buffer, cercle_rose_x, cercle_rose_y, TAILLE_CERCLE, makecol(255, 0, 255));
circlefill(buffer, cercle_orange_x, cercle_orange_y, TAILLE_CERCLE, makecol(255, 255, 0));





 // Libération de la mémoire
    destroy_bitmap(image);
    destroy_bitmap(poubelle);
    destroy_bitmap(decoupe);
    destroy_bitmap(assiette);
    destroy_bitmap(pain);
    destroy_bitmap(tomate);
    destroy_bitmap(mozza);
    destroy_bitmap(fromage);
    destroy_bitmap(ingre1);
    destroy_bitmap(ingre2);
    destroy_bitmap(ingre3);
    destroy_bitmap(ingre4);
    destroy_bitmap(plaque);
    destroy_bitmap(buffer);
    destroy_bitmap(bacon);*/



/*
 *
    bool dans_zone_assiette = false;

    bool passe_sur_case = false;
    int assiette_x = 455;
    int assiette_y = 320;


 // Vérifie si le cercle rouge passe sur les coordonnées spécifiées
        if (((cercle_rouge_x > 277 && cercle_rouge_x < 360 && cercle_rouge_y > 320 && cercle_rouge_y < 360) && !passe_sur_case) && (key[KEY_P])){
            passe_sur_case = true; // Met à jour le drapeau pour indiquer que le cercle a passé les coordonnées spécifiées
            assiette_x = cercle_rouge_x; // Positionne l'assiette sur le cercle rouge
            assiette_y = cercle_rouge_y;
        }

        // Si le cercle rouge a passé les coordonnées spécifiées, déplacez l'assiette avec le cercle rouge
        if (passe_sur_case) {
            assiette_x = cercle_rouge_x;
            assiette_y = cercle_rouge_y;
        }

        masked_blit(assiette, buffer, 0, 0, assiette_x, assiette_y, assiette->w, assiette->h);
*/