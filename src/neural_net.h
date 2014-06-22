#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <stdint.h>

struct neuron {
    uint8_t output; // une sortie
    uint8_t input_number; // un nombre d'entrées
    uint8_t **inputs; // un tableau de pointeurs pour les entrées
    uint8_t *weights; // des poids pour pondérer les entrées
    uint8_t (*output_function)(uint8_t, uint8_t**, uint8_t*); // Une fonction pour le calcul de la sortie
};

uint8_t Identity_function(uint8_t input_number, uint8_t **inputs, uint8_t *weights);
uint8_t Sigmoid_function(uint8_t input_number, uint8_t **inputs, uint8_t *weights);

struct neuron_layer {
    uint8_t layer_size;
    struct neuron *neurons;
};

struct neural_data {
    uint8_t layer_nb;
    struct neuron_layer *neuron_layers;
};

#endif
