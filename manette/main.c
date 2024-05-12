#include <allegro.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CHAR_SIZE 32
#define DEAD_ZONE 20

//Il y a des trucs que t'as déjà dans ton code et des trucs à garder, je vais te dire les trucs à garder

int main() {
    int character_x = SCREEN_WIDTH / 2 - CHAR_SIZE / 2;
    int character_y = SCREEN_HEIGHT / 2 - CHAR_SIZE / 2;

    allegro_init();
    install_keyboard();
    install_timer();
    install_joystick(JOY_TYPE_AUTODETECT); //A garder : initialisation du joystick

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT); //juste pour le refresh

    //A garder
    if (num_joysticks < 1) {
        allegro_message("Aucun joystick détecté.");
        return 1; //Au lieu de return 1 il faut basculer sur le mode clavier
    }


    while (!key[KEY_ESC]) {
        clear_to_color(buffer, makecol(255, 255, 255));

        char text_buffer[256];

        //Tout garder à partir de là dans la boucle
        poll_joystick();

        //Déplacements du bonhomme
        if (joy_x < -DEAD_ZONE) character_x--;
        if (joy_x >  DEAD_ZONE) character_x++;
        if (joy_y < -DEAD_ZONE) character_y--;
        if (joy_y >  DEAD_ZONE) character_y++;

        if (joy_b3 == 1) {
            sprintf(text_buffer,"Couper"); //Remplacer par la fonction couper
            textout_ex(buffer, font, text_buffer, 10, 10, makecol(0, 0, 255), -1);
        }

        if (joy_b1 == 1) {
            sprintf(text_buffer,"Prendre l'ingrédient"); //Remplacer par la fonction prendre l'ingrédient
            textout_ex(buffer, font, text_buffer, 10, 20, makecol(0, 255, 0), -1);
        }

        //A remplacer par le personnage
        rectfill(buffer, character_x, character_y, character_x + CHAR_SIZE, character_y + CHAR_SIZE, makecol(255, 0, 0));

        //Rafraichissement (à enlever)
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(5);

        // A LAISSER EN COMMENTAIRE : DEBUG AU CAS OU
        /*for (int i = 0; i < num_joysticks; i++) {
            //textprintf_ex("Joystick %d : flag %d\n", i + 1, joy[i].flags);
            //printf("  Nombre de sticks : %d\n", joy[i].num_sticks);
            for (int j = 0; j < joy[i].num_sticks; j++) {
                //printf("    Stick %d : %d axes\n", j + 1, joy[i].stick[j].num_axis);
                for (int k = 0; k < joy[i].stick[j].num_axis; k++) {
                    sprintf(text_buffer,"      Axe %d : name %s, d1 %d, d2 %d, pos %d\n", k + 1, joy[i].stick[j].axis[k].name, joy[i].stick[j].axis[k].d1,  joy[i].stick[j].axis[k].d2,  joy[i].stick[j].axis[k].pos);
                    textout_ex(buffer, font, text_buffer, j*380, k*30, makecol(0, 0, 0), -1);
                }
            }
        }*/
    }

    destroy_bitmap(buffer);
    allegro_exit();
    return 0;
}
END_OF_MAIN()