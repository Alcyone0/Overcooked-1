#include <allegro.h>
#include "menu.h"
#include "initallegro.h"


MenuState menuState = MAIN_MENU;


int main() {


    // Initialisation d'Allegro
    initAllegro();
    show_mouse(screen);


    // Chargement des images du menu
    Menu mainMenu;
    MenuS set;
    Menulvl levelMenu;
    loadBackground(&mainMenu, &levelMenu);
    loadMenuImages(&mainMenu);
    loadMenulevel(&levelMenu);


    // Boucle principale
    while (!key[KEY_ESC]) {
        // Gestion de la logique des menus
        handleMenuLogic();

        if (menuState == GAME) {

            //nv1(buffer); // Remplacez setupGame() par le nom de la fonction qui initialise votre jeu
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
        else if (menuState == SETTINGS) {
            showSettings(buffer, &set); // Assurez-vous d'avoir défini et initialisé set correctement
        }

        // Afficher le contenu du buffer à l'écran
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        // Petite pause
        rest(20);
    }


    // Nettoyage et fermeture d'Allegro
    cleanup(&mainMenu, &levelMenu);


    return 0;



}
END_OF_MAIN()