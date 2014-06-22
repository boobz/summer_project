#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "species.h"
#include "utils.h"
#include "output_functions.h"
#include "input_functions.h"

struct species *create_subject_1()
{
    const int layer_nb = 2;
    const int layer1_nb = 3;
    const int layer2_nb = 5;
    struct species *subject = (struct species*) malloc(sizeof(struct species));
    // base data of the subject
    subject->pos_x = rand()%WORLD_WIDTH;
    subject->pos_y = rand()%WORLD_HEIGHT;
    subject->orient = rand();
    subject->input_energy = UINT8_T_MAX;
    subject->input_captor1 = 0;
    subject->input_captor2 = 0;
    subject->output_attack = 0;
    subject->output_forward = 0;
    subject->output_turn_right = 0;
    subject->output_turn_left = 0;
    subject->output_reproduce = 0;
    // neural data of the subject
    struct neural_data *neural = &(subject->neural);
    neural->layer_nb = layer_nb;
    neural->neuron_layers = (struct neuron_layer*) malloc(layer_nb*sizeof(struct neuron_layer));

    neural->neuron_layers[0].layer_size = layer1_nb;
    struct neuron *neurons = (struct neuron*)malloc(layer1_nb*sizeof(struct neuron));
    uint8_t i;
    for (i=0; i<layer1_nb; i++)
    {
        neurons[i].output = 0;
        neurons[i].input_number = layer1_nb;

        uint8_t **inputs = (uint8_t**) malloc(layer1_nb*sizeof(uint8_t*));
        inputs[0] = &(subject->input_energy);
        inputs[1] = &(subject->input_captor1);
        inputs[2] = &(subject->input_captor2);
        neurons[i].inputs = inputs;

        uint8_t *weights = (uint8_t*) malloc(layer1_nb*sizeof(uint8_t));
        weights[0] = rand()%UINT8_T_MAX;
        weights[1] = rand()%UINT8_T_MAX;
        weights[2] = rand()%UINT8_T_MAX;
        neurons[i].weights = weights;

        neurons[i].output_function = Identity_function; // Une fonction pour le calcul de la sortie !!! A CHANGER EN SIGMOIDE
    }
    neural->neuron_layers[0].neurons = neurons;

    neural->neuron_layers[1].layer_size = layer2_nb;
    neurons = (struct neuron*) malloc(layer2_nb*sizeof(struct neuron));
    for (i=0; i<layer2_nb; i++)
    {
        neurons[i].output = 0;
        neurons[i].input_number = layer1_nb;

        uint8_t **inputs = (uint8_t**) malloc(layer1_nb*sizeof(uint8_t*));
        inputs[0] = &(subject->input_energy);
        inputs[1] = &(subject->input_captor1);
        inputs[2] = &(subject->input_captor2);
        neurons[i].inputs = inputs;

        uint8_t *weights = (uint8_t*) malloc(layer1_nb*sizeof(uint8_t));
        weights[0] = rand()%UINT8_T_MAX;
        weights[1] = rand()%UINT8_T_MAX;
        weights[2] = rand()%UINT8_T_MAX;
        neurons[i].weights = weights;

        neurons[i].output_function = Identity_function; // Une fonction pour le calcul de la sortie
    }
    neural->neuron_layers[1].neurons = neurons;

    return subject;
}

void update_subject_1(struct species *subject)
{
    //subject->input_energy;
    subject->input_captor1 = captor1_function(subject);
    subject->input_captor2 = captor2_function(subject);

    uint8_t j;
    uint8_t k;
    for (k=0; k<subject->neural.layer_nb; k++)
    {
        for (j=0; j<subject->neural.neuron_layers[k].layer_size; j++)
        {
            uint8_t input_number = subject->neural.neuron_layers[k].neurons[j].input_number;
            uint8_t **inputs = subject->neural.neuron_layers[k].neurons[j].inputs;
            uint8_t *weights = subject->neural.neuron_layers[k].neurons[j].weights;

            subject->neural.neuron_layers[k].neurons[j].output =
                    subject->neural.neuron_layers[k].neurons[j].output_function(input_number, inputs, weights);
        }
    }

    subject->output_attack = subject->neural.neuron_layers[subject->neural.layer_nb - 1].neurons[1].output > UINT8_T_HALF_MAX;
    subject->output_forward = subject->neural.neuron_layers[subject->neural.layer_nb - 1].neurons[2].output > UINT8_T_HALF_MAX;
    if (subject->output_forward) {
        go_forward(subject);
    }
    subject->output_turn_right = subject->neural.neuron_layers[subject->neural.layer_nb - 1].neurons[3].output > UINT8_T_HALF_MAX;
    if (subject->output_turn_right) {
        turn_right(subject);
    }
    subject->output_turn_left = subject->neural.neuron_layers[subject->neural.layer_nb - 1].neurons[4].output > UINT8_T_HALF_MAX;
    if (subject->output_turn_left) {
        turn_left(subject);
    }
    subject->output_reproduce = subject->neural.neuron_layers[subject->neural.layer_nb - 1].neurons[5].output > UINT8_T_HALF_MAX;
    // neural data of the subject

}

void display_subject_1(struct species *subject, bool display_extended)
{
    printf("(%d, %d) ,%d\n", subject->pos_x, subject->pos_y, subject->orient);
    if (display_extended) {
        printf("energy :%d\n", subject->input_energy);
        printf("captor 1 :%d\n", subject->input_captor1);
        printf("captor 1 :%d\n", subject->input_captor2);
        printf("neural data :\n");
        uint8_t i;
        uint8_t j;
        uint8_t k;
        for (k=0; k<subject->neural.layer_nb; k++)
        {
            printf("    layer %d\n", k);
            for (j=0; j<subject->neural.neuron_layers[k].layer_size; j++)
            {
                printf("        neuron %d\n", j);
                printf("            input number :%d\n", subject->neural.neuron_layers[k].neurons[j].input_number);
                for (i=0; i<subject->neural.neuron_layers[k].neurons->input_number; i++ )
                {
                    printf("                input %d : %d\n", i, *(subject->neural.neuron_layers[k].neurons[j].inputs[i]));
                    printf("                weight %d : %d\n", i, subject->neural.neuron_layers[k].neurons[j].weights[i]);
                }
                printf("output :%d\n", subject->neural.neuron_layers[k].neurons[j].output);
                printf("\n");
            }
        }
    }
}


void release_species(struct species *subject)
{
    int i,j;
    for (i=0; i<subject->neural.layer_nb; i++)
    {
        for (j=0; j<subject->neural.neuron_layers[i].layer_size; j++)
        {
            free(subject->neural.neuron_layers[i].neurons[j].weights);
        }
        free(subject->neural.neuron_layers[i].neurons);
    }
    free(subject->neural.neuron_layers);
    free(subject);
}
