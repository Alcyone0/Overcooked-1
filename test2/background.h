#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <allegro.h>
#define NUM_ROWS 12
#define NUM_COLS 20

typedef enum {
    TILE_FLOOR_PARQUET,
    TILE_FLOOR_CARRELAGE,
    TILE_PLAYER_1_START,
    TILE_PLAYER_2_START,
    TILE_WORKBENCH,
    TILE_COOKING_PLATE,
    TILE_TOMATO_GENERATOR,
    TILE_TRASH_CAN,
    // Ajoutez d'autres types d'éléments ici...
    NUM_TILE_TYPES
} TileType;
// Structure représentant un niveau
typedef struct {
    TileType grid[NUM_ROWS][NUM_COLS];
} Level;

Level loadLevelFromFile(const char *filename);

#endif
