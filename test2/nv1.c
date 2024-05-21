#include "nv1.h"
#include <allegro.h>
#include <stdio.h>
#include "saisirpseudo.h"
#include <stdbool.h>
#include "deplace.h"
#include "plat.h"
#include "clients.h"
#include "score.h"
#include "timer.h"
#include "menu.h"

#define MAX_ANGLE 50
#define VITESSE 4.2
#define JAUGE_LONGUEUR 85
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
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
int cercle_rouge_y = 530;
int cercle_bleu_x = 600;
int cercle_bleu_y = 530;

int directionX_cuisinier2 = 1;
int directionX_cuisinier1 = 1;

int pos_rose ;
int pos_jaune ;
int pos_vert ;

BITMAP* images[256];
char pseudo1[50], pseudo2[50];
int scorejoueur1 =0;
int scorejoueur2 = 0;
int scoretot = 0;

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

//verifier pour rectangle central
bool isInsideRectangle5(int x, int y) {
    return (x >= 221 && x <= 609 && y >= 281 && y <= 428);
}
// verifier pour MUR QUI SEPARE DU BAS
bool isInsideRectangle6(int x, int y) {
    return (x >= 420 && x <= 455 && y >= 220 && y <= 322);
}
// VERIFIER POUR MUR QUI SEPARE DU HAUT
bool isInsideRectangle7(int x, int y) {
    return (x >= 421 && x <= 458 && y >= 461 && y <= 567);
}


//verifier pour colonne gauche du rectangle centrale
bool isInsideRectangle8(int x, int y) {
    return (x >= 306 && x <= 340 && y >= 300 && y <= 462);
}
// verifier pour colonne droite du rec centrale
bool isInsideRectangle9(int x, int y) {
    return (x >= 523 && x <= 565 && y >= 288 && y <= 462);
}
// VERIFIER pour horizontal haut du rec centrale
bool isInsideRectangle10(int x, int y) {
    return (x >= 306 && x <= 533 && y >= 300 && y <= 340);
}
//pour verifier horizontal du bas rect centrale
bool isInsideRectangle11(int x, int y) {
    return (x >= 306 && x <= 572  && y >= 435 && y <= 470);
}
//rectangle bas pour glace
bool isInsideRectangle12(int x, int y) {
    return (x >= 260 && x <= 570  && y >= 537 && y <= 600);
}
volatile int seconds_left = 0;





        // Si la jauge est vide, fin

        //vsync();


void decrement_timer() {
    if (seconds_left > 0) {
        seconds_left--;
    }
}

void draw_timer(int seconds_left, int x, int y, int rect_width, int rect_height) {

    // Dessin du rectangle bleu marine (tu peux changer la couleur ici si besoin)
    rectfill(screen, x, y, x + rect_width, y + rect_height, makecol(0, 0, 128));

    int minutes = seconds_left / 60;
    int seconds = seconds_left % 60;

    char timer_text[6];
    snprintf(timer_text, sizeof(timer_text), "%02d:%02d", minutes, seconds);

    textout_ex(screen, font, timer_text, x + 10, y + 10, makecol(255, 255, 255), -1);
}

// C'est ici qu'il faut remplacer par l'image de fin du jeu
void show_end_screen() {
    BITMAP *fintemps = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\Fin_du_temps_imparti.bmp", NULL);
    if (!fintemps) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Erreur : Impossible de charger le nouveau fond.");
        return;
    }

    draw_sprite(screen, fintemps, 0, 0);

    rest(2500);

    BITMAP *scoredefin = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\scorefin.bmp", NULL);
    if (!scoredefin) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Erreur : Impossible de charger le nouveau fond.");
        return;
    }

    draw_sprite(screen, scoredefin, 0, 0);

    // Convert integers to strings
    char scorejoueur1_str[12];
    char scorejoueur2_str[12];
    char scoretot_str[12];
    sprintf(scorejoueur1_str, "%d", scorejoueur1);
    sprintf(scorejoueur2_str, "%d", scorejoueur2);
    sprintf(scoretot_str, "%d", scoretot);

    // Afficher les pseudos sur le nouveau fond
    textout_ex(screen, font, pseudo1, 274, 370, makecol(0, 0, 0), -1);
    textout_ex(screen, font, pseudo2, 492, 370, makecol(0, 0, 0), -1);

    // Affiche les scores des joueurs
    textout_ex(screen, font, scorejoueur1_str, 270, 400, makecol(255, 255, 255), -1);
    textout_ex(screen, font, scorejoueur2_str, 509, 400, makecol(255, 255, 255), -1);

    // Affiche le score total de la partie
    textout_ex(screen, font, scoretot_str, 450, 550, makecol(255, 255, 255), -1);
}


void run_timer(int initial_minutes) {
    seconds_left = initial_minutes * 60;

    install_int(decrement_timer, 1000);


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


}

void displaycuisine(char** layout, int tile_width, int tile_height, BITMAP* buffer) {
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

bool finnv3;

void nv3(BITMAP* buffer) {
    finnv3 = false;
    install_keyboard();

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);

    load_images();

    FILE* layout_file = fopen("niveau3.txt", "r");
    if (!layout_file) {
        perror("Error opening layout file");
        return;
    }

    // Allocation dynamique pour stocker la disposition de la cuisine en tant que tableau d'entiers
    char** cuisine_layout = malloc(12 * sizeof(int*)); // Allocation dynamique pour 13 lignes
    for (int i = 0; i < 12; ++i) {
        cuisine_layout[i] = malloc(20 * sizeof(int)); // Allocation dynamique pour 21 colonnes

        // Lire chaque entier à partir du fichier
        for (int j = 0; j < 20; ++j) {
            if (fscanf(layout_file, "%d", &cuisine_layout[i][j]) != 1) {
                perror("Error reading layout file");
                fclose(layout_file);
                return;
            }
        }
    }
    fclose(layout_file);

    BITMAP *cuisinier1 = NULL;
    BITMAP *cuisinier2 = NULL;
    BITMAP* couteau = NULL;



    BITMAP *fond = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fond.bmp", NULL);
    if (!fond) {
        fprintf(stderr, "Erreur lors du chargement de l'image fondjeu_nv1.bmp\n");
        // Gérer l'erreur ici (par exemple, retourner ou terminer le programme)
    }
    // Charger l'image du couteau
    couteau = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\couteau.bmp", NULL);
    if (!couteau) {
        allegro_message("Impossible de charger l'image couteau");
        return;
    }

    // Position de l'image au centre de l'écran
    int image_x = 350;
    int image_y = 310;

// Position initiale de la jauge
    int jauge_x = image_x + 10; // Ajuster la position en fonction du couteau
    int jauge_y = image_y - 20; // Au-dessus du couteau
    int jauge_largeur = JAUGE_LONGUEUR; // Commence pleine
    int jauge_hauteur = 15;
    int jauge_couleur = makecol(0, 255, 0); // Couleur de la jauge (vert)
    int jauge_temps_initial = 4500; // Temps initial de la jauge (en millisecondes)
    int jauge_temps_restant = jauge_temps_initial; // Temps restant de la jauge

    float angle = 0;
    int rotation_direction = 1;

    cuisinier1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier1.bmp", NULL);
    cuisinier2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\cuisinier2.bmp", NULL);

    if (!cuisinier1 || !cuisinier2) {
        allegro_message("Erreur lors du chargement de l'image1.");
        exit(EXIT_FAILURE);
    }

    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche

    cercle_rouge_y = 320;
    cercle_rouge_x = 408;

    Position playerPos;
    playerPos.curseur_x = cercle_rouge_x; // Par exemple, utilisez la position du cercle rouge
    playerPos.curseur_Y = cercle_rouge_y;

    Position playerPos1;
    playerPos1.curseur_x = cercle_bleu_x; // Par exemple, utilisez la position du cercle rouge
    playerPos1.curseur_Y = cercle_bleu_y;


    run_timer(1);

    while (!key[KEY_ESC]&&(!finnv3)) {

        clear_to_color(buffer, makecol(255, 255, 255));
        blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
        // Affichage de la cuisine avec la disposition chargée
        displaycuisine(cuisine_layout, 38, 35, buffer);
        rectfill(buffer, jauge_x, jauge_y, jauge_x + jauge_largeur, jauge_y + jauge_hauteur, jauge_couleur);
        // rotation du couteau
        rotate_sprite(buffer, couteau, image_x, image_y, ftofix(angle));
        //blit(buffer, screen, 0, 0, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN);


        angle += VITESSE * rotation_direction;

        if (angle >= MAX_ANGLE) {
            rotation_direction = -1;
        } else if (angle <= 0) {
            rotation_direction = 1;
        }


        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);
        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);

        afficherscoretotal(buffer);
        afficherscoredesjoueurs(buffer, pseudo1,pseudo2);
        //afficher_score(buffer, obtenir_score());

        // Réduire le temps restant de la jauge si la touche M est pressée
        if (key[KEY_K]) {
            jauge_temps_restant -= 100; // Réduire le temps de 100 ms
            if (jauge_temps_restant < 0) {
                jauge_temps_restant = 0; // Assurer que le temps ne devienne pas négatif
            }
            // Mettre à jour la largeur de la jauge en fonction du temps restant
            jauge_largeur = (jauge_temps_restant * JAUGE_LONGUEUR) / jauge_temps_initial;
        }

        // Réduire le temps restant de la jauge si la touche L est pressée
        if (key[KEY_C]) {
            jauge_temps_restant -= 100; // Réduire le temps de 100 ms
            if (jauge_temps_restant < 0) {
                jauge_temps_restant = 0;
            }
            // Mettre à jour la largeur de la jauge en fonction du temps restant
            jauge_largeur = (jauge_temps_restant * JAUGE_LONGUEUR) / jauge_temps_initial;
        }
        if (jauge_temps_restant <= 0) {
            jauge_temps_restant = 4500;
            jauge_largeur = JAUGE_LONGUEUR;

        }

        if (key[KEY_LEFT] && cercle_rouge_x - VITESSE_DEPLACEMENT >= 105 &&
            !isInsideRectangle8(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle9(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle10(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y)
            &&
            !isInsideRectangle11(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle12(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y)) {
            cercle_rouge_x -= VITESSE_DEPLACEMENT;
            directionX_cuisinier2 = -1; // Gauche
            playerPos.curseur_Y = cercle_rouge_y + 40;
            playerPos.curseur_x = cercle_rouge_x - 10;
        }
        if (key[KEY_RIGHT] && cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 725 &&
            !isInsideRectangle8(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle9(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)
            &&
            !isInsideRectangle10(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle11(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)
            &&
            !isInsideRectangle12(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)) {
            cercle_rouge_x += VITESSE_DEPLACEMENT;
            directionX_cuisinier2 = 1; // Droite
            playerPos.curseur_Y = cercle_rouge_y + 40;
            playerPos.curseur_x = cercle_rouge_x + 50;
        }
        if (key[KEY_UP] && cercle_rouge_y - VITESSE_DEPLACEMENT >= 180 &&
            !isInsideRectangle8(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT) &&
            !isInsideRectangle9(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle10(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle11(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle12(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)) {
            cercle_rouge_y -= VITESSE_DEPLACEMENT;
            playerPos.curseur_Y = cercle_rouge_y - 10;
            playerPos.curseur_x = cercle_rouge_x + 20;
        }
        if (key[KEY_DOWN] && cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
            !isInsideRectangle8(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle9(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle10(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)&&
            !isInsideRectangle11(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle12(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
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
            !isInsideRectangle8(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y) &&
            !isInsideRectangle9(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)
            &&
            !isInsideRectangle10(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)&&
            !isInsideRectangle11(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)
            &&
            !isInsideRectangle12(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)) {
            cercle_bleu_x -= VITESSE_DEPLACEMENT;
            directionX_cuisinier1 = -1; // Gauche
            playerPos1.curseur_Y= cercle_bleu_y + 40;
            playerPos1.curseur_x = cercle_bleu_x - 10;
        }
        if (key[KEY_D] && cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 705 &&
            !isInsideRectangle8(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y) &&
            !isInsideRectangle9(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)&&
            !isInsideRectangle10(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)&&
            !isInsideRectangle11(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)&&
            !isInsideRectangle12(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)) {
            cercle_bleu_x += VITESSE_DEPLACEMENT;
            directionX_cuisinier1 = 1; // Droite
            playerPos1.curseur_Y = cercle_bleu_y + 35;
            playerPos1.curseur_x = cercle_bleu_x + 70;
        }
        if (key[KEY_W] && cercle_bleu_y - VITESSE_DEPLACEMENT >= 180 &&
            !isInsideRectangle8(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT) &&
            !isInsideRectangle9(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle10(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle11(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle12(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)) {
            cercle_bleu_y -= VITESSE_DEPLACEMENT;
            playerPos1.curseur_Y = cercle_bleu_y - 10;
            playerPos1.curseur_x = cercle_bleu_x + 20;
        }
        if (key[KEY_S] && cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
            !isInsideRectangle8(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle9(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)&&
            !isInsideRectangle10(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)&&
            !isInsideRectangle11(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)&&
            !isInsideRectangle12(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
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

       // blit(buffer, screen, 0,0,0,0, 800,600);
        deplace3(buffer, playerPos, playerPos1);
        if (key[KEY_ENTER]){
            finnv3 = false;
            return;
        }

        //run_timer(3);
        draw_timer(seconds_left, 700, 0, 100, 25);
        if (seconds_left == 0) {
            finnv3 = true;
        }

        rest(20);
    }
    while (finnv3){
        clear_to_color(screen, makecol(0, 0, 0));
        // Nettoyage de la mémoire allouée
        show_end_screen();
        rest(5000);
        //
        return;

    }

    // Attente de l'appui sur la touche Échap pour quitter
    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }

    // Nettoyage de la mémoire allouée
    for (int i = 0; i < 12; ++i) {
        free(cuisine_layout[i]);
    }
    free(cuisine_layout);
    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    destroy_bitmap(cuisinier1);
    destroy_bitmap(cuisinier2);
    unload_images();
}

bool finnv2;

void nv2(BITMAP* buffer) {

    install_keyboard();

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    chargerimage(&plat1, &plat2, &plat3);

    load_images();

    FILE* layout_file = fopen("niveau2.txt", "r");
    if (!layout_file) {
        perror("Error opening layout file");
        return;
    }

    // Allocation dynamique pour stocker la disposition de la cuisine en tant que tableau d'entiers
    char** cuisine_layout = malloc(12 * sizeof(int*)); // Allocation dynamique pour 13 lignes
    for (int i = 0; i < 12; ++i) {
        cuisine_layout[i] = malloc(20 * sizeof(int)); // Allocation dynamique pour 21 colonnes

        // Lire chaque entier à partir du fichier
        for (int j = 0; j < 20; ++j) {
            if (fscanf(layout_file, "%d", &cuisine_layout[i][j]) != 1) {
                perror("Error reading layout file");
                fclose(layout_file);
                return;
            }
        }
    }
    fclose(layout_file);


    BITMAP *cuisinier1 = NULL;
    BITMAP *cuisinier2 = NULL;
    BITMAP *couteau;
    // Charger l'image du couteau
    couteau = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\couteau.bmp", NULL);
    if (!couteau) {
        allegro_message("Impossible de charger l'image couteau");
        return;
    }

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
    // Position de l'image au centre de l'écran
    int image_x = 570;
    int image_y = 370;

// Position initiale de la jauge
    int jauge_x = image_x + 10; // Ajuster la position en fonction du couteau
    int jauge_y = image_y - 20; // Au-dessus du couteau
    int jauge_largeur = JAUGE_LONGUEUR; // Commence pleine
    int jauge_hauteur = 15;
    int jauge_couleur = makecol(0, 255, 0); // Couleur de la jauge (vert)
    int jauge_temps_initial = 4500; // Temps initial de la jauge (en millisecondes)
    int jauge_temps_restant = jauge_temps_initial; // Temps restant de la jauge

    float angle = 0;
    int rotation_direction = 1;


    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche

    cercle_rouge_x = 200;
    cercle_rouge_y = 530;
    cercle_bleu_x = 600;
    cercle_bleu_y = 539;

    Position playerPos;
    playerPos.curseur_x = cercle_rouge_x; // Par exemple, utilisez la position du cercle rouge
    playerPos.curseur_Y = cercle_rouge_y;

    Position playerPos1;
    playerPos1.curseur_x = cercle_bleu_x; // Par exemple, utilisez la position du cercle rouge
    playerPos1.curseur_Y = cercle_bleu_y;

    run_timer(1);
   // afficher_score(buffer, obtenir_score());

    while (!key[KEY_ESC] && (!finnv2)) {

        clear_to_color(buffer, makecol(255, 255, 255));
        blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
        // Affichage de la cuisine avec la disposition chargée
        displaycuisine(cuisine_layout, 38, 35, buffer);
        rectfill(buffer, jauge_x, jauge_y, jauge_x + jauge_largeur, jauge_y + jauge_hauteur, jauge_couleur);
        // rotation du couteau
        rotate_sprite(buffer, couteau, image_x, image_y, ftofix(angle));

        angle += VITESSE * rotation_direction;

        if (angle >= MAX_ANGLE) {
            rotation_direction = -1;
        } else if (angle <= 0) {
            rotation_direction = 1;
        }


        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);
        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);

        //afficher_score(buffer, obtenir_score());
        afficherscoretotal(buffer);
        afficherscoredesjoueurs(buffer, pseudo1,pseudo2);

        // Réduire le temps restant de la jauge si la touche M est pressée
        if (key[KEY_K]) {
            jauge_temps_restant -= 100; // Réduire le temps de 100 ms
            if (jauge_temps_restant < 0) {
                jauge_temps_restant = 0; // Assurer que le temps ne devienne pas négatif
            }
            // Mettre à jour la largeur de la jauge en fonction du temps restant
            jauge_largeur = (jauge_temps_restant * JAUGE_LONGUEUR) / jauge_temps_initial;
        }

        // Réduire le temps restant de la jauge si la touche L est pressée
        if (key[KEY_C]) {
            jauge_temps_restant -= 100; // Réduire le temps de 100 ms
            if (jauge_temps_restant < 0) {
                jauge_temps_restant = 0;
            }
            // Mettre à jour la largeur de la jauge en fonction du temps restant
            jauge_largeur = (jauge_temps_restant * JAUGE_LONGUEUR) / jauge_temps_initial;
        }
        if (jauge_temps_restant <= 0) {
            jauge_temps_restant = 4500;
            jauge_largeur = JAUGE_LONGUEUR;

        }

        if (key[KEY_LEFT] && cercle_rouge_x - VITESSE_DEPLACEMENT >= 105 &&
            !isInsideRectangle5(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle6(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle7(cercle_rouge_x - VITESSE_DEPLACEMENT, cercle_rouge_y)) {
            cercle_rouge_x -= VITESSE_DEPLACEMENT;
            directionX_cuisinier2 = -1; // Gauche
            playerPos.curseur_Y = cercle_rouge_y + 40;
            playerPos.curseur_x = cercle_rouge_x - 10;
        }
        if (key[KEY_RIGHT] && cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 725 &&
            !isInsideRectangle5(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y) &&
            !isInsideRectangle6(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)
            &&
            !isInsideRectangle7(cercle_rouge_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_rouge_y)) {
            cercle_rouge_x += VITESSE_DEPLACEMENT;
            directionX_cuisinier2 = 1; // Droite
            playerPos.curseur_Y = cercle_rouge_y + 40;
            playerPos.curseur_x = cercle_rouge_x + 50;
        }
        if (key[KEY_UP] && cercle_rouge_y - VITESSE_DEPLACEMENT >= 180 &&
            !isInsideRectangle5(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT) &&
            !isInsideRectangle6(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle7(cercle_rouge_x, cercle_rouge_y - VITESSE_DEPLACEMENT)) {
            cercle_rouge_y -= VITESSE_DEPLACEMENT;
            playerPos.curseur_Y = cercle_rouge_y - 10;
            playerPos.curseur_x = cercle_rouge_x + 20;
        }
        if (key[KEY_DOWN] && cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
            !isInsideRectangle5(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle6(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle7(cercle_rouge_x, cercle_rouge_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
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
            !isInsideRectangle5(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y) &&
            !isInsideRectangle6(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)
            &&
            !isInsideRectangle7(cercle_bleu_x - VITESSE_DEPLACEMENT, cercle_bleu_y)) {
            cercle_bleu_x -= VITESSE_DEPLACEMENT;
            directionX_cuisinier1 = -1; // Gauche
            playerPos1.curseur_Y= cercle_bleu_y + 40;
            playerPos1.curseur_x = cercle_bleu_x - 10;
        }
        if (key[KEY_D] && cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 705 &&
            !isInsideRectangle5(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y) &&
            !isInsideRectangle6(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)&&
            !isInsideRectangle7(cercle_bleu_x + TAILLE_CERCLE + VITESSE_DEPLACEMENT, cercle_bleu_y)) {
            cercle_bleu_x += VITESSE_DEPLACEMENT;
            directionX_cuisinier1 = 1; // Droite
            playerPos1.curseur_Y = cercle_bleu_y + 35;
            playerPos1.curseur_x = cercle_bleu_x + 70;
        }
        if (key[KEY_W] && cercle_bleu_y - VITESSE_DEPLACEMENT >= 180 &&
            !isInsideRectangle5(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT) &&
            !isInsideRectangle6(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)&&
            !isInsideRectangle7(cercle_bleu_x, cercle_bleu_y - VITESSE_DEPLACEMENT)) {
            cercle_bleu_y -= VITESSE_DEPLACEMENT;
            playerPos1.curseur_Y = cercle_bleu_y - 10;
            playerPos1.curseur_x = cercle_bleu_x + 20;
        }
        if (key[KEY_S] && cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT <= 570 &&
            !isInsideRectangle5(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT) &&
            !isInsideRectangle6(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)&&
            !isInsideRectangle7(cercle_bleu_x, cercle_bleu_y + TAILLE_CERCLE + VITESSE_DEPLACEMENT)) {
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

        blit(buffer, screen, 0,0,0,0, 800,600);
        deplace2(buffer, playerPos, playerPos1);


        if (key[KEY_ENTER]){
            finnv2 = false;
            return;

        }
        draw_timer(seconds_left, 700, 0, 100, 25);
        if (seconds_left == 0){
            finnv2 = true;
        }

        rest(20);
    }
    while (finnv2){
        clear_to_color(screen, makecol(0, 0, 0));
        // Nettoyage de la mémoire allouée
        show_end_screen();
        rest(5000);
        //destroy_bitmap(buffer);
        nv3(buffer);
    }

    // Attente de l'appui sur la touche Échap pour quitter
    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }

    // Nettoyage de la mémoire allouée
    for (int i = 0; i < 12; ++i) {
        free(cuisine_layout[i]);
    }
    free(cuisine_layout);
    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    destroy_bitmap(cuisinier1);
    destroy_bitmap(cuisinier2);
    unload_images();
}

bool finnv1;
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
    char** cuisine_layout = malloc(12 * sizeof(int*)); // Allocation dynamique pour 13 lignes
    for (int i = 0; i < 12; ++i) {
        cuisine_layout[i] = malloc(20 * sizeof(int)); // Allocation dynamique pour 21 colonnes

        // Lire chaque entier à partir du fichier
        for (int j = 0; j < 20; ++j) {
            if (fscanf(layout_file, "%d", &cuisine_layout[i][j]) != 1) {
                perror("Error reading layout file");
                fclose(layout_file);
                return;
            }
        }
    }
    fclose(layout_file);

    // Position de l'image au centre de l'écran
    int image_x = 505;
    int image_y = 530;

// Position initiale de la jauge
    int jauge_x = image_x + 10; // Ajuster la position en fonction du couteau
    int jauge_y = image_y - 20; // Au-dessus du couteau
    int jauge_largeur = JAUGE_LONGUEUR; // Commence pleine
    int jauge_hauteur = 15;
    int jauge_couleur = makecol(0, 255, 0); // Couleur de la jauge (vert)
    int jauge_temps_initial = 4500; // Temps initial de la jauge (en millisecondes)
    int jauge_temps_restant = jauge_temps_initial; // Temps restant de la jauge

    float angle = 0;
    int rotation_direction = 1;

    buffer = create_bitmap(800, 600);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        exit(EXIT_FAILURE);
    }
    BITMAP *cuisinier1 = NULL;
    BITMAP *cuisinier2 = NULL;
    BITMAP *couteau;

    BITMAP *fond = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fond.bmp", NULL);
    if (!fond) {
        fprintf(stderr, "Erreur lors du chargement de l'image fondjeu_nv1.bmp\n");
        // Gérer l'erreur ici (par exemple, retourner ou terminer le programme)
    }
    // Charger l'image du couteau
    couteau = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\couteau.bmp", NULL);
    if (!couteau) {
        allegro_message("Impossible de charger l'image couteau");
        return;
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

    run_timer(1);
    while (!key[KEY_ESC]&&(!finnv1)) {

        clear_to_color(buffer, makecol(255, 255, 255));
        blit(fond, buffer, 0, 0, 0, 0, fond->w, fond->h);
        // Affichage de la cuisine avec la disposition chargée
        displaycuisine(cuisine_layout, 38, 35, buffer);
        rectfill(buffer, jauge_x, jauge_y, jauge_x + jauge_largeur, jauge_y + jauge_hauteur, jauge_couleur);
        // rotation du couteau
        rotate_sprite(buffer, couteau, image_x, image_y, ftofix(angle));

        angle += VITESSE * rotation_direction;

        if (angle >= MAX_ANGLE) {
            rotation_direction = -1;
        } else if (angle <= 0) {
            rotation_direction = 1;
        }

        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);
        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);
        //afficher_score(buffer, obtenir_score());

        afficherscoretotal(buffer);
        afficherscoredesjoueurs(buffer, pseudo1, pseudo2);

        // Réduire le temps restant de la jauge si la touche M est pressée
        if (key[KEY_K]) {
            jauge_temps_restant -= 100; // Réduire le temps de 100 ms
            if (jauge_temps_restant < 0) {
                jauge_temps_restant = 0; // Assurer que le temps ne devienne pas négatif
            }
            // Mettre à jour la largeur de la jauge en fonction du temps restant
            jauge_largeur = (jauge_temps_restant * JAUGE_LONGUEUR) / jauge_temps_initial;
        }

        // Réduire le temps restant de la jauge si la touche L est pressée
        if (key[KEY_C]) {
            jauge_temps_restant -= 100; // Réduire le temps de 100 ms
            if (jauge_temps_restant < 0) {
                jauge_temps_restant = 0;
            }
            // Mettre à jour la largeur de la jauge en fonction du temps restant
            jauge_largeur = (jauge_temps_restant * JAUGE_LONGUEUR) / jauge_temps_initial;
        }
        if (jauge_temps_restant <= 0) {
            jauge_temps_restant = 4500;
            jauge_largeur = JAUGE_LONGUEUR;

        }

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

        /*if (key[KEY_ENTER]){
            //finnv1 = false;
            return;
        }*/


        draw_timer(seconds_left, 700, 0, 100, 25);
        if (seconds_left == 0) {
            finnv1 = true;
        }

        rest(20);
    }
    while (finnv1){
        clear_to_color(screen, makecol(0, 0, 0));
         show_end_screen();
        rest(5000);
        //destroy_bitmap(buffer);
        nv2(buffer);
    }



    // Nettoyage de la mémoire allouée
    for (int i = 0; i < 12; ++i) {
        free(cuisine_layout[i]);
    }
    free(cuisine_layout);
    destroy_bitmap(buffer);
    destroy_bitmap(fond);
    destroy_bitmap(cuisinier1);
    destroy_bitmap(cuisinier2);
    unload_images();
}