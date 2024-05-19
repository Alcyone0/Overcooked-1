#ifndef OVERCOOKED_SCORE_H
#define OVERCOOKED_SCORE_H

#include <allegro.h>

// Déclaration des variables externes
extern int scorejoueur1;
extern int scorejoueur2;
extern int scoretot;

// Fonction pour afficher le score à l'écran
void afficherscoretotal(BITMAP *buffer);
void afficherscoredesjoueurs(BITMAP *buffer, const char *pseudo1, const char *pseudo2);

#endif // OVERCOOKED_SCORE_H
