//
// Created by ACER on 07/04/2024.
//

#include "commandes.h"
#include <allegro.h>


typedef struct Command {
    int type;
    struct Command *next;
} Command;