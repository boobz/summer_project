#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>

#include "species.h"

struct species_list {
    struct species *subject;
    struct species_list *next;
};

struct food_list {
    uint32_t pos_x;
    uint32_t pos_y;
    struct food_list *next;
};

void world_init(uint8_t species_number, uint8_t food_number);
void world_update();
void world_display();
void world_destroy();

#endif
