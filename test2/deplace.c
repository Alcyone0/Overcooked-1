#include "deplace.h"
#include <allegro.h>
#include <stdbool.h>
#include <stdlib.h>
#include "nv1.h"

#define MAX_INGREDIENTS 8
#define MAX_PICKED_INGREDIENTS 16

typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
} Zone;

typedef struct {
    BITMAP *image;
    int x;
    int y;
    bool picked;
    Zone zone; // Zone pour la détection de ramassage
    bool inPoubelle;
} Ingredient;

Ingredient ingredients[MAX_INGREDIENTS];
Ingredient pickedIngredients[MAX_PICKED_INGREDIENTS];

int numPickedIngredients = 0;

bool isInsideZone(int x, int y, Zone zone) {
    return (x >= zone.x_min && x <= zone.x_max && y >= zone.y_min && y <= zone.y_max);
}

BITMAP *champi1, *tomate1, *assiette1, *pate1, *jambon1, *mozza1, *piZ1, *olive1;

void initIngredients() {
    // Initialiser chaque ingrédient avec son image, sa position et sa zone de ramassage
    ingredients[0].image = champi1;
    ingredients[0].x = 724;
    ingredients[0].y = 293;
    ingredients[0].picked = false;
    ingredients[0].inPoubelle = false;
    ingredients[0].zone = (Zone){724, 760, 287, 324}; // Champignon

    ingredients[1].image = tomate1;
    ingredients[1].x = 726;
    ingredients[1].y = 566;
    ingredients[1].picked = false;
    ingredients[1].inPoubelle = false;
    ingredients[1].zone = (Zone){726, 760, 568, 600}; // Tomate

    ingredients[2].image = assiette1;
    ingredients[2].x = 455;
    ingredients[2].y = 320;
    ingredients[2].picked = false;
    ingredients[2].inPoubelle = false;
    ingredients[2].zone = (Zone){462, 494, 319, 356}; // Assiette

    ingredients[3].image = pate1;
    ingredients[3].x = 72;
    ingredients[3].y = 105;
    ingredients[3].picked = false;
    ingredients[3].inPoubelle = false;
    ingredients[3].zone = (Zone){72, 105, 252, 287}; // Pâte

    ingredients[4].image = mozza1;
    ingredients[4].x = 72;
    ingredients[4].y = 420;
    ingredients[4].picked = false;
    ingredients[4].inPoubelle = false;
    ingredients[4].zone = (Zone){72, 105, 463, 500}; // Mozza

    ingredients[5].image = olive1;
    ingredients[5].x = 724;
    ingredients[5].y = 432;
    ingredients[5].picked = false;
    ingredients[5].inPoubelle = false;
    ingredients[5].zone = (Zone){725, 760, 428, 465}; // Olive

    ingredients[6].image = jambon1;
    ingredients[6].x = 724;
    ingredients[6].y = 355;
    ingredients[6].picked = false;
    ingredients[6].inPoubelle = false;
    ingredients[6].zone = (Zone){725, 760, 357, 393}; // Jambon

    ingredients[7].image = piZ1;
    ingredients[7].x = 72;
    ingredients[7].y = 535;
    ingredients[7].picked = false;
    ingredients[7].inPoubelle = false;
    ingredients[7].zone = (Zone){72, 105, 531, 569}; // Pizza
}

bool passe_sur_case = false;
bool passe_sur_case1 = false;

int table_x = 568;
int table_y = 612;

int ingredientRamasse = -1;
int ingredientRamasse1 = -1;

void deplace(BITMAP *buffer, Position playerPos, Position playerPos1) {
    Zone tableZone = {568, 609, 183, 219};
    Zone poubelleZone = {338, 379, 322, 360};

    // Charger les images (ne pas les recharger à chaque appel)
    static bool images_loaded = false;
    if (!images_loaded) {
        assiette1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\assiette.bmp", NULL);
        pate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\pate.bmp", NULL);
        champi1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\champi.bmp", NULL);
        tomate1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\tomate.bmp", NULL);
        jambon1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\jambon.bmp", NULL);
        olive1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\olive.bmp", NULL);
        piZ1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\piz.bmp", NULL);
        mozza1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\mozza.bmp", NULL);

        if (!assiette1 || !pate1 || !jambon1 || !champi1 || !tomate1 || !piZ1 || !mozza1 || !olive1) {
            allegro_message("Erreur lors du chargement de l'image.");
            exit(EXIT_FAILURE);
        }

        // Initialiser les ingrédients au début du jeu
        initIngredients();

        images_loaded = true;
    }

    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (255));
    circlefill(buffer, playerPos1.curseur_x, playerPos1.curseur_Y, 7, (12));

    // Gestion du personnage 1 (playerPos)
    // Vérifier si le cuisinier 1 ramasse un ingrédient
    if (key[KEY_P]) {
        if (ingredientRamasse == -1) {
            for (int i = 0; i < MAX_INGREDIENTS; ++i) {
                if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, ingredients[i].zone) && !ingredients[i].picked) {
                    ingredients[i].picked = true;
                    ingredientRamasse = i;
                    break;
                }
            }
        } else {
            // Déposer l'ingrédient uniquement dans une zone valide
            if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone) || isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone)) {
                // Créer une copie temporaire de l'ingrédient ramassé
                if (numPickedIngredients < MAX_PICKED_INGREDIENTS) {
                    pickedIngredients[numPickedIngredients++] = ingredients[ingredientRamasse];
                }
                // Mettre à jour l'état si l'ingrédient est dans la poubelle
                if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone)) {
                    ingredients[ingredientRamasse].inPoubelle = true;
                }
                // Lâcher l'ingrédient
                ingredients[ingredientRamasse].picked = false;
                ingredientRamasse = -1;
            }
        }
    }

    // Vérifier si le cuisinier 2 ramasse un ingrédient
    if (key[KEY_L]) {
        if (ingredientRamasse1 == -1) {
            for (int i = 0; i < MAX_INGREDIENTS; ++i) {
                if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, ingredients[i].zone) && !ingredients[i].picked) {
                    ingredients[i].picked = true;
                    ingredientRamasse1 = i;
                    break;
                }
            }
        } else {
            // Déposer l'ingrédient uniquement dans une zone valide
            if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone) || isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone)) {
                // Créer une copie temporaire de l'ingrédient ramassé
                if (numPickedIngredients < MAX_PICKED_INGREDIENTS) {
                    pickedIngredients[numPickedIngredients++] = ingredients[ingredientRamasse1];
                }
                // Mettre à jour l'état si l'ingrédient est dans la poubelle
                if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone)) {
                    ingredients[ingredientRamasse1].inPoubelle = true;
                }
                // Lâcher l'ingrédient
                ingredients[ingredientRamasse1].picked = false;
                ingredientRamasse1 = -1;
            }
        }
    }

    // Afficher les ingrédients ramassés à côté des cuisiniers
    /*for (int i = 0; i < numPickedIngredients; ++i) {
        pickedIngredients[i].x = playerPos.curseur_x - 10 + i * 20; // Ajustez cet offset si nécessaire
        pickedIngredients[i].y = playerPos.curseur_Y - 15; // Ajustez cet offset si nécessaire
        draw_sprite(buffer, pickedIngredients[i].image, pickedIngredients[i].x, pickedIngredients[i].y);
    }*/

    // Afficher les ingrédients ramassés à côté des cuisiniers
    if (ingredientRamasse != -1) {
        ingredients[ingredientRamasse].x = playerPos.curseur_x - 10; // Ajustez cet offset si nécessaire
        ingredients[ingredientRamasse].y = playerPos.curseur_Y - 15; // Ajustez cet offset si nécessaire
        draw_sprite(buffer, ingredients[ingredientRamasse].image, ingredients[ingredientRamasse].x, ingredients[ingredientRamasse].y);
    }

    if (ingredientRamasse1 != -1) {
        ingredients[ingredientRamasse1].x = playerPos1.curseur_x - 10; // Ajustez cet offset si nécessaire
        ingredients[ingredientRamasse1].y = playerPos1.curseur_Y - 15; // Ajustez cet offset si nécessaire
        draw_sprite(buffer, ingredients[ingredientRamasse1].image, ingredients[ingredientRamasse1].x, ingredients[ingredientRamasse1].y);
    }

    // Afficher tous les ingrédients non ramassés à leurs positions actuelles
    for (int i = 0; i < MAX_INGREDIENTS; ++i) {
        if (!ingredients[i].picked) {
            draw_sprite(buffer, ingredients[i].image, ingredients[i].x, ingredients[i].y);
        }
    }

    // Vérifier la condition de victoire
    bool victoire = true;
    bool foundPizza = false, foundTomato = false, foundMozza = false;
    for (int i = 0; i < MAX_INGREDIENTS; ++i) {
        if (ingredients[i].inPoubelle) {
            if (ingredients[i].image == piZ1) foundPizza = true;
            if (ingredients[i].image == tomate1) foundTomato = true;
            if (ingredients[i].image == mozza1) foundMozza = true;
        }
    }
    victoire = foundPizza && foundTomato && foundMozza;

    if (victoire) {
        textout_ex(buffer, font, "Victoire!", 400, 300, makecol(255, 255, 255), -1);
    }

    blit(buffer, screen, 0, 0, 0, 0, 800, 600);

    // Note : Ne pas détruire les bitmaps à chaque itération
    // Les détruire uniquement à la fin du jeu ou lors du déchargement de ressources
}

