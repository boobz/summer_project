#include <math.h>

#include "output_functions.h"
#include "utils.h"

void go_forward(struct species *subject)
{
    subject->pos_x += 100*cos(subject->orient/TWOPI);
    subject->pos_y += 100*sin(subject->orient/TWOPI);
}

void turn_right(struct species *subject)
{
    subject->orient -= 10;
}

void turn_left(struct species *subject)
{
    subject->orient += 10;
}
