#include "Wall.h"

Wall::Wall()
{
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(0, 0);
	//rect.setFillColor(sf::Color::Transparent);
}

void Wall::update()
{
	sprite.setPosition(rect.getPosition());
}