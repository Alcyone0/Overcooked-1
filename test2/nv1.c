#include "nv1.h"
#include <allegro.h>
#include <stdio.h>
#include "saisirpseudo.h"
#include <stdbool.h>
#include "deplace.h"
#include "plat.h"
#include "clients.h"
#include "score.h"
// Taille et vitesse de déplacement des cercles
#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 7

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

int cercle_rouge_x = 200;
int cercle_rouge_y = 400;
int cercle_bleu_x = 500;
int cercle_bleu_y = 400;

int directionX_cuisinier2 = 1;
int directionX_cuisinier1 = 1;

int pos_rose ;
int pos_jaune ;
int pos_vert ;

BITMAP* images[256];
char pseudo1[50], pseudo2[50];

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

void load_images() {
    images[00] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\sol.bmp", NULL);
    images[01] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mur.bmp", NULL);
    images[02] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\decoupe.bmp", NULL);
    images[03] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    images[04] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\poivron.bmp", NULL);
    images[05] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\plaque.bmp", NULL);
    images[06] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fromage.bmp", NULL);
    images[07] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    images[10] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    images[11] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\creme.bmp", NULL);
    images[12] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);
    images[13] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\piz.bmp", NULL);
    images[14] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\champi.bmp", NULL);
    images[15] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\jambon.bmp", NULL);
    images[16] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\olive.bmp", NULL);
    images[17] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\foure.bmp", NULL);
    images[18] = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\poubelle.bmp", NULL);


    if (!images[00] || !images[01] || !images[02] || !images[03] || !images[04] || !images[05] || !images[06] || !images[07] || !images[10] || !images[11] || !images[12] || !images[13] || !images[14] || !images[15] || !images[16] || !images[17] || !images[18])  {
        fprintf(stderr, "Erreur lors du chargement de l'image assiette.bmp\n");
        // Gérer l'erreur ici (par exemple, retourner ou terminer le programme)
    }
    //images['W'] = load_bitmap("counter.bmp", NULL);

}

void display_kitchen(char** layout, int tile_width, int tile_height, BITMAP* buffer) {


    // Afficher les éléments de la cuisine sur le tampon
    for (int row = 0; row < 12; ++row) {
        for (int col = 0; col < 20; ++col) {
            char element = layout[row][col];
            //printf("%c", element);  // Débogage : imprimer le caractère de la disposition
            if (images[element]) {
                // Afficher l'image correspondant à l'élément
                BITMAP *image_to_display = images[element];
                draw_sprite(buffer, image_to_display, 40 + (col * tile_width), 180 + (row * tile_height));
            }
        }
        printf("\n");  // Débogage : sauter une ligne après chaque rangée
    }
}


void unload_images() {
    for (int i = 0; i < sizeof(images) / sizeof(images[0]); ++i) {
        if (images[i]) {
            destroy_bitmap(images[i]);
        }
    }
}


void nv1(BITMAP* buffer) {

    srand(time(NULL));

    install_keyboard();

    saisie_pseudos(pseudo1, pseudo2);

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);

    load_images();

    FILE* layout_file = fopen("niveau1.txt", "r");
    if (!layout_file) {
        perror("Error opening layout file");
        return;
    }

    // Allocation dynamique pour stocker la disposition de la cuisine en tant que tableau d'entiers
    char** kitchen_layout = malloc(12 * sizeof(int*)); // Allocation dynamique pour 13 lignes
    for (int i = 0; i < 12; ++i) {
        kitchen_layout[i] = malloc(20 * sizeof(int)); // Allocation dynamique pour 21 colonnes

        // Lire chaque entier à partir du fichier
        for (int j = 0; j < 20; ++j) {
            if (fscanf(layout_file, "%d", &kitchen_layout[i][j]) != 1) {
                perror("Error reading layout file");
                fclose(layout_file);
                return;
            }
        }
    }
    fclose(layout_file);

    buffer = create_bitmap(800, 600);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        exit(EXIT_FAILURE);
    }
    BITMAP *cuisinier1 = NULL;
    BITMAP *cuisinier2 = NULL;

    BITMAP *fond = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fond.bmp", NULL);
    if (!fond) {
        fprintf(stderr, "Erreur lors du chargement de l'image fondjeu_nv1.bmp\n");
        // Gérer l'erreur ici (par exemple, retourner ou terminer le programme)
    }

    cuisinier1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier1.bmp", NULL);
    cuisinier2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier2.bmp", NULL);

    if (!cuisinier1 || !cuisinier2) {
        allegro_message("Erreur lors du chargement de l'image1.");
        exit(EXIT_FAILURE);
    }

    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche

    Position playerPos;
    playerPos.curseur_x = cercle_rouge_x; // Par exemple, utilisez la position du cercle rouge
    playerPos.curseur_Y = cercle_rouge_y;

    Position playerPos1;
    playerPos1.curseur_x = cercle_bleu_x; // Par exemple, utilisez la position du cercle rouge
    playerPos1.curseur_Y = cercle_bleu_y;

    while (!key[KEY_ESC]) {
        clear_to_color(buffer, makecol(255, 255, 255));
        blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
        // Affichage de la cuisine avec la disposition chargée
        display_kitchen(kitchen_layout, 38, 35, buffer);


        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);
        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);
        afficher_score(buffer, obtenir_score());

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

        rest(50);
    }

    // Attente de l'appui sur la touche Échap pour quitter
    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }

    // Nettoyage de la mémoire allouée
    for (int i = 0; i < 12; ++i) {
        free(kitchen_layout[i]);
    }
    free(kitchen_layout);
    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    destroy_bitmap(cuisinier1);
    destroy_bitmap(cuisinier2);
    unload_images();
}