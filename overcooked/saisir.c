#include "saisir.h"
#include <allegro.h>
#include <stdbool.h>

void saisie_pseudos(char *pseudo1, char *pseudo2) {


    // image fond pour la saisie des pseudos
    BITMAP *arriere_plan1 = load_bitmap("C:\\Users\\estel\\Documents\\saisisperso\\saisie des joueurs.bmp", NULL);
    if (!arriere_plan1) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Erreur : Impossible de charger l'image de fond.");
        return;
    }

    draw_sprite(screen, arriere_plan1, 0, 0);

    destroy_bitmap(arriere_plan1);

    textout_ex(screen, font, "Joueur 1 :", 200, 375, makecol(0, 0, 0), -1);
    textout_ex(screen, font, "Joueur 2 :", 200, 465, makecol(0, 0, 0), -1);

    char tampon_saisie1[50] = {0};
    char tampon_saisie2[50] = {0};

    int position_curseur1 = 0;
    int position_curseur2 = 0;

    bool joueur1_saisi = false;
    bool joueur2_saisi = false;

    // Boucle de saisie des pseudos
    while (!key[KEY_ESC] && (!joueur1_saisi || !joueur2_saisi)) {
        if (keypressed()) {
            int touche = readkey();
            int code_ascii = touche & 0xff;
            if (touche >> 8 == KEY_BACKSPACE) {
                if (!joueur1_saisi && position_curseur1 > 0) {
                    position_curseur1--;
                    tampon_saisie1[position_curseur1] = '\0';
                } else if (!joueur2_saisi && position_curseur2 > 0) {
                    position_curseur2--;
                    tampon_saisie2[position_curseur2] = '\0';
                }
            } else if (code_ascii >= 32 && code_ascii <= 126) {
                if (!joueur1_saisi && position_curseur1 < 49) {
                    tampon_saisie1[position_curseur1++] = code_ascii;
                    tampon_saisie1[position_curseur1] = '\0';
                } else if (!joueur2_saisi && position_curseur2 < 49) {
                    tampon_saisie2[position_curseur2++] = code_ascii;
                    tampon_saisie2[position_curseur2] = '\0';
                }
            } else if (touche >> 8 == KEY_ENTER) {
                if (!joueur1_saisi) {
                    joueur1_saisi = true;
                } else if (!joueur2_saisi) {
                    joueur2_saisi = true;
                }
            }
        }

        // Affichage des pseudos en cours de saisie
        textout_ex(screen, font, tampon_saisie1, 300, 375, makecol(0, 0, 0), -1);
        textout_ex(screen, font, tampon_saisie2, 300, 465, makecol(0, 0, 0), -1);
        rest(10);
    }

    // Copie des pseudos saisis
    strcpy(pseudo1, tampon_saisie1);
    strcpy(pseudo2, tampon_saisie2);

    //image fond pour affichage des pseudos
    BITMAP *arriere_plan2 = load_bitmap("C:\\Users\\estel\\Documents\\overcooked\\TOUCHES (1).bmp", NULL);
    if (!arriere_plan2) {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Erreur : Impossible de charger le nouveau fond.");
        return;
    }

    draw_sprite(screen, arriere_plan2, 0, 0);

    // Afficher les pseudos sur le nouveau fond
    textout_ex(screen, font, pseudo1, 240, 340, makecol(0, 0, 0), -1);
    textout_ex(screen, font, pseudo2, 520, 340, makecol(0, 0, 0), -1);

    // on peut entrer dans le jeu si on appuye sur la touche entrer
    bool continuer = false;
    while (!continuer) {
        if (keypressed()) {
            int touche = readkey();
            if ((touche >> 8) == KEY_ENTER) {
                continuer = true;
            }
        }
        rest(10);
    }

    destroy_bitmap(arriere_plan2);

}
