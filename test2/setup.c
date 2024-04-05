//
// Created by ACER on 26/03/2024.
//

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

int setup(){
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

    BITMAP *image = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\solcuisine.bmp", NULL);
    if (!image) {
        allegro_message("Erreur lors du chargement de l'image1.");
        return -1;
    }
    install_keyboard();

    BITMAP *poubelle = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\poubelle.bmp", NULL);
    if (!poubelle) {
        allegro_message("Erreur lors du chargement de l'image poubelle.");
        return -1;
    }

    BITMAP *decoupe = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\découpe.bmp", NULL);
    if (!decoupe) {
        allegro_message("Erreur lors du chargement de l'image2.");
        return -1;
    }

    BITMAP *assiette = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
    if (!assiette) {
        allegro_message("Erreur lors du chargement de l'image3.");
        return -1;
    }

    BITMAP *mozza = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);
    if (!mozza) {
        allegro_message("Erreur lors du chargement de l'image4.");
        return -1;
    }

    BITMAP *pain = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
    if (!pain) {
        allegro_message("Erreur lors du chargement de l'image5.");
        return -1;
    }

    BITMAP *fromage = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\fromage.bmp", NULL);
    if (!fromage) {
        allegro_message("Erreur lors du chargement de l'image6.");
        return -1;
    }

    BITMAP *tomate = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
    if (!tomate) {
        allegro_message("Erreur lors du chargement de l'image7.");
        return -1;
    }

    BITMAP *ingre1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\1.bmp", NULL);
    if (!ingre1) {
        allegro_message("Erreur lors du chargement de l'image8.");
        return -1;
    }

    BITMAP *ingre2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\2.bmp", NULL);
    if (!ingre2) {
        allegro_message("Erreur lors du chargement de l'image9.");
        return -1;
    }

    BITMAP *ingre3 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\3.bmp", NULL);
    if (!ingre3) {
        allegro_message("Erreur lors du chargement de l'image0.");
        return -1;
    }

    BITMAP *ingre4 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\4.bmp", NULL);
    if (!ingre4) {
        allegro_message("Erreur lors du chargement de l'imageA.");
        return -1;
    }

    BITMAP *plaque = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\plaque.bmp", NULL);
    if (!plaque) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }

    BITMAP *clean = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\clean.bmp", NULL);
    if (!clean) {
        allegro_message("Erreur lors du chargement de l'imageZ.");
        return -1;
    }

    BITMAP *glace = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\glace.bmp", NULL);
    if (!glace) {
        allegro_message("Erreur lors du chargement de l'imageA.");
        return -1;
    }

    BITMAP *plan = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\1.bmp", NULL);
    if (!plan) {
        allegro_message("Erreur lors du chargement de l'imageZ.");
        return -1;
    }

    BITMAP *bacon = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\bacon.bmp", NULL);
    if (!bacon) {
        allegro_message("Erreur lors du chargement de l'imageZ.");
        return -1;
    }

    bool dans_zone_assiette = false;

    bool passe_sur_case = false;
    int assiette_x = 290;
    int assiette_y = 250;

    bool passe_sur_case1 = false;
    int bacon_x = 580;
    int bacon_y = 545;

    // Variables de position des cercles
    int cercle_rouge_x =200;
    int cercle_rouge_y = 400;
    int cercle_bleu_x = 500;
    int cercle_bleu_y = 400;
    int cercle_vert_x = 0;
    int cercle_vert_y = 120;


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
       // rect(buffer, 0 , 320, 680, 520, makecol(0,0,0));


        //blit(clean, buffer, 0, 0, 0, 320, clean->w, clean->h);


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