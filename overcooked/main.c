#include <allegro.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "plat.h"
#include "clients.h"
#include "saisir.h"
#include "score.h"

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

char pseudo1[50], pseudo2[50];

volatile int seconds_left = 0;

void decrement_timer() {
    if (seconds_left > 0) {
        seconds_left--;
    }
}

void draw_timer(int seconds_left, int x, int y, int rect_width, int rect_height) {
    // Dessin du rectangle bleu marine
    rectfill(screen, x, y, x + rect_width, y + rect_height, makecol(0, 0, 128));

    int minutes = seconds_left / 60;
    int seconds = seconds_left % 60;

    char timer_text[6];
    snprintf(timer_text, sizeof(timer_text), "%02d:%02d", minutes, seconds);

    textout_ex(screen, font, timer_text, x + 10, y + 10, makecol(255, 255, 255), -1);
}

void show_end_screen() {
    BITMAP *fintemps = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\tempsfini.bmp", NULL);
    if (!fintemps) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Erreur : Impossible de charger le nouveau fond.");
        return;
    }

    draw_sprite(screen, fintemps, 0, 0);

    rest(2500);
    //image fond pour affichage des pseudos
    BITMAP *scoredefin = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\Design sans titre (1).bmp", NULL);
    if (!scoredefin) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Erreur : Impossible de charger le nouveau fond.");
        return;
    }

    draw_sprite(screen, scoredefin, 0, 0);

    // Afficher les pseudos sur le nouveau fond
    textout_ex(screen, font, pseudo1, 274, 370, makecol(0, 0, 0), -1);
    textout_ex(screen, font, pseudo2, 492, 370, makecol(0, 0, 0), -1);
    // Affiche les scores des joueurs
    //textout_ex(screen, font, scorejoueur1, 210, 400, makecol(255, 255, 255), -1);
    //textout_ex(screen, font, scorejoueur2, 549, 400, makecol(255, 255, 255), -1);
    //affiche le score totale de la partie
    //textout_ex(screen, font, scoretot, 450, 550, makecol(255, 255, 255), -1);
}

void run_timer(int initial_minutes) {
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

    clear_to_color(screen, makecol(0, 0, 0));

    int rect_width = 100;
    int rect_height = 25;
    int x = 800 - rect_width;
    int y = 0;

    seconds_left = initial_minutes * 60;

    install_int(decrement_timer, 1000);

    while (!keypressed() && seconds_left > 0) {
        draw_timer(seconds_left, x, y, rect_width, rect_height);

        // Double buffering pour éviter le scintillement (utile ?)
        acquire_screen();
        release_screen();
    }

    if (seconds_left == 0) {
        show_end_screen();
    }

    readkey();
    allegro_exit();
}


int main() {
    allegro_init();

    // OUVERTURE MODE GRAPHIQUE (ouverture fenêtre allegro)
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGEUR_ECRAN, HAUTEUR_ECRAN, 0, 0) != 0) {
        allegro_message("Erreur lors de l'initialisation du mode graphique.");
        return -1;
    }

    BITMAP *buffer = create_bitmap(LARGEUR_ECRAN, HAUTEUR_ECRAN);
    if (!buffer) {
        allegro_message("Erreur lors de la création du buffer.");
        return -1;
    }

    BITMAP *image = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\fond.bmp", NULL);
    if (!image) {
        allegro_message("Erreur lors du chargement de l'image1.");
        return -1;
    }
    install_keyboard();

    /*BITMAP *poubelle = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\poubelle (1).bmp", NULL);
    if (!poubelle) {
        allegro_message("Erreur lors du chargement de l'image poubelle.");
        return -1;
    }

    BITMAP *decoupe = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\découpe (1).bmp", NULL);
    if (!decoupe) {
        allegro_message("Erreur lors du chargement de l'image2.");
        return -1;
    }

    BITMAP *assiette = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\assiette (1).bmp", NULL);
    if (!assiette) {
        allegro_message("Erreur lors du chargement de l'image3.");
        return -1;
    }

    BITMAP *mozza = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\mozza (1).bmp", NULL);
    if (!mozza) {
        allegro_message("Erreur lors du chargement de l'image4.");
        return -1;
    }

    BITMAP *plaque = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\plaque (2).bmp", NULL);
    if (!plaque) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }*/

    BITMAP *cuisinier1 = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\cuisinier1.bmp", NULL);
    if (!cuisinier1) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }

    BITMAP *cuisinier2 = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\cuisinier2.bmp", NULL);
    if (!cuisinier2) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }

    srand(time(NULL));


    // Variables de position des cercles
    int cercle_rouge_x =200;
    int cercle_rouge_y = 400;
    int cercle_bleu_x = 500;
    int cercle_bleu_y = 400;

    clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le buffer avec la couleur blanche

    // délais aléatoire pour chaque client
    delay_vert = rand() % 4000 + 2000;
    delay_rose = rand() % 3000 + 1500;
    delay_orange = rand() % 2000 + 1000;

    //chargerimage(&plat1, &plat2, &plat3);
    // Saisie des pseudos
    saisie_pseudos(pseudo1, pseudo2);
    run_timer(1);



    // Boucle de jeu
    while (!key[KEY_ESC]) {
        blit(image, buffer, 0, 0, 0, 0, image->w, image->h);
        /*blit(decoupe, buffer, 0, 0, 0, 240, decoupe->w, decoupe->h);
        masked_blit(assiette, buffer, 0, 0, 290, 250, assiette->w, assiette->h);
        blit(mozza, buffer, 0, 0, 0, 520, mozza->w, mozza->h);
        blit(poubelle, buffer, 0, 0, 545, 240, poubelle->w, poubelle->h);*/
        rect(buffer, 0 , 320, 680, 520, makecol(0,0,0));

        choisir_image(plat1,plat2,plat3,&taille),
        chargerimage(&plat1, &plat2, &plat3);
        recupererimage(plat1, plat2, plat3, &plat_rose, &plat_vert, &plat_jaune, &flag_rose, &flag_vert, &flag_jaune,&pos_rose,  &pos_vert, &pos_jaune);
        dessinerclients(buffer, plat_rose, plat_vert, plat_jaune,&flag_rose, &flag_vert, &flag_jaune);
        avancerclients(&delay_vert,&delay_rose,&delay_orange);
        revenirclients(&flag_vert, &flag_rose, &flag_jaune,&delay_vert,&delay_rose,&delay_orange);
        afficherscoretotal(buffer);
        afficherscoredesjoueurs(buffer,pseudo1, pseudo2);

       /* if ((cercle_rouge_x > 277 && cercle_rouge_x < 360 && cercle_rouge_y > 320 && cercle_rouge_y < 360) || (key[KEY_P]) ){
            masked_blit(assiette, buffer, 0, 0, cercle_rouge_x, cercle_rouge_y, assiette->w, assiette->h);
            //cercle_rouge_x = assiette;
        }*/

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


        // Dessiner les cercle
        // cuisiniers
        masked_blit(cuisinier1, buffer, 0, 0, cercle_rouge_x,cercle_rouge_y, cuisinier1->w, cuisinier1->h);
        masked_blit(cuisinier2, buffer, 0, 0, cercle_bleu_x,cercle_bleu_y, cuisinier2->w, cuisinier2->h);

        blit(buffer,screen,0,0,0,0,800,600);
        // Rafraîchir l'écran
        rest(20);
    }

    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }
    // Libération de la mémoire
    destroy_bitmap(plat1);
    destroy_bitmap(plat2);
    destroy_bitmap(plat3);
    destroy_bitmap(image);
    /*destroy_bitmap(poubelle);
    destroy_bitmap(decoupe);
    destroy_bitmap(assiette);
    destroy_bitmap(mozza);
    destroy_bitmap(plaque);*/
    destroy_bitmap(buffer);
    destroy_bitmap(cuisinier1);
    destroy_bitmap(cuisinier2);

    return 0;
}
END_OF_MAIN();