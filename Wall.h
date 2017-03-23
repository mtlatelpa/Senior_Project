#pragma once
#include <SFML\Graphics.hpp>

class Wall
{
public:

	Wall();
	void update();

	sf::RectangleShape rect;
	sf::Sprite sprite;
};