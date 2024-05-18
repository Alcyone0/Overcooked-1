#include <allegro.h>
#include <stdio.h>

void draw_timer(int minutes, int seconds, int x, int y, int rect_width, int rect_height) {
    // Rectangle bleu marine
    rectfill(screen, x, y, x + rect_width, y + rect_height, makecol(0, 0, 128));

    char timer_text[6];
    snprintf(timer_text, sizeof(timer_text), "%02d:%02d", minutes, seconds);

    // Texte du timer
    textout_ex(screen, font, timer_text, x + 10, y + 10, makecol(255, 255, 255), -1);
}

int main(void) {
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

    clear_to_color(screen, makecol(0, 0, 0));

    int rect_width = 100;
    int rect_height = 30;
    int x = 800 - rect_width;
    int y = 0;

    // Timer initial à 3 minutes (tu peux changer le temps j'ai mis au pif)
    int minutes = 3;
    int seconds = 0;

    while (minutes > 0 || seconds > 0) {
        // Dessin du timer dans le rectangle
        draw_timer(minutes, seconds, x, y, rect_width, rect_height);

        rest(1000);

        if (seconds == 0) {
            if (minutes > 0) {
                minutes--;
                seconds = 59;
            }
        } else {
            seconds--;
        }
    }

    draw_timer(0, 0, x, y, rect_width, rect_height);
    allegro_message("Fin du temps imparti");

    readkey();
    allegro_exit();
    return 0;
} END_OF_MAIN()