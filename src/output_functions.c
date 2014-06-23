#include <math.h>

#include "output_functions.h"
#include "utils.h"

void go_forward(struct species *subject)
{
    subject->pos_x = (uint32_t)(subject->pos_x + 10*cos(subject->orient/TWOPI)) % WORLD_WIDTH;
    subject->pos_y = (uint32_t)(subject->pos_y + 10*sin(subject->orient/TWOPI)) % WORLD_HEIGHT;
}

void turn_right(struct species *subject)
{
    subject->orient -= 16;
}

void turn_left(struct species *subject)
{
    subject->orient += 16;
}
