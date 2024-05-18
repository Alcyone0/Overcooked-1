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

BITMAP *champi1, *tomate1, *assiette1, *pate1, *jambon1, *mozza1, *piZ1, *olive1, *plats2;

int positionsInitiales[MAX_INGREDIENTS][2] = {
        {724, 287}, // Position initiale du champignon
        {724, 565}, // Position initiale de la tomate
        {455, 320}, // Position initiale de l'assiette
        {77, 252},  // Position initiale de la pâte
        {77, 458},  // Position initiale de la mozza
        {724, 427}, // Position initiale de l'olive
        {724, 355}, // Position initiale du jambon
        {77, 532}   // Position initiale de la pizza
};

void initIngredients() {
    ingredients[0].image = champi1;
    ingredients[0].x = positionsInitiales[0][0];
    ingredients[0].y = positionsInitiales[0][1];
    ingredients[0].picked = false;
    ingredients[0].inPoubelle = false;
    ingredients[0].zone = (Zone){724, 760, 287, 324}; // Champignon

    ingredients[1].image = tomate1;
    ingredients[1].x = positionsInitiales[1][0];
    ingredients[1].y = positionsInitiales[1][1];
    ingredients[1].picked = false;
    ingredients[1].inPoubelle = false;
    ingredients[1].zone = (Zone){726, 760, 568, 600}; // Tomate

    ingredients[2].image = assiette1;
    ingredients[2].x = positionsInitiales[2][0];
    ingredients[2].y = positionsInitiales[2][1];
    ingredients[2].picked = false;
    ingredients[2].inPoubelle = false;
    ingredients[2].zone = (Zone){462, 494, 319, 356}; // Assiette

    ingredients[3].image = pate1;
    ingredients[3].x = positionsInitiales[3][0];
    ingredients[3].y = positionsInitiales[3][1];
    ingredients[3].picked = false;
    ingredients[3].inPoubelle = false;
    ingredients[3].zone = (Zone){72, 105, 252, 287}; // Pâte

    ingredients[4].image = mozza1;
    ingredients[4].x = positionsInitiales[4][0];
    ingredients[4].y = positionsInitiales[4][1];
    ingredients[4].picked = false;
    ingredients[4].inPoubelle = false;
    ingredients[4].zone = (Zone){72, 105, 463, 500}; // Mozza

    ingredients[5].image = olive1;
    ingredients[5].x = positionsInitiales[5][0];
    ingredients[5].y = positionsInitiales[5][1];
    ingredients[5].picked = false;
    ingredients[5].inPoubelle = false;
    ingredients[5].zone = (Zone){725, 760, 428, 465}; // Olive

    ingredients[6].image = jambon1;
    ingredients[6].x = positionsInitiales[6][0];
    ingredients[6].y = positionsInitiales[6][1];
    ingredients[6].picked = false;
    ingredients[6].inPoubelle = false;
    ingredients[6].zone = (Zone){725, 760, 357, 393}; // Jambon

    ingredients[7].image = piZ1;
    ingredients[7].x = positionsInitiales[7][0];
    ingredients[7].y = positionsInitiales[7][1];
    ingredients[7].picked = false;
    ingredients[7].inPoubelle = false;
    ingredients[7].zone = (Zone){72, 105, 531, 569}; // Pizza

}

void resetIngredientsPIZZAPosition() {

        ingredients[7].x = positionsInitiales[7][0];
        ingredients[7].y = positionsInitiales[7][1];
        ingredients[7].picked = false;
        ingredients[7].inPoubelle = false;

    ingredients[4].x = positionsInitiales[4][0];
    ingredients[4].y = positionsInitiales[4][1];
    ingredients[4].picked = false;
    ingredients[4].inPoubelle = false;

    ingredients[1].x = positionsInitiales[1][0];
    ingredients[1].y = positionsInitiales[1][1];
    ingredients[1].picked = false;
    ingredients[1].inPoubelle = false;

}

bool passe_sur_case = false;
bool passe_sur_case1 = false;

int table_x = 568;
int table_y = 612;

int plat2_x;
int plat2_y;


int ingredientRamasse = -1;
int ingredientRamasse1 = -1;
bool afficherPlat2 = false;
bool pizzaPicked = false;
bool plat2Picked = false;
int plat2RamassePar = -1; // Ajoutez une variable pour suivre qui a ramassé le plat 2

void deplace(BITMAP *buffer, Position playerPos, Position playerPos1) {
    Zone poubelleZone = {339, 494, 515, 565};//table
    Zone tableZone = {612, 648, 214, 251};//poubelle

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
        plats2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\2plat.bmp", NULL);
        if (!assiette1 || !pate1 || !jambon1 || !champi1 || !tomate1 || !piZ1 || !mozza1 || !olive1 || !plats2) {
            allegro_message("Erreur lors du chargement de l'image.");
            exit(EXIT_FAILURE);
        }

        initIngredients();
        images_loaded = true;
    }

    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (255));
    circlefill(buffer, playerPos1.curseur_x, playerPos1.curseur_Y, 7, (12));

    if (key[KEY_L]) {
        if (ingredientRamasse == -1 && !pizzaPicked && !plat2Picked) {
            for (int i = 0; i < MAX_INGREDIENTS; ++i) {
                if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, ingredients[i].zone) && !ingredients[i].picked) {
                    ingredients[i].picked = true;
                    ingredientRamasse = i;
                    break;
                }
            }
            if (afficherPlat2 && isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, (Zone){plat2_x, plat2_x + plats2->w, plat2_y, plat2_y + plats2->h})) {
                plat2Picked = true;
                afficherPlat2 = false;
                plat2RamassePar = 0; // Le cuisinier 2 ramasse le plat
            }
        } else if (pizzaPicked && isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone)) {
            pizzaPicked = false;
        } else if (ingredientRamasse != -1) {
            if ( isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone)) {
                if (numPickedIngredients < MAX_PICKED_INGREDIENTS) {
                    pickedIngredients[numPickedIngredients++] = ingredients[ingredientRamasse];
                }
                if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone)) {
                    ingredients[ingredientRamasse].inPoubelle = true;
                }
                ingredients[ingredientRamasse].picked = false;
                ingredientRamasse = -1;
            }
        }
    }

    if (key[KEY_V]) {
        if (ingredientRamasse1 == -1 && !pizzaPicked && !plat2Picked) {
            for (int i = 0; i < MAX_INGREDIENTS; ++i) {
                if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, ingredients[i].zone) && !ingredients[i].picked) {
                    ingredients[i].picked = true;
                    ingredientRamasse1 = i;
                    break;
                }
            }
            if (afficherPlat2 && isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, (Zone){plat2_x, plat2_x + plats2->w, plat2_y, plat2_y + plats2->h})) {
                plat2Picked = true;
                afficherPlat2 = false;
                plat2RamassePar = 1; // Le cuisinier 1 ramasse le plat
            }
        } else if (pizzaPicked && isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone)) {
            pizzaPicked = false;
        } else if (ingredientRamasse1 != -1) {
            if ( isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone)) {
                if (numPickedIngredients < MAX_PICKED_INGREDIENTS) {
                    pickedIngredients[numPickedIngredients++] = ingredients[ingredientRamasse1];
                }
                if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone)) {
                    ingredients[ingredientRamasse1].inPoubelle = true;
                }
                ingredients[ingredientRamasse1].picked = false;
                ingredientRamasse1 = -1;
            }
        }
    }

    // Ajoutez cette condition pour vérifier si le plat 2 est sur la table et si la touche correspondante est enfoncée

        if ((plat2RamassePar == 0)&& isInsideZone(plat2_x, plat2_y, tableZone)) {
            if (key[KEY_L]) {
                plat2RamassePar = -1;
                plat2_x = 620;
                plat2_y = 188;
                //rest(5000);
                //initIngredients();

            }// Le cuisinier 2 ramasse le plat
        } if ((plat2RamassePar == 1)&& isInsideZone(plat2_x, plat2_y, tableZone)) {
            if (key[KEY_V]) {
                plat2RamassePar = -1;
                plat2_x = 620;
                plat2_y = 188;// Le cuisinier 1 ramasse le plat
                //rest(5000);
                //initIngredients();
            }
        }



    if (ingredientRamasse != -1) {
        ingredients[ingredientRamasse].x = playerPos.curseur_x - 10;
        ingredients[ingredientRamasse].y = playerPos.curseur_Y - 15;
        draw_sprite(buffer, ingredients[ingredientRamasse].image, ingredients[ingredientRamasse].x, ingredients[ingredientRamasse].y);
    }

    if (ingredientRamasse1 != -1) {
        ingredients[ingredientRamasse1].x = playerPos1.curseur_x - 10;
        ingredients[ingredientRamasse1].y = playerPos1.curseur_Y - 15;
        draw_sprite(buffer, ingredients[ingredientRamasse1].image, ingredients[ingredientRamasse1].x, ingredients[ingredientRamasse1].y);
    }

    for (int i = 0; i < MAX_INGREDIENTS; ++i) {
        if (!ingredients[i].picked) {
            draw_sprite(buffer, ingredients[i].image, ingredients[i].x, ingredients[i].y);
        }
    }

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
        afficherPlat2 = true;
        resetIngredientsPIZZAPosition();
        plat2_x = poubelleZone.x_min; // Mettre plats2 dans la zone poubelle
        plat2_y = poubelleZone.y_min;
    }

    if (afficherPlat2 && !plat2Picked) {
        draw_sprite(buffer, plats2, plat2_x, plat2_y);
    } else if (plat2Picked) {
        if (plat2RamassePar == 0) {
            plat2_x = playerPos.curseur_x - 10;
            plat2_y = playerPos.curseur_Y - 15;
        } else if (plat2RamassePar == 1) {
            plat2_x = playerPos1.curseur_x - 10;
            plat2_y = playerPos1.curseur_Y - 15;
        }
        draw_sprite(buffer, plats2, plat2_x, plat2_y);
    }

    if (!afficherPlat2 && !plat2Picked) {
        draw_sprite(buffer, plats2, 568, 612);
    }

    blit(buffer, screen, 0, 0, 0, 0, 800, 600);
    /*destroy_bitmap(assiette1);
    destroy_bitmap(pate1);
    destroy_bitmap(champi1);
    destroy_bitmap(tomate1);
    destroy_bitmap(jambon1);
    destroy_bitmap(olive1);
    destroy_bitmap(piZ1);
    destroy_bitmap(mozza1);
    destroy_bitmap(plats2);*/
    //destroy_bitmap(buffer);
}
