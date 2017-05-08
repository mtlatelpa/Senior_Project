#include "enemy.h"

enemy::enemy()
{
	rect.setSize(sf::Vector2f(50.0f, 50.0f));
	rect.setPosition(360.0f, 240.0f);
	sprite.setTextureRect(sf::IntRect((spritex * counterWalking) + spritexStart, spritey * 0 + spriteyStart, spritex, spritey));

}

void enemy::update()
{
	sprite.setPosition(rect.getPosition());
	text.setPosition(rect.getPosition().x - rect.getSize().x / 2 - 8, rect.getPosition().y - rect.getSize().y / 2 - 10);
}

void enemy::updateMovement()
{

	if (direction == 1) // Up
	{
		if (faceUp == true)
		{
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect((spritex * counterWalking) + spritexStart, spritey * 3 + spriteyStart, spritex, spritey));
			faceLeft = true; faceDown = true;  // Add enemy collision with wall
			faceRight = true; faceUp = true;
		}
	}

	else if (direction == 2) // Down
	{
		if (faceDown == true)
		{
			rect.move(0, movementSpeed);
			sprite.setTextureRect(sf::IntRect((spritex * counterWalking) + spritexStart, spritey * 0 + spriteyStart, spritex, spritey));
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}

	else if (direction == 3) // Left
	{
		if (faceLeft == true)
		{
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect((spritex * counterWalking) + spritexStart, spritey * 1 + spriteyStart, spritex, spritey));
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}

	else if (direction == 4) // Right
	{
		if (faceRight == true)
		{
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(sf::IntRect((spritex * counterWalking) + spritexStart, spritey * 2 + spriteyStart, spritex, spritey));
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}

	//else
	//{
	// No movement
	//	}

	counterWalking++;

	if (counterWalking == 2)
	{
		counterWalking = 0;
	}

	counter++;

	if (counter >= movementLength)
		//if (counter >= 40)
	{
		//direction = generateRandom(10);
		direction = generateRandom(5);
		counter = 0;
	}

}