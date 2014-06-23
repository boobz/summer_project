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
    while (graphic_is_open()) {
	graphic_clear();
        world_display();
	graphic_display();

        printf("\nworld updated\n\n");
        world_update();
	i++;
    }
    world_destroy();
    return 0;
}
