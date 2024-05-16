#include <allegro.h>
#include "menu.h"

#include "musique.h"
#include "initiaallegro.h"
#include "nv1.h"


MenuState menuState = MAIN_MENU;


int main() {


    // Initialisation d'Allegro
    initAllegro();
    show_mouse(screen);
    musique();

    // Chargement des images du menu
    Menu mainMenu;
    Menulvl levelMenu;
    loadBackground(&mainMenu, &levelMenu);
    loadMenuImages(&mainMenu);
    loadMenulevel(&levelMenu);

    // Boucle principale
   while (!key[KEY_ESC]) {
        // Gestion de la logique des menus
        handleMenuLogic();

       if (menuState == GAME) {
           // Appel à une fonction pour démarrer le jeu
           nv1(); // Remplacez setupGame() par le nom de la fonction qui initialise votre jeu
           // Sortir de la boucle après le jeu
           break;
       }

        // Affichage du menu principal
        if (menuState == MAIN_MENU) {
            showMainMenu(buffer, &mainMenu);
        }
            // Affichage du menu des niveaux
        else if (menuState == LEVEL_MENU) {
            showMenulevel(buffer, &levelMenu);
        }

        // Afficher le contenu du buffer à l'écran
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Petite pause
        rest(20);
    }

    // Arrêter la musique et libérer la mémoire
    stop_sample(musique);
    destroy_sample(musique);

    // Nettoyage et fermeture d'Allegro
    cleanup(&mainMenu, &levelMenu);

    return 0;



}
END_OF_MAIN()