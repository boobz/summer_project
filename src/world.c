#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "world.h"
#include "species.h"
#include "utils.h"

struct species_list *species;
struct food_list *food;

void world_init(uint8_t species_number, uint8_t food_number)
{
    srand(time(NULL));
    uint8_t i;
    species = NULL;
    for (i=0; i<species_number; i++)
    {
        struct species_list *new_specimen = (struct species_list*) malloc(sizeof(struct species_list));
        new_specimen->subject = create_subject_1();
        new_specimen->next = species;
        species = new_specimen;
    }

    food = NULL;
    for (i=0; i<food_number; i++)
    {
    	struct food_list *new_food = (struct food_list*) malloc(sizeof(food_list));
    	new_food->pos_x = rand()%WORLD_WIDTH;
    	new_food->pos_y = rand()%WORLD_HEIGHT;
    	new_food->next = food;
    	food = new_food;
    }

}

void world_update()
{
    struct species_list *specimen = species;
    while (specimen != NULL)
    {
        update_subject_1(specimen->subject);
        specimen = specimen->next;
    }
}

void world_display()
{
    struct species_list *specimen = species;
    uint8_t i = 0;
    while (specimen != NULL)
    {
        i++;
        printf("individu %d : ", i);
        display_subject_1(specimen->subject, false);
        specimen = specimen->next;
    }

    i = 0;
    struct food_list *cur_food = food;
    while (cur_food != NULL)
    {
        i++;
        printf("food %d : (%d, %d)\n", i, cur_food->pos_x, cur_food->pos_y);
        cur_food = cur_food->next;
    }
}

void world_destroy()
{
    struct species_list *specimen = species;
    struct species_list *next_specimen;
    while (specimen != NULL)
    {
        next_specimen = specimen->next;
        release_species(specimen->subject);
        free(specimen);
        specimen = next_specimen;
    }

    struct food_list *cur_food = food;
    struct food_list *next_food;
    while (cur_food != NULL)
    {
        next_food = cur_food->next;
        free(cur_food);
        cur_food = next_food;
    }

}
