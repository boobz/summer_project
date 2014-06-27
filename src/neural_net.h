#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <stdint.h>

struct neuron {
    int8_t output; // une sortie
    uint8_t input_number; // un nombre d'entrées
    int8_t **inputs; // un tableau de pointeurs pour les entrées
    int8_t *weights; // des poids pour pondérer les entrées
    int8_t (*output_function)(uint8_t, int8_t**, int8_t*); // Une fonction pour le calcul de la sortie
};

int8_t Identity_function(uint8_t input_number, int8_t **inputs, int8_t *weights);
int8_t Sigmoid_function(uint8_t input_number, int8_t **inputs, int8_t *weights);
void mutate_neural(struct species *subject);

struct neuron_layer {
    uint8_t layer_size;
    struct neuron *neurons;
};

struct neural_data {
    uint8_t layer_nb;
    struct neuron_layer *neuron_layers;
};

#endif
