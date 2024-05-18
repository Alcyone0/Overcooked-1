//---------------------------------------anime couteau------------------------------------------------------------
/* #include "Animation.h"
#include <time.h>
#include <allegro.h>


#define MAX_ANGLE 50
#define VITESSE 4.2
#define TEMPS 4500 //en mili


void anime_couteau(BITMAP *image, BITMAP* buffer) {

    image = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled4\\COUTEAU.bmp", NULL);
    if (!image) {
        allegro_message("Impossible de charger l'image couteau");
        return;
    }

    // Position de l'image au centre de l'écran
    int image_x = (SCREEN_W - image->w) / 2;
    int image_y = (SCREEN_H - image->h) / 2;

    // Angle initial de rotation
    float angle = 0;
    // Direction de rotation (1 pour tourner dans le sens horaire, -1 pour tourner dans le sens anti-horaire)
    int rotation_direction = 1;

    // Temps écoulé depuis le début de la rotation
    clock_t start_time = clock();
    clock_t current_time;

    // Boucle de jeu
    while (!key[KEY_ESC]) { //changer
        clear_bitmap(buffer);

        // rotation du couteau
        rotate_sprite(buffer, image, image_x, image_y, ftofix(angle));
        blit(buffer, screen, 0, 0, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN);

        // Mettre à jour l'angle de rotation
        angle += VITESSE * rotation_direction;

        // Inverser la direction de rotation si on atteint l'inclinaison maximale
        if (angle >= MAX_ANGLE) {
            rotation_direction = -1;
        }
            // Revenir à la direction initiale si l'inclinaison est de retour à 0
        else if (angle <= 0) {
            rotation_direction = 1;
        }

        vsync();

        // Mettre à jour le temps écoulé
        current_time = clock();
        if (((float)(current_time - start_time) / CLOCKS_PER_SEC) * 1000 >= TEMPS) {
            break; // Sortir de la boucle si la durée de rotation est atteinte
        }
    }
    destroy_bitmap(buffer);
}

//--------------------------flammes cuisson --------------------------------------------------------------


#define SPRITE_WIDTH 36
#define SPRITE_HEIGHT 42
#define NUM_FRAMES 6

// Vitesse d'animation pour chaque ligne
#define VITESSE_LIGNE1 12
#define VITESSE_LIGNE2 8
#define VITESSE_LIGNE3 6

int vitesse_flammes (int frame_y) {
    if (frame_y < SPRITE_HEIGHT) {
        return VITESSE_LIGNE1;
    } else if (frame_y < SPRITE_HEIGHT * 2) {
        return VITESSE_LIGNE2;
    } else {
        return VITESSE_LIGNE3;
    }
}

void animation_flammes(BITMAP* buffer, BITMAP* sprite_flammes) {
    int frame_index = 0; // Indice de l'image à afficher
    int frame_width = sprite_flammes->w / NUM_FRAMES; // Largeur de chaque image dans la feuille de sprite
    int frame_height = sprite_flammes->h / 3; // Hauteur de chaque ligne dans la feuille de sprite
    int frame_x = 0; // Position x de l'image dans la feuille de sprite
    int frame_y = 0; // Position y de l'image dans la feuille de sprite
    int frame_counter = 0; // Compteur pour contrôler la vitesse de l'animation
    int delay_counter = 0; // Compteur pour contrôler le délai entre les lignes
    int delay_threshold = 7 * 60; // Délai de 7 secondes en termes de frames (60 frames par seconde)


    sprite_flammes = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled4\\flammes.bmp", NULL);
    if (!sprite_flammes) {
        allegro_message("Impossible de charger les flammes");
        return ;
    }

    while (!key[KEY_ESC]) { //chnager
        clear_to_color(buffer, makecol(255, 255, 255)); // Effacer le contenu du buffer

        masked_blit(sprite_flammes, buffer, frame_x, frame_y, 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
        blit(buffer, screen, 0, 0, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN);

        vsync();

        // Contrôler de la vitesse
        frame_counter++;
        if (frame_counter >= vitesse_flammes (frame_y)) {
            // Passer à la frame suivante
            frame_index++;
            if (frame_index >= NUM_FRAMES) {
                frame_index = 0; // Revenir à la première frame
            }

            // Calculer la position x de la nouvelle frame
            frame_x = frame_index * frame_width;

            // Reinitiali
            frame_counter = 0;
        }

        // Contrôler le changement de ligne après un délai de 7 secondes
        delay_counter++;
        if (delay_counter >= delay_threshold) { //fonction pour jouer en mm temps
            // Passer à la ligne suivante
            frame_y += frame_height;
            if (frame_y >= sprite_flammes->h) {
                frame_y = 0; // Revenir à la première ligne
            }
            // Réinitialiser le compteur de délai
            delay_counter = 0;
        }
    }
    destroy_bitmap(buffer);
    destroy_bitmap(sprite_flammes);
}

//------------------------casserole -----------------------------------------------------


#define LARGEUR_IMAGE 54
#define HAUTEUR_IMAGE 46
#define NB_IMAGES_PAR_LIGNE 6
#define VITESSE_ANIMATION 16// Vitesse par frame
#define DUREE_ANIMATION_SECONDES 10 // Durée totale de l'animation en secondes a revoir


void animation_casserole(BITMAP* buffer, BITMAP* sprite_eau) {
    int indice_image = 0;
    int largeur_image = sprite_eau->w / NB_IMAGES_PAR_LIGNE;
    int hauteur_ligne = sprite_eau->h / 3;
    int x_image = 0;
    int y_image = 0;
    int compteur_image = 0;


    sprite_eau = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled4\\casserole.bmp", NULL);
    if (!sprite_eau) {
        allegro_message("Impossible de charger la feuille de sprite de la casserole");
        return ;
    }

    while (!key[KEY_ESC]) { //changer
        clear_to_color(buffer, makecol(255, 255, 255));

        masked_blit(sprite_eau, buffer, x_image, y_image, 0, 0, LARGEUR_IMAGE, HAUTEUR_IMAGE);

        blit(buffer, screen, 0, 0, 0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN);

        vsync();

        compteur_image++;
        if (compteur_image >= VITESSE_ANIMATION) {
            indice_image++;
            if (indice_image >= NB_IMAGES_PAR_LIGNE) {
                indice_image = 0;
                if (y_image == hauteur_ligne * 2) { // Si la troisième ligne
                    y_image = hauteur_ligne * 2; // Restez sur la troisième ligne
                } else {
                    y_image += hauteur_ligne; // ligne suivante
                }
            }

            x_image = indice_image * largeur_image;

            compteur_image = 0;
        }
    }
    destroy_bitmap(buffer);
    destroy_bitmap(sprite_eau);

}
*/
