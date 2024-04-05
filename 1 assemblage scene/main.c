#include <allegro.h>
#include "menu.h"


MenuState menuState = MAIN_MENU;

int main() {
    // Initialisation d'Allegro
    initAllegro();
    show_mouse(screen);

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

    // Nettoyage et fermeture d'Allegro
    cleanup(&mainMenu, &levelMenu);

    return 0;
}
END_OF_MAIN()