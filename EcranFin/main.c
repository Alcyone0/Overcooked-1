#include <allegro.h>
#include <stdio.h>

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

void afficher_score() {
    // Ici il faut reprendre mettre le code de la fonction score
}

// C'est ici qu'il faut remplacer par l'image de fin du jeu
void show_end_screen() {
    clear_to_color(screen, makecol(0, 0, 0));
    textout_centre_ex(screen, font, "Fin du temps imparti", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 255, 255), -1);
    //afficher_score(); //et je pense que cette ligne devrait se mettre là
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

int main(void) {
    run_timer(3);  // Démarrer un timer de 3 minutes
    return 0;
} END_OF_MAIN()