#include <stdint.h>
#include <math.h>

#include "neural_net.h"
#include "utils.h"

uint8_t sum_function(uint8_t input_number, uint8_t **inputs, uint8_t *weights)
{
    uint8_t sum = 0;
    uint8_t i;
    for (i = 0; i<input_number; i++)
    {
        sum += *(inputs[i])*weights[i];
    }
    return sum;
}

uint8_t Identity_function(uint8_t input_number, uint8_t **inputs, uint8_t *weights)
{
    const uint8_t sum = sum_function(input_number, inputs, weights);
    return sum;
}


uint8_t Sigmoid_function(uint8_t input_number, uint8_t **inputs, uint8_t *weights)
{
    const uint8_t sum = sum_function(input_number, inputs, weights);
    return UINT8_T_MAX/(1+exp(-sum));
}
