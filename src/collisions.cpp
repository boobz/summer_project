#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "collisions.h"
#include "world.h"
#include "utils.h"


const uint8_t food_gain = 8;

void collision_with_food(struct species *subject)
{
    const uint32_t pos_x = subject->pos_x;
    const uint32_t pos_y = subject->pos_y;
    const uint8_t radius = subject->input_size;

    uint8_t gain = 0;
    struct food_list *food = world_food_return();
    while (food != NULL)
    {
        const int32_t distance = sqrt((food->pos_x - pos_x)*(food->pos_x - pos_x) + (food->pos_y - pos_y)*(food->pos_y - pos_y));
        if (food->timer == 0 && distance < (radius + BASE_SIZE)) {
            food->pos_x = rand() % WORLD_WIDTH;
            food->pos_y = rand() % WORLD_HEIGHT;
            food->timer = FOOD_TIMER;
            gain += food_gain;
        }
        food = food->next;
    }
    if (gain + subject->input_energy > 127)
        subject->input_energy = 127;
    else
        subject->input_energy += gain;
}

void collision_vision(struct species *subject)
{
    uint8_t occurences = 0;
    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    uint32_t feel = 0;

    const double v_x = cos(subject->orient/TWOPI);
    const double v_y = sin(subject->orient/TWOPI);
    const double angle_source = atan2(v_y, v_x);

    struct food_list *food = world_food_return();

    while (food != NULL)
    {
        const int32_t distance = sqrt((food->pos_x - subject->pos_x)*(food->pos_x - subject->pos_x)
                                       + (food->pos_y - subject->pos_y)*(food->pos_y - subject->pos_y));
        if (food->timer == 0 && distance < 10*subject->input_size)
        {
            if ((10*subject->input_size - distance)*UINT8_T_MAX/(10*subject->input_size) > feel)
                feel = (10*subject->input_size - distance)*UINT8_T_HALF_MAX/(10*subject->input_size);

            const double y_diff = (int32_t)food->pos_y - (int32_t)subject->pos_y;
            const double x_diff = (int32_t)food->pos_x - (int32_t)subject->pos_x;
            const double angle_food = atan2(y_diff, x_diff);
            if (fabs(angle_source - angle_food) < PI_ON_EIGHT) {
                green += UINT8_T_HALF_MAX;
                occurences ++;
            }
        }
    food = food->next;
    }
    subject->input_captor_feel = feel;
    if (occurences != 0) {
        subject->input_captor_red = red/occurences;
        subject->input_captor_green = green/occurences;
        subject->input_captor_blue = blue/occurences;
    } else {
        subject->input_captor_red = 0;
        subject->input_captor_green = 0;
        subject->input_captor_blue = 0;
    }
}
