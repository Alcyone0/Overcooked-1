//
// Created by ACER on 26/03/2024.
//
#include <stdlib.h>
#include <time.h>
#include "setup.h"
#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>

// Dimensions de la fenêtre
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600

// Taille et vitesse de déplacement des cercles
#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5


typedef struct Command {
    int type;
    struct Command *next;
} Command;

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


void enqueueRandomCommand(Command **queue) {
    int randomType = rand() % 3; // Génère un type de commande aléatoire (0: vert, 1: rose, 2: orange)
    enqueue(queue, randomType); // Ajoute la commande à la file
}


void setup(){
    /*allegro_init();
    // OUVERTURE MODE GRAPHIQUE (ouverture fenêtre allegro)
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGEUR_ECRAN, HAUTEUR_ECRAN, 0, 0) != 0) {
        allegro_message("Erreur lors de l'initialisation du mode graphique.");
        exit(EXIT_FAILURE);
    }*/

    BITMAP *buffer = create_bitmap(LARGEUR_ECRAN, HAUTEUR_ECRAN);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        exit(EXIT_FAILURE);
    }

    BITMAP *image = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\solcuisine.bmp", NULL);
    BITMAP *poubelle = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\poubelle.bmp", NULL);
    BITMAP *decoupe = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\découpe.bmp", NULL);
    BITMAP *assiette = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    BITMAP *mozza = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);
    BITMAP *pain = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    BITMAP *fromage = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fromage.bmp", NULL);
    BITMAP *tomate = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    BITMAP *ingre1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\1.bmp", NULL);
    BITMAP *ingre3 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\3.bmp", NULL);
    BITMAP *ingre2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\2.bmp", NULL);
    BITMAP *ingre4 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\4.bmp", NULL);
    BITMAP *plaque = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\plaque.bmp", NULL);
    BITMAP *clean = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\clean.bmp", NULL);
    BITMAP *glace = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\glace.bmp", NULL);
    BITMAP *plan = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\1.bmp", NULL);
    BITMAP *bacon = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\bacon.bmp", NULL);

    install_keyboard();

    if (!image || !poubelle || !decoupe || !assiette || !mozza || !pain || !fromage || !tomate || !ingre1 || !ingre2 || !ingre3 || !ingre4 || !plaque || !clean || !glace || !plan || !bacon) {
        allegro_message("Erreur lors du chargement de l'image1.");
        exit(EXIT_FAILURE);
    }

    bool dans_zone_assiette = false;

    bool passe_sur_case = false;
    int assiette_x = 290;
    int assiette_y = 250;

    bool passe_sur_case1 = false;
    int bacon_x = 580;
    int bacon_y = 545;

    srand(time(NULL));
    Command *commandQueue = NULL;

    // délai aléatoire pour chauque client
    int delay_vert = rand() % 5000;
    int delay_rose = rand() % 5000;
    int delay_orange = rand() % 5000;

    // Variables de position des cercles
    int cercle_rouge_x =200;
    int cercle_rouge_y = 400;
    int cercle_bleu_x = 500;
    int cercle_bleu_y = 400;
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

    makecol(255, 0, 255);

    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche


    // Boucle de jeu
    while (!key[KEY_ESC]) {

        blit(image, buffer, 0, 0, 0, 0, image->w, image->h);
        blit(decoupe, buffer, 0, 0, 0, 240, decoupe->w, decoupe->h);
        blit(plan, buffer, 0, 0, 280, 240, plan->w, plan->h);
        masked_blit(assiette, buffer, 0, 0, 290, 250, assiette->w, assiette->h);
        blit(mozza, buffer, 0, 0, 0, 520, mozza->w, mozza->h);
        blit(pain, buffer, 0, 0, 80, 520, pain->w, pain->h);
        blit(tomate, buffer, 0, 0, 160, 520, tomate->w, tomate->h);
        blit(fromage, buffer, 0, 0, 240, 520, fromage->w, fromage->h);
        blit(ingre2, buffer, 0, 0, 320, 520, ingre2->w, ingre2->h);
        blit(ingre3, buffer, 0, 0, 400, 520, ingre3->w, ingre3->h);
        blit(ingre4, buffer, 0, 0, 480, 520, ingre4->w, ingre4->h);
        blit(ingre1, buffer, 0, 0, 560, 520, ingre1->w, ingre1->h);
        blit(plaque, buffer, 0, 0, 120, 240, plaque->w, plaque->h);
        blit(plaque, buffer, 0, 0, 200, 240, plaque->w, plaque->h);
        blit(glace, buffer, 0, 0, 360, 242, glace->w, glace->h);
        blit(poubelle, buffer, 0, 0, 545, 240, poubelle->w, poubelle->h);
        masked_blit(bacon, buffer, 0, 0, 575, 545, bacon->w, bacon->h);

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

        // Vérifie si le cercle rouge passe sur les coordonnées spécifiées
        if (((cercle_rouge_x > 460 && cercle_rouge_x < 560 && cercle_rouge_y > 600 && cercle_rouge_y < 520) && !passe_sur_case1) && (key[KEY_P])){
            passe_sur_case1 = true; // Met à jour le drapeau pour indiquer que le cercle a passé les coordonnées spécifiées
             bacon_x = cercle_rouge_x+20; // Positionne l'bacon sur le cercle rouge
            bacon_y = cercle_rouge_y+20;
        }

        // Si le cercle rouge a passé les coordonnées spécifiées, déplacez l'bacon avec le cercle rouge
        if (passe_sur_case1) {
            bacon_x = cercle_rouge_x+20;
            bacon_y = cercle_rouge_y+20;
        }

        masked_blit(bacon, buffer, 0, 0, bacon_x, bacon_y, bacon->w, bacon->h);
        masked_blit(assiette, buffer, 0, 0, assiette_x, assiette_y, assiette->w, assiette->h);


        // Déplacement du cercle rouge avec les flèches du clavier
        if (key[KEY_UP] && cercle_rouge_y > 340) cercle_rouge_y -= VITESSE_DEPLACEMENT;
        if (key[KEY_DOWN] && cercle_rouge_y < 520 - TAILLE_CERCLE) cercle_rouge_y += VITESSE_DEPLACEMENT;
        if (key[KEY_LEFT] && cercle_rouge_x > 0) cercle_rouge_x -= VITESSE_DEPLACEMENT;
        if (key[KEY_RIGHT] && cercle_rouge_x < 680 - TAILLE_CERCLE) cercle_rouge_x += VITESSE_DEPLACEMENT;

        // Déplacement du cercle bleu avec les touches ZQSD
        if (key[KEY_W] && cercle_bleu_y > 340) cercle_bleu_y -= VITESSE_DEPLACEMENT;
        if (key[KEY_S] && cercle_bleu_y < 520 - TAILLE_CERCLE) cercle_bleu_y += VITESSE_DEPLACEMENT;
        if (key[KEY_A] && cercle_bleu_x > 0) cercle_bleu_x -= VITESSE_DEPLACEMENT;
        if (key[KEY_D] && cercle_bleu_x < 680 - TAILLE_CERCLE) cercle_bleu_x += VITESSE_DEPLACEMENT;

        if (cercle_vert_x <500) cercle_vert_x += VITESSE_DEPLACEMENT;

        if (key[KEY_U] )
            while ( cercle_vert_x < 900 ){
                cercle_vert_x += VITESSE_DEPLACEMENT;
            }

        // Dessiner les cercles
        circlefill(buffer, cercle_rouge_x, cercle_rouge_y, TAILLE_CERCLE, makecol(255, 0, 0));
        circlefill(buffer, cercle_bleu_x, cercle_bleu_y, TAILLE_CERCLE, makecol(0, 0, 255));
        circlefill(buffer, cercle_vert_x, cercle_vert_y, TAILLE_CERCLE, makecol(0, 255, 0));
        circlefill(buffer, cercle_rose_x, cercle_rose_y, TAILLE_CERCLE, makecol(255, 0, 255));
        circlefill(buffer, cercle_orange_x, cercle_orange_y, TAILLE_CERCLE, makecol(255, 255, 0));

        blit(buffer,screen,0,0,0,0,800,600);
        // Rafraîchir l'écran
        rest(20);


    }


    // Attente de l'appui sur la touche Échap pour quitter
    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }

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
    destroy_bitmap(bacon);

}