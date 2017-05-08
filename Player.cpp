#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	face = true;

	body.setSize(sf::Vector2f(40.0f, 40.0f));
	body.setPosition(-360.0f, 240.0f);
	body.setTexture(texture);

	view.setSize(720, 480);
	view.setCenter(360.0f, 240.0f);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	movement.x = 0.0f;
	movement.y = 0.0f;

	//Gerardo 4/4
	//Added a +0.5 to movement speed, maybe could be a variable on power up you can move faster
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sound.play();
		if (faceLeft == true) {
			movement.x -= ((speed * deltaTime) + 0.5);		//Gerardo: added + 4 to move in blocks
			direction = 3;
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (faceRight == true) {
			movement.x += ((speed * deltaTime) + 0.5);
			direction = 4;
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (faceUp == true) {
			movement.y -= ((speed * deltaTime) + 0.5);
			direction = 1;
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (faceDown == true) {
			movement.y += ((speed * deltaTime) + 0.5);
			direction = 2;
			faceLeft = true; faceDown = true;
			faceRight = true; faceUp = true;
		}
	}
	else {/*Player not moving*/ }


	//Gerardo 4/13 made posxy global
	//Switching map locations
	playerposx = body.getPosition().x;
	playerposy = body.getPosition().y;
	//std::cout << "x: " << playerposx << "     " << "y: " << playerposy << std::endl;

	//East
	if (body.getPosition().x > 720.0f && body.getPosition().y < 480.0f) {
		view.setCenter(1080.0f, 240.0f);
		N = false, E = true, C = false, S = false, W = false, SW = false, SE = false;
		here = 2;
	}
	//South East
	else if (body.getPosition().x > 720.0f && body.getPosition().y > 480.0f) {
		view.setCenter(1080.0f, 720.0f);
		N = false, E = false, C = false, S = false, W = false, SW = false, SE = true;
		here = 7;
	}
	//South 
	else if (body.getPosition().y > 480.0f && body.getPosition().x > 0) {
		view.setCenter(360.0f, 720.0f);
		N = false, E = false, C = false, S = true, W = false, SW = false, SE = false;
		here = 3;
	}
	//South West
	else if (body.getPosition().y > 480.0f && body.getPosition().x < 0) {
		view.setCenter(-360.0f, 720.0f);
		N = false, E = false, C = false, S = false, W = false, SW = true, SE = false;
		here = 6;
	}
	//North
	else if (body.getPosition().y < -50.0f) {
		view.setCenter(360.0f, -240.0f);
		N = true, E = false, C = false, S = false, W = false, SW = false, SE = false;
		here = 1;
	}
	//West
	else if (body.getPosition().x < -50.0f) {
		view.setCenter(-360.0f, 240.0f);
		N = false, E = false, C = false, S = false, W = true, SW = false, SE = false;
		here = 4;
	}
	else {
		view.setCenter(360.0f, 240.0f);
		N = false, E = false, C = true, S = false, W = false, SW = false, SE = false;
		here = 5;
	}

	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (movement.x > 0.0f)
			face = true;
		else
			face = false;
	}
	if (movement.y < 0.0f) {
		row = 2;
	}

	animation.Update(row, deltaTime, face);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
