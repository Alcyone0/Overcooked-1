#include <allegro.h>
#include <stdbool.h>
#include "setup.h"

// Dimensions de la fenêtre
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600

// Taille et vitesse de déplacement des cercles
#define TAILLE_CERCLE 30
#define VITESSE_DEPLACEMENT 5


int main() {
    allegro_init();

    setup();



    return 0;
}
END_OF_MAIN();
