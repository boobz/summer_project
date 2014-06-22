#include <stdio.h>
#include <stdlib.h>

#include "graphic.h"
#include "world.h"
#include "species.h"
#include "utils.h"

int main ( int argc, char** argv )
{
    graphic_create(WORLD_WIDTH, WORLD_HEIGHT);
    world_init(10, 10);
    
    // run the main loop
    int i = 0;	
    while (graphic_is_open() && i!=2) {
        world_display();

        printf("\nworld updated\n\n");
        world_update();

	graphic_clear();
	graphic_draw_circle_colored(200, 350, 50, 255, 0, 0);
	graphic_draw_circle_colored(0, 0, 50, 255, 128, 64);
	graphic_display();
	i++;
    }
    world_destroy();
    return 0;
}
