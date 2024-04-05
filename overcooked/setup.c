#include "setup.h"
#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600

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

    BITMAP *image = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\fond2 (1).bmp", NULL);
    if (!image) {
        allegro_message("Erreur lors du chargement de l'image1.");
        return -1;
    }
    install_keyboard();

    BITMAP *poubelle = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\poubelle (1).bmp", NULL);
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

    /* BITMAP *pain = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
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

     /*BITMAP *ingre1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\1.bmp", NULL);
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
     }*/

    BITMAP *plaque = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\plaque (2).bmp", NULL);
    if (!plaque) {
        allegro_message("Erreur lors du chargement de l'imageE.");
        return -1;
    }

    /*BITMAP *clean = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\clean.bmp", NULL);
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
    } */

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
    int cercle_vert_x= 0;
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
        /*blit(plan, buffer, 0, 0, 280, 240, plan->w, plan->h);*/
        masked_blit(assiette, buffer, 0, 0, 290, 250, assiette->w, assiette->h);
        blit(mozza, buffer, 0, 0, 0, 520, mozza->w, mozza->h);
        /*blit(pain, buffer, 0, 0, 80, 520, pain->w, pain->h);
        blit(tomate, buffer, 0, 0, 160, 520, tomate->w, tomate->h);
        blit(fromage, buffer, 0, 0, 240, 520, fromage->w, fromage->h);
        blit(ingre2, buffer, 0, 0, 320, 520, ingre2->w, ingre2->h);
        blit(ingre3, buffer, 0, 0, 400, 520, ingre3->w, ingre3->h);
        blit(ingre4, buffer, 0, 0, 480, 520, ingre4->w, ingre4->h);
        blit(ingre1, buffer, 0, 0, 560, 520, ingre1->w, ingre1->h);
        blit(plaque, buffer, 0, 0, 120, 240, plaque->w, plaque->h);
        blit(plaque, buffer, 0, 0, 200, 240, plaque->w, plaque->h);*/
        // blit(glace, buffer, 0, 0, 360, 242, glace->w, glace->h);
        blit(poubelle, buffer, 0, 0, 545, 240, poubelle->w, poubelle->h);
        rect(buffer, 0 , 320, 680, 520, makecol(0,0,0));

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

        //blit(clean, buffer, 0, 0, 0, 320, clean->w, clean->h);

        if ((cercle_rouge_x > 277 && cercle_rouge_x < 360 && cercle_rouge_y > 320 && cercle_rouge_y < 360) || (key[KEY_P]) ){
            masked_blit(assiette, buffer, 0, 0, cercle_rouge_x, cercle_rouge_y, assiette->w, assiette->h);
            //cercle_rouge_x = assiette;
        }

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

    while (!key[KEY_ESC]) {
        rest(100); // Attend 100 ms avant de vérifier à nouveau
    }

    // Libération de la mémoire
    destroy_bitmap(image);
    destroy_bitmap(poubelle);
    destroy_bitmap(decoupe);
    destroy_bitmap(assiette);
    /*destroy_bitmap(pain);
    destroy_bitmap(tomate);*/
    destroy_bitmap(mozza);
    // destroy_bitmap(fromage);
    /*destroy_bitmap(ingre1);
    destroy_bitmap(ingre2);
    destroy_bitmap(ingre3);
    destroy_bitmap(ingre4);*/
    destroy_bitmap(plaque);
    destroy_bitmap(buffer);

}