#include <allegro.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define BALL_SIZE 100

volatile int ticks = 0;
volatile int vitesse = 1;

SAMPLE *ding_sound;

void ticker() {
    ticks++;
}
END_OF_FUNCTION(ticker)

int main() {
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
    install_timer();
    install_int_ex(ticker, BPS_TO_TIMER(60));

    // Chargement du son "ding"
    ding_sound = load_sample("C:\\Users\\jeann\\Documents\\Allegro\\Sons\\cmake-build-debug\\sons\\doorbell.wav");
    if (!ding_sound) {
        allegro_message("Erreur dans le chargement du son");
        return 1;
    }

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(buffer, makecol(0, 0, 0));

    int ball1_x = SCREEN_W / 4;
    int ball1_y = SCREEN_H / 2;
    int ball1_dx = vitesse;
    int ball1_dy = vitesse;
    int ball1_color = makecol(255, 255, 255);

    int ball2_x = 3 * SCREEN_W / 4;
    int ball2_y = SCREEN_H / 2;
    int ball2_dx = -vitesse;
    int ball2_dy = -vitesse;
    int ball2_color = makecol(255, 255, 255);

    while (!key[KEY_ESC]) {
        if (ticks % 2 == 0) {
            ball1_x += ball1_dx;
            ball1_y += ball1_dy;

            ball2_x += ball2_dx;
            ball2_y += ball2_dy;

            if (ball1_x < BALL_SIZE / 2 || ball1_x > SCREEN_W - BALL_SIZE / 2) {
                ball1_dx = -ball1_dx;
                ball1_color = makecol(rand() % 256, rand() % 256, rand() % 256);
                play_sample(ding_sound, 255, 128, 1000, FALSE);
            }
            if (ball1_y < BALL_SIZE / 2 || ball1_y > SCREEN_H - BALL_SIZE / 2) {
                ball1_dy = -ball1_dy;
                ball1_color = makecol(rand() % 256, rand() % 256, rand() % 256);
                play_sample(ding_sound, 255, 128, 1000, FALSE);
            }

            if (ball2_x < BALL_SIZE / 2 || ball2_x > SCREEN_W - BALL_SIZE / 2) {
                ball2_dx = -ball2_dx;
                ball2_color = makecol(rand() % 256, rand() % 256, rand() % 256);
                play_sample(ding_sound, 255, 128, 1000, FALSE);
            }
            if (ball2_y < BALL_SIZE / 2 || ball2_y > SCREEN_H - BALL_SIZE / 2) {
                ball2_dy = -ball2_dy;
                ball2_color = makecol(rand() % 256, rand() % 256, rand() % 256);
                play_sample(ding_sound, 255, 128, 1000, FALSE);
            }

            clear_to_color(buffer, makecol(0, 0, 0));

            circlefill(buffer, ball1_x, ball1_y, BALL_SIZE / 2, ball1_color);
            circlefill(buffer, ball2_x, ball2_y, BALL_SIZE / 2, ball2_color);

            stretch_blit(buffer, screen, 0, 0, SCREEN_W, SCREEN_H, 0, 0, SCREEN_W, SCREEN_H);
        }
    }

    destroy_sample(ding_sound);
    destroy_bitmap(buffer);
    return 0;
}
END_OF_MAIN()
