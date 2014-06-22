#ifndef GRAPHIC_H
#define GRAPHIC_H

void graphic_create(int width, int height);

int graphic_is_open();

void graphic_clear();
void graphic_draw_circle(int x, int y, int radius);
void graphic_draw_circle_colored(int x, int y, int radius, int red, int green, int blue);
void graphic_display();


#endif
