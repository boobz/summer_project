#ifndef SPECIES_H
#define SPECIES_H

#include <stdint.h>
#include <stdbool.h>

#include "neural_net.h"

struct species {
    struct neural_data neural;
    uint32_t pos_x;
    uint32_t pos_y;
    uint8_t orient;
    uint8_t input_size; // pas encore géré
    uint8_t input_energy; // pas encore géré
    uint8_t input_captor1;
    uint8_t input_captor2;
    bool output_attack;
    bool output_forward;
    bool output_turn_right;
    bool output_turn_left;
    bool output_reproduce;
};

struct species *create_subject_1();
void update_subject_1(struct species *subject);
void display_subject_1(struct species *subject, bool display_extended);

void release_species(struct species *subject);

#endif
