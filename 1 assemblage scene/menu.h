//
// Created by marti on 20/03/2024.
//
#ifndef INC_1_ASSEMBLAGE_SCENE_MENU_H
#define INC_1_ASSEMBLAGE_SCENE_MENU_H
#include <allegro.h>

// Définition des variables globales
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
BITMAP *buffer;
typedef struct {
    BITMAP *background;
    BITMAP *start;
    BITMAP *level;
    BITMAP *settings;
    BITMAP *exit;
    BITMAP *start2;
    BITMAP *level2;
    BITMAP *settings2;
    BITMAP *exit2;
} Menu;

typedef struct {
    BITMAP *background;
    BITMAP *level1;
    BITMAP *level2;
    BITMAP *level3;
    BITMAP *Bouton_return;
    BITMAP *level1r;
    BITMAP *level2r;
    BITMAP *level3r;
    BITMAP *Bouton_return_r;
} Menulvl;

typedef enum {
    MAIN_MENU,
    LEVEL_MENU
} MenuState;


typedef enum {
    NO_SUB_MENU,
    SETTINGS_SUB_MENU
} SubMenuState;

extern MenuState menuState;
extern SubMenuState subMenuState;

// Initialisation d'Allegro
void initAllegro();

// Chargement des images du menu
extern void loadBackground(Menu* menu, Menulvl *lvl);
extern void loadMenuImages(Menu* menu);
extern void loadMenulevel(Menulvl *lvl);

// Affichage du menu principal
extern void showMainMenu(BITMAP *buffer, Menu *menu);
extern void showMenulevel(BITMAP *buffer, Menulvl *lvl);
extern void handleMenuLogic();
// Nettoyage et fermeture d'Allegro
void cleanup(Menu *menu, Menulvl *lvl);

#endif //INC_1_ASSEMBLAGE_SCENE_MENU_H
