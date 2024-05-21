
#ifndef OVERCOOKED_SCORE_H
#define OVERCOOKED_SCORE_H

#include <allegro.h>

// Déclaration des variables externes
extern int scoretot;
extern int scorejoueur1;
extern int scorejoueur2;

// Fonction pour afficher le score à l'écran
void afficherscoretotal(BITMAP *buffer);
void afficherscoredesjoueurs(BITMAP *buffer, const char *pseudo1, const char *pseudo2);
//void show_end_screen(BITMAP *buffer,const char *pseudo1, const char *pseudo2, int *scorejoueur1, int *scorejoueur2, int *scoretot);

#endif // OVERCOOKED_SCORE_H
