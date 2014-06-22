#include <stdio.h>
#include <stdlib.h>

#include "graphic.h"
#include "world.h"
#include "species.h"

int main ( int argc, char** argv )
{
    graphic_create(800, 600);
    world_init(10, 10);
    
    // run the main loop
	
    while (graphic_is_open()) {
        world_display();

        printf("\nworld updated\n\n");
        world_update();

        world_display();
        world_destroy();
        /*
        struct species *animal_1 = create_subject_1();
        display_subject_1(animal_1, false);

        int i;
        for (i=0; i<10; i++)
        {
            printf("\n");
            update_subject_1(animal_1);
            display_subject_1(animal_1, false);
        }

	release_species(animal_1);
   	*/
	graphic_clear();
	graphic_draw_circle_colored(200, 350, 50, 255, 0, 0);
	graphic_draw_circle_colored(0, 0, 50, 255, 128, 64);
	graphic_display();
    }
    world_destroy();
    return 0;
}
