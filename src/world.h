#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>
#include <stdbool.h>

#include "species.h"

struct species_list {
    struct species *subject;
    struct species_list *next;
};

struct food_list {
    uint32_t pos_x;
    uint32_t pos_y;
    uint8_t timer;
    struct food_list *next;
};

void world_init(uint8_t species_number, uint8_t food_number);
void world_update();
struct species_list** world_species_return();
struct food_list* world_food_return();
uint32_t world_timestamp_return();
void world_display(bool console_display);
void world_destroy();
void world_species_destroy(struct species *subject);

#endif
