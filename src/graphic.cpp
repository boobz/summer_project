#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "graphic.h"


static sf::RenderWindow window;

void graphic_create(int width, int height)
{
	window.create(sf::VideoMode(width, height),
				  "Title", 
				  sf::Style::Default, 
				  sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	
}

int graphic_is_open()
{
	sf::Event event;
	window.pollEvent(event);
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Escape) {
		window.close();
	}
	
	return window.isOpen();
}

void graphic_clear()
{
	window.clear();
}

void graphic_draw_circle(int x, int y, int radius)
{
	graphic_draw_circle_colored(x, y, radius, rand()%255, rand()%255, rand()%255);
}

void graphic_draw_circle_colored(int x, int y, int radius, int red, int green, int blue)
{
	sf::CircleShape c(radius);
	c.setPosition(x, y);
	c.setFillColor(sf::Color(red, green, blue));
	c.setOrigin(c.getLocalBounds().width / 2,
				c.getLocalBounds().height / 2);
	window.draw(c);
}

void graphic_display()
{
	window.display();
}
