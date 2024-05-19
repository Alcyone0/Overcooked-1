#include "deplace.h"
#include <allegro.h>
#include <stdbool.h>
#include <stdlib.h>
#include "nv1.h"
#include "timer.h"

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

typedef struct {
    bool foundPizza;
    bool foundTomato;
    bool foundMozza;
    bool foundAssiette;
    bool foundOlive; // Ajouté pour la deuxième recette
    bool foundJambon;
} Recipe;

Ingredient ingredients[MAX_INGREDIENTS];
Ingredient pickedIngredients[MAX_PICKED_INGREDIENTS];

int numPickedIngredients = 0;

bool isInsideZone(int x, int y, Zone zone) {
    return (x >= zone.x_min && x <= zone.x_max && y >= zone.y_min && y <= zone.y_max);
}

BITMAP *champi1, *tomate1, *assiette1, *pate1, *jambon1, *mozza1, *piZ1, *olive1, *plats2, *plats1, *plats3;

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

void resetIngredientsPIZZA1Position() {
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

    ingredients[2].x = positionsInitiales[2][0];
    ingredients[2].y = positionsInitiales[2][1];
    ingredients[2].picked = false;
    ingredients[2].inPoubelle = false;
}

void resetIngredientsPIZZA2Position() {
    ingredients[7].x = positionsInitiales[7][0];
    ingredients[7].y = positionsInitiales[7][1];
    ingredients[7].picked = false;
    ingredients[7].inPoubelle = false;

    ingredients[1].x = positionsInitiales[1][0];
    ingredients[1].y = positionsInitiales[1][1];
    ingredients[1].picked = false;
    ingredients[1].inPoubelle = false;

    ingredients[2].x = positionsInitiales[2][0];
    ingredients[2].y = positionsInitiales[2][1];
    ingredients[2].picked = false;
    ingredients[2].inPoubelle = false;

    ingredients[5].x = positionsInitiales[5][0];
    ingredients[5].y = positionsInitiales[5][1];
    ingredients[5].picked = false;
    ingredients[5].inPoubelle = false;

}

void resetIngredientsPIZZA3Position() {
    ingredients[7].x = positionsInitiales[7][0];
    ingredients[7].y = positionsInitiales[7][1];
    ingredients[7].picked = false;
    ingredients[7].inPoubelle = false;

    ingredients[1].x = positionsInitiales[1][0];
    ingredients[1].y = positionsInitiales[1][1];
    ingredients[1].picked = false;
    ingredients[1].inPoubelle = false;

    ingredients[2].x = positionsInitiales[2][0];
    ingredients[2].y = positionsInitiales[2][1];
    ingredients[2].picked = false;
    ingredients[2].inPoubelle = false;

    ingredients[6].x = positionsInitiales[6][0];
    ingredients[6].y = positionsInitiales[6][1];
    ingredients[6].picked = false;
    ingredients[6].inPoubelle = false;

}

bool passe_sur_case = false;
bool passe_sur_case1 = false;

int table_x = 568;
int table_y = 612;

int plat1_x, plat1_y;
int plat2_x, plat2_y;
int plat3_x, plat3_y;

int ingredientRamasse = -1;
int ingredientRamasse1 = -1;
//int ingredientRamasse2 = -1;

bool afficherPlat1 = false;
bool afficherPlat2 = false;
bool afficherPlat3 = false;


bool pizzaPicked = false;
bool plat1Picked = false;
bool plat2Picked = false;
bool plat3Picked = false;

int plat1RamassePar = -1;
int plat2RamassePar = -1;
int plat3RamassePar = -1;

void deplace(BITMAP *buffer, Position playerPos, Position playerPos1) {
    Zone poubelleZone = {339, 494, 515, 565}; // table pour faire commandes
    Zone tableZone1 = {193, 231, 182, 216}; //table 1 pour deposer commmandes
    Zone tableZone2 = {420, 458, 181, 249}; //table 2 pour desposé comandes
    Zone tableZone3 = {609, 648, 181, 216}; // table 3 pouor depose commandes
    Zone poubelZone = {338, 379, 322, 360}; //poubelle

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
        plats2 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\2platsb.bmp", NULL);
        plats1 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\1platsb.bmp", NULL);
        plats3 = load_bitmap("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\images\\3plat.bmp", NULL);
        if (!assiette1 || !pate1 || !jambon1 || !champi1 || !tomate1 || !piZ1 || !mozza1 || !olive1 || !plats2 || !plats1 || !plats3) {
            allegro_message("Erreur lors du chargement de l'image.");
            exit(EXIT_FAILURE);
        }

        initIngredients();
        images_loaded = true;
    }

    circlefill(buffer, playerPos.curseur_x, playerPos.curseur_Y, 7, (255));
    circlefill(buffer, playerPos1.curseur_x, playerPos1.curseur_Y, 7, (12));

    if (key[KEY_L]) {
        if (ingredientRamasse == -1) {
            for (int i = 0; i < MAX_INGREDIENTS; ++i) {
                if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, ingredients[i].zone)) {
                    ingredientRamasse = i;
                    ingredients[i].picked = true;
                    passe_sur_case = true;
                    break;
                }
            }
        } else {
            if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone)) {
                ingredients[ingredientRamasse].picked = false;
                ingredients[ingredientRamasse].inPoubelle = true;
                ingredientRamasse = -1;
            }
        }

        if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone) && afficherPlat2) {
            plat2Picked = true;
            plat2RamassePar = 0;
        }



        if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone) && afficherPlat1) {
            plat1Picked = true;
            plat1RamassePar = 0;
        }
        if (isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelleZone) && afficherPlat3) {
            plat3Picked = true;
            plat3RamassePar = 0;
        }

    }

    if (key[KEY_V]) {
        if (ingredientRamasse1 == -1) {
            for (int i = 0; i < MAX_INGREDIENTS; ++i) {
                if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, ingredients[i].zone)) {
                    ingredientRamasse1 = i;
                    ingredients[i].picked = true;

                    break;
                }
            }
        } else {
            if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone)) {
                ingredients[ingredientRamasse1].picked = false;
                ingredients[ingredientRamasse1].inPoubelle = true;
                ingredientRamasse1 = -1;
            }
        }

        if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone) && afficherPlat2) {
            plat2Picked = true;
            plat2RamassePar = 1;
        } else {
            plat2Picked = false;
            plat2RamassePar = -1;
        }

        if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone) && afficherPlat1) {
            plat1Picked = true;
            plat1RamassePar = 1;
        } else {
            plat1Picked = false;
            plat1RamassePar = -1;
        }
        if (isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelleZone) && afficherPlat3) {
            plat3Picked = true;
            plat3RamassePar = 1;
        } else {
            plat3Picked = false;
            plat3RamassePar = -1;
        }
    }
    if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, poubelZone )) && key[KEY_L]){
        ingredientRamasse = -1;
    }
    if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, poubelZone )) && key[KEY_V]){
        ingredientRamasse1 = -1;
    }


    for (int i = 0; i < MAX_INGREDIENTS; ++i) {
        if (ingredients[i].picked) {
            if (ingredientRamasse == i) {
                ingredients[i].x = playerPos.curseur_x - 10;
                ingredients[i].y = playerPos.curseur_Y - 15;
            } else if (ingredientRamasse1 == i) {
                ingredients[i].x = playerPos1.curseur_x - 10;
                ingredients[i].y = playerPos1.curseur_Y - 15;
            }

        }
        draw_sprite(buffer, ingredients[i].image, ingredients[i].x, ingredients[i].y);
    }

    Recipe recipe1 = {false, false, false, false, false};
    Recipe recipe2 = {false, false, false, false, false};
    Recipe recipe3 = {false, false, false, false, false};

    for (int i = 0; i < MAX_INGREDIENTS; ++i) {
        if (ingredients[i].inPoubelle) {
            if (ingredients[i].image == piZ1) recipe1.foundPizza = recipe2.foundPizza = recipe3.foundPizza = true;
            if (ingredients[i].image == tomate1) recipe1.foundTomato = recipe2.foundTomato = recipe3.foundTomato = true;
            if (ingredients[i].image == mozza1) recipe2.foundMozza = true;
            if (ingredients[i].image == assiette1) recipe1.foundAssiette = recipe2.foundAssiette = recipe3.foundAssiette = true;
            if (ingredients[i].image == olive1) recipe1.foundOlive = true;
            if (ingredients[i].image == jambon1) recipe3.foundJambon = true; // Ajouté pour la recette 3
        }
    }

    bool victoire1 = recipe1.foundPizza && recipe1.foundTomato && recipe1.foundAssiette && recipe1.foundOlive;
    bool victoire2 = recipe2.foundPizza && recipe2.foundTomato && recipe2.foundMozza && recipe2.foundAssiette;
   bool victoire3 = recipe3.foundPizza && recipe3.foundTomato && recipe3.foundAssiette && recipe3.foundJambon;


    if (victoire1) {
        afficherPlat1 = true;
        resetIngredientsPIZZA2Position();
        plat1_x = poubelleZone.x_min;
        plat1_y = poubelleZone.y_min;
    }

    if (victoire2) {
        afficherPlat2 = true;
        resetIngredientsPIZZA1Position();
        plat2_x = poubelleZone.x_min;
        plat2_y = poubelleZone.y_min;
    }
    if (victoire3) {
        afficherPlat3 = true;
        resetIngredientsPIZZA3Position();
        plat3_x = poubelleZone.x_min;
        plat3_y = poubelleZone.y_min;
    }

    if (afficherPlat1 && !plat1Picked) {
        draw_sprite(buffer, plats1, plat1_x, plat1_y);
    } else if (plat1Picked) {
        if (plat1RamassePar == 0) {
            plat1_x = playerPos.curseur_x - 10;
            plat1_y = playerPos.curseur_Y - 15;
            if (plat1Picked && plat1RamassePar == 0) {
                if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone1) ||
                    isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone2) ||
                    isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone3))&& key[KEY_L]) {
                    plat1Picked = false;
                    afficherPlat1 = false;
                    victoire1 = false;
                    plat1RamassePar = -1;
                }
            }
        }if (plat1RamassePar == 1) {
            plat1_x = playerPos1.curseur_x - 10;
            plat1_y = playerPos1.curseur_Y - 15;
            if (plat1Picked && plat1RamassePar == 1) {
                if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone1) ||
                    isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone2) ||
                    isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone3)) && key[KEY_V]) {
                    plat1Picked = false;
                    afficherPlat1 = false;
                    victoire1 = false;
                    plat1RamassePar = -1;
                }
            }
        }
        draw_sprite(buffer, plats1, plat1_x, plat1_y);
    }




    if (afficherPlat3 && !plat3Picked) {
        draw_sprite(buffer, plats3, plat3_x, plat3_y);
    } else if (plat3Picked) {
        if (plat3RamassePar == 0) {
            plat3_x = playerPos.curseur_x - 10;
            plat3_y = playerPos.curseur_Y - 15;
            if (plat3Picked && plat3RamassePar == 0) {
                if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone1) ||
                     isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone2) ||
                     isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone3)) && key[KEY_L]) {
                    plat3Picked = false;
                    afficherPlat3 = false;
                    victoire3 = false;
                    plat3RamassePar = -1;
                }
            }
        } else if (plat3RamassePar == 1) {
            plat3_x = playerPos1.curseur_x - 10;
            plat3_y = playerPos1.curseur_Y - 15;
            if (plat3Picked && plat3RamassePar == 1) {
                if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone1) ||
                     isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone2) ||
                     isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone3)) && key[KEY_V]) {
                    plat3Picked = false;
                    afficherPlat3 = false;
                    victoire3 = false;
                    plat3RamassePar = -1;
                }
            }
        }
        draw_sprite(buffer, plats3, plat3_x, plat3_y);
    }




    if (afficherPlat2 && !plat2Picked) {
        draw_sprite(buffer, plats2, plat2_x, plat2_y);
    } else if (plat2Picked) {
        if (plat2RamassePar == 0) {
            plat2_x = playerPos.curseur_x - 10;
            plat2_y = playerPos.curseur_Y - 15;
            if (plat2Picked && plat2RamassePar == 0) {
                if ((isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone1) ||
                    isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone2) ||
                    isInsideZone(playerPos.curseur_x, playerPos.curseur_Y, tableZone3)) && key[KEY_L]) {
                    plat2Picked = false;
                    afficherPlat2 = false;
                    victoire2 = false;
                    plat2RamassePar = -1;
                }
            }
        } else if (plat2RamassePar == 1) {
            plat2_x = playerPos1.curseur_x - 10;
            plat2_y = playerPos1.curseur_Y - 15;
            if (plat2Picked && plat2RamassePar == 1) {
                if ((isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone1) ||
                    isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone2) ||
                    isInsideZone(playerPos1.curseur_x, playerPos1.curseur_Y, tableZone3)) && key[KEY_V]) {
                    plat2Picked = false;
                    afficherPlat2 = false;
                    victoire2 = false;
                    plat2RamassePar = -1;
                }
            }
        }
        draw_sprite(buffer, plats2, plat2_x, plat2_y);
    }

    blit(buffer, screen, 0,0,0,0, 800,600);
}
