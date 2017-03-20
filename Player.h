#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	//Sound settings
	sf::SoundBuffer soundBuf;
	sf::Sound sound;
	sf::View view;

	//Player+Movement+Collision
	sf::Vector2f movement;
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	int direction = 0;
	bool face;
	bool faceRight = true;
	bool faceLeft = true;
	bool faceUp = true;
	bool faceDown = true;
};