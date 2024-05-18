//
// Created by marti on 18/05/2024.
//

#include "menu.h"
#include <allegro.h> // Ajout de l'en-tête Allegro
#include <stdbool.h>


// Chargement de l'image de fond
void loadBackground(Menu* menu, Menulvl *lvl) {
    menu->background = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\affiche_ece_cooked_couleur.bmp", NULL);
    lvl->background = menu->background; // Même image pour les deux menus

    if (!menu->background) {
        allegro_message("Erreur : chargement de l'image de fond.");
        exit(EXIT_FAILURE);
    }

}

// Affichage de l'image de fond
void showBackground(BITMAP *buffer, BITMAP *background) {
    clear_bitmap(buffer); // Effacer le contenu précédent du buffer
    draw_sprite(buffer, background, 0, 0); // Afficher l'image de fond
}

void loadMenuImages(Menu* menu) {
    menu->start = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Bouton_sta.bmp", NULL);
    menu->level = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Bouton_lev.bmp", NULL);
    menu->settings = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Bouton_Set.bmp", NULL);
    menu->exit = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Bouton_ex.bmp", NULL);
    menu->start2 = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\start_2.bmp",NULL);
    menu->level2 = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level_2.bmp",NULL);
    menu->settings2 = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\settings_2.bmp",NULL);
    menu->exit2 = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\exit_2.bmp",NULL);


    if (!menu->start || !menu->level || !menu->settings || !menu->exit || !menu->exit2 || !menu->start2 || !menu->settings2 || !menu->level2 ) {
        allegro_message("Error: chargement menu");
        exit(EXIT_FAILURE);
    }
}

void loadMenulevel( Menulvl *lvl) {
    lvl->level1r=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level1_r.bmp",NULL);
    lvl->level2r=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level2r.bmp",NULL);
    lvl->level3r=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level3r.bmp",NULL);
    lvl->Bouton_return_r=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Return2.bmp",NULL);
    lvl->level1=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level1.bmp",NULL);
    lvl->level2=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level2.bmp",NULL);
    lvl->level3=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\level3.bmp",NULL);
    lvl->Bouton_return=load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\return.bmp",NULL);

    if (!lvl->level1 || !lvl->level2|| !lvl->level3||!lvl->Bouton_return || !lvl->level1r || !lvl->level2r || !lvl->level3r ||!lvl->Bouton_return_r){
        allegro_message("Probleme menulevel.");
        exit(EXIT_FAILURE);
    }
}


bool isMouseOverButton(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    return (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight);
}

void drawButton(BITMAP *buffer, BITMAP *normalImage, BITMAP *hoveredImage, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    if (isMouseOverButton(mouse_x, mouse_y, buttonX, buttonY, buttonWidth, buttonHeight)) {
        draw_sprite(buffer, hoveredImage, buttonX, buttonY); // Bouton survolé
    } else {
        draw_sprite(buffer, normalImage, buttonX, buttonY); // Bouton normal
    }
}


void showMainMenu(BITMAP *buffer, Menu *menu) {
    clear_to_color(buffer, makecol(0, 0, 0)); // Effacer le contenu précédent du buffer
    showBackground(buffer, menu->background);
    drawButton(buffer, menu->start, menu->start2, 177, 392,135 ,42);
    drawButton(buffer, menu->level, menu->level2, 402, 392,135,42);
    drawButton(buffer, menu->settings, menu->settings2, 177, 474,135,42);
    drawButton(buffer, menu->exit, menu->exit2, 402, 474,135,42);

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void showMenulevel (BITMAP *buffer, Menulvl *lvl){
    clear_bitmap(buffer); // Effacer le contenu précédent du buffer
    showBackground(buffer, lvl->background);
    drawButton(buffer, lvl->level1, lvl->level1r, 313, 376,120,53);
    drawButton(buffer, lvl->level2, lvl->level2r, 313, 448,120,53);
    drawButton(buffer, lvl->level3, lvl->level3r, 313, 516,120,53);
    drawButton(buffer, lvl->Bouton_return, lvl->Bouton_return_r, 636, 534,105,32);

    // Afficher le buffer sur l'écran
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

bool isMouseOverRegles(int mouseX, int mouseY) {
    return isMouseOverButton(mouseX, mouseY, 636, 534, 105, 42);
}

void showSettings(BITMAP *buffer, MenuS *set) {
    clear_to_color(buffer, makecol(0, 0, 0)); // Effacer le contenu précédent du buffer

    set->regles = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Regles_du_jeu.bmp", NULL);
    set->Bouton_return = load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\return.bmp",NULL);
    set->Bouton_return2 =load_bitmap("C:\\Users\\marti\\OneDrive\\Documents\\Allegro\\untitled7\\IMAGES\\Return2.bmp",NULL);
    if (!set->regles || !set->Bouton_return ||!set->Bouton_return2) {
        allegro_message("Erreur : chargement de l'image des règles ou retours.");
        exit(EXIT_FAILURE);
    }
    draw_sprite(buffer, set->regles, 0, 0);
    drawButton(buffer, set->Bouton_return, set->Bouton_return2, 636, 534,105,32);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


// Fonction pour vérifier si la souris est sur un bouton du menu principal
bool isMouseOverMainMenuButton(int mouseX, int mouseY, int buttonNumber) {
    switch (buttonNumber) {
        case 1:
            return isMouseOverButton(mouseX, mouseY, 177, 392, 135, 42); // Start button
        case 2:
            return isMouseOverButton(mouseX, mouseY, 402, 392, 135, 42); // Level button
        case 3:
            return isMouseOverButton(mouseX, mouseY, 177, 474, 135, 42); // Settings button
        case 4:
            return isMouseOverButton(mouseX, mouseY, 402, 474, 135, 42); // Exit button
        default:
            return false;
    }
}

// Fonction pour vérifier si la souris est sur un bouton du menu de niveau
bool isMouseOverLevelButton(int mouseX, int mouseY, int buttonNumber) {
    switch (buttonNumber) {
        case 1:
            return isMouseOverButton(mouseX, mouseY, 313, 376, 120, 53); // Level 1 button
        case 2:
            return isMouseOverButton(mouseX, mouseY, 313, 448, 120, 53); // Level 2 button
        case 3:
            return isMouseOverButton(mouseX, mouseY, 313, 516, 120, 53); // Level 3 button
        case 4:
            return isMouseOverButton(mouseX, mouseY, 636, 534, 105, 32); // Return button
        default:
            return false;
    }
}

// Fonction pour gérer la logique des menus
void handleMenuLogic() {
    // Logique du menu principal
    if (menuState == MAIN_MENU) {
        if (mouse_b & 1) {
            // Gestion de la souris pour le menu principal
            for (int i = 1; i <= 4; i++) {
                if (isMouseOverMainMenuButton(mouse_x, mouse_y, i)) {
                    switch (i) {
                        case 1:
                            menuState = GAME; // Passer à l'état de jeu
                            break;

                        case 2:
                            menuState = LEVEL_MENU;
                            break;
                        case 3:
                            menuState = SETTINGS;
                            break;
                        case 4:
                            exit(EXIT_SUCCESS);
                            break;
                    }
                    break;
                }
            }
        }
    }
        // Logique du menu de niveau
    else if (menuState == LEVEL_MENU) {
        if (mouse_b & 1) {
            // Gestion de la souris pour le menu de niveau
            for (int i = 1; i <= 4; i++) {
                if (isMouseOverLevelButton(mouse_x, mouse_y, i)) {
                    switch (i) {
                        case 1:
                            allegro_message("Level 1 selected");
                            break;
                        case 2:
                            allegro_message("Level 2 selected");
                            break;
                        case 3:
                            allegro_message("Level 3 selected");
                            break;
                        case 4:
                            menuState = MAIN_MENU;
                            break;
                    }
                    break;
                }
            }
        }
    } else if (menuState == SETTINGS) {
        if (mouse_b & 1) {
            // Gestion de la souris pour le menu de niveau
            for (int i = 1; i <= 4; i++) {
                if (isMouseOverRegles(mouse_x, mouse_y)) {
                    menuState = MAIN_MENU;
                }

            }

        }
    }
}


// Nettoyage et fermeture d'Allegro
void cleanup(Menu *menu, Menulvl *lvl) {
    destroy_bitmap(buffer);
    destroy_bitmap(menu->background);
    destroy_bitmap(menu->start);
    destroy_bitmap(menu->level);
    destroy_bitmap(menu->settings);
    destroy_bitmap(menu->exit);

    destroy_bitmap(lvl->background);
    destroy_bitmap(lvl->level1);
    destroy_bitmap(lvl->level2);
    destroy_bitmap(lvl->level3);
    destroy_bitmap(lvl->Bouton_return);

    allegro_exit();
}

