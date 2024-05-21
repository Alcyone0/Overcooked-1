#include <allegro.h>
#include "score.h"

void afficherscoretotal(BITMAP *buffer) {
    int text_color = makecol(0, 0, 0);
    int text_x = 10;
    int text_y = 10;
    scoretot = scorejoueur1 + scorejoueur2;
    textprintf_ex(buffer, font, text_x, text_y, text_color, -1, "Score: %d", scoretot);
}

void afficherscoredesjoueurs(BITMAP *buffer, const char *pseudo1, const char *pseudo2) {
    int couleurtexte = makecol(0, 0, 0);
    textprintf_ex(buffer, font, 10, 50, couleurtexte, -1, "Score %s: %d", pseudo1, scorejoueur1);
    textprintf_ex(buffer, font, 10, 90, couleurtexte, -1, "Score %s: %d", pseudo2, scorejoueur2);
}
