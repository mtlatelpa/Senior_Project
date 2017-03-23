#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "Graphic.h"
#include "Wall.h"
#include "Resource.h"
#include "Enemy.h"

using namespace std;
int exitgame = 0;

int main() {

	//Global Variables
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Titlebar);
	Audio audio;
	Graphic graphics;
	int flag = 0, counter = 0, help = 0;
	sf::Clock clock1; // clock for AI
	int counter2 = 0, counter3 = 0;

	//Gerardo 
	//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	playerTexture.loadFromFile("char_sprite_walk_swords.png");

	//---------------------------------------------------------------------------------------------------------------
	//Miguel text on screen
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "can't open ttf file" << std::endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(15);
	//text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setString("Level - 1\n");

	sf::Text textHelp;
	textHelp.setFont(font);
	textHelp.setCharacterSize(15);
	textHelp.setString("\n(H) Help?\n");
	sf::Text textHelp2;
	textHelp2.setFont(font);
	textHelp2.setCharacterSize(15);
	textHelp2.setString("\n(H) Help?\n(F) - Flashlight\n(Space) - Shoot\n(1) - Melee\n(2) - Sword\n(3) - Tower\n");
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Miguel Walls
	vector<Wall>::const_iterator wallit;
	vector<Wall> wallArray;

	class Wall wall1, wall2, wall3, wall4;
	/*sf::Texture textureWall;
	textureWall.loadFromFile("cave_top.png");
	wall1.rect.setTexture(&textureWall);
	sf::Texture textureWall2;
	textureWall2.loadFromFile("cave_bottom_left.png");
	wall2.rect.setTexture(&textureWall2);
	sf::Texture textureWall3;
	textureWall3.loadFromFile("cave_bottom_right.png");
	wall3.rect.setTexture(&textureWall3);
	*/
	wall1.rect.setPosition(0, 0);
	wall1.rect.setSize(sf::Vector2f(720, 160));
	wallArray.push_back(wall1);
	wall2.rect.setPosition(0, 340);
	wall2.rect.setSize(sf::Vector2f(150, 150));
	wallArray.push_back(wall2);
	wall3.rect.setPosition(150, 430);
	wall3.rect.setSize(sf::Vector2f(570, 50));
	wallArray.push_back(wall3);
	wall4.rect.setPosition(560, 240);
	wall4.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall4);
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Miguel Resources
	vector<Resource>::const_iterator resourceit;
	vector<Resource> resourceArray;
	class Resource resource1;
	sf::Texture textureResource1;

	//Miguel Resource Allocation
	resource1.resource1 = true;
	resource1.resource2 = false;
	resource1.resource3 = false;
	resource1.rect.setFillColor(sf::Color::Green);
	resource1.rect.setPosition(300, 350);
	resourceArray.push_back(resource1);
	resource1.resource1 = false;
	resource1.resource2 = true;
	resource1.resource3 = false;
	resource1.rect.setFillColor(sf::Color::Blue);
	resource1.rect.setPosition(400, 250);
	resourceArray.push_back(resource1);
	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = true;
	resource1.rect.setFillColor(sf::Color::Red);
	resource1.rect.setPosition(200, 250);
	resourceArray.push_back(resource1);
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Gerardo Player Sprite/Sound
	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);
	//Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Cuong
	// Adding enemy texture - need to work more for sprite sheet
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("ghost.png")) {
		return EXIT_FAILURE;
	}
	// Enemy Vector Array
	vector<Enemy>::const_iterator iter4;
	vector<Enemy> enemyArray;

	// Enemy Objects - make 2 enemies try
	class Enemy enemy1, enemy2;
	enemy1.sprite.setTexture(textureEnemy);
	enemy1.rect.setPosition(700, 250); // y: 200 is the border with the wall
	enemyArray.push_back(enemy1);
	enemy2.sprite.setTexture(textureEnemy);
	enemy2.rect.setPosition(500, 260);
	enemyArray.push_back(enemy2);
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Gerardo Clock
	float deltaTime = 0.0f;
	sf::Clock clock;
	//if(music = 1) play
	//if(music = 2) play

	cout << "Playing background music" << endl;
	audio.backgroundmusic1.play();
	audio.backgroundmusic1.setVolume(25);
	//---------------------------------------------------------------------------------------------------------------



	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					std::cout << "Menu Being Displayed" << std::endl;
					if (exitgame == 0)
						exitgame = 1;
					else
						exitgame = 0;
				}
			}
			//Grabbing Left Button
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.key.code == sf::Mouse::Left)
				{
					std::cout << "left button clicked" << std::endl;
					sf::Vector2i position = sf::Mouse::getPosition(window);
					std::cout << position.x << std::endl;
					std::cout << position.y << std::endl;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
		{
			help ^= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			flag = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			flag = 1;
		}
		if (flag == 0)
		{
			playerTexture.loadFromFile("char_sprite_walk3.png");
		}
		else if (flag == 1)
		{
			playerTexture.loadFromFile("char_sprite_walk_swords.png");
		}


		//---------------------------------------------------------------------------------------------------------------
		//Cuong
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			int counter2 = 0;
			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					if (enemyArray[counter].direction == 1) //Up
					{
						enemyArray[counter].faceUp = false;
						enemyArray[counter].rect.move(0, 1);
					}
					else if (enemyArray[counter].direction == 2) //Down
					{
						enemyArray[counter].faceDown = false;
						enemyArray[counter].rect.move(0, -1);
					}
					else if (enemyArray[counter].direction == 3) //Left
					{
						enemyArray[counter].faceLeft = false;
						enemyArray[counter].rect.move(1, 0);
					}
					else if (enemyArray[counter].direction == 4) //Right
					{
						enemyArray[counter].faceRight = false;
						enemyArray[counter].rect.move(-1, 0);
					}
					else
					{
					}
				}
				counter2++;
			}
			counter++;
		}
		//---------------------------------------------------------------------------------------------------------------


		//---------------------------------------------------------------------------------------------------------------
		//Cuong
		//Player Wall Collision
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++) {
			if (player.body.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
			{
				//Hit wall
				if (player.direction == 1) //Up
				{
					player.faceUp = false;
					player.body.move(0, 1);
				}
				else if (player.direction == 2) //Down
				{
					player.faceDown = false;
					player.body.move(0, -1);
				}
				else if (player.direction == 3) //Left
				{
					player.faceLeft = false;
					player.body.move(1, 0);
				}
				else if (player.direction == 4) //Right
				{
					player.faceRight = false;
					player.body.move(-1, 0);
				}
				else {}
			}
			counter++;
		}
		//---------------------------------------------------------------------------------------------------------------


		window.setView(player.view);

		//---------------------------------------------------------------------------------------------------------------
		//Miguel
		//Player Wall Collision
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++) {
			if (player.body.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
			{
				//Hit wall
				if (player.direction == 1) //Up
				{
					player.faceUp = false;
					player.body.move(0, 1);
				}
				else if (player.direction == 2) //Down
				{
					player.faceDown = false;
					player.body.move(0, -1);
				}
				else if (player.direction == 3) //Left
				{
					player.faceLeft = false;
					player.body.move(1, 0);
				}
				else if (player.direction == 4) //Right
				{
					player.faceRight = false;
					player.body.move(-1, 0);
				}
				else {}
			}
			counter++;
		}
		//---------------------------------------------------------------------------------------------------------------

		//what is this?
		window.setView(player.view);

		player.Update(deltaTime);
		window.clear(sf::Color(125, 125, 125));
		window.draw(graphics.background);
		window.draw(graphics.background2);
		window.draw(graphics.background3);
		window.draw(graphics.background4);
		window.draw(graphics.background5);

		//Draw Wall
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
		{
			wallArray[counter].update();

			window.draw(wallArray[counter].rect);
			window.draw(wallArray[counter].sprite);
			counter++;
		}

		//window.setPosition(sf::Vector2i(50, 50));
		player.Draw(window);
		window.draw(wall1.sprite);
		window.draw(wall2.sprite);
		window.draw(wall3.sprite);
		window.draw(wall4.sprite);
		window.draw(graphics.backgroundTree);

		//---------------------------------------------------------------------------------------------------------------
		//Cuong 
		//Drawing Enemy
		sf::Time elapsed1 = clock1.getElapsedTime();

		// Enemy Chasing (AI)
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].chase == true)
			{
				if (elapsed1.asSeconds() >= 1)
				{
					clock1.restart();
					int tempRand = generateRandom(3);
					if (tempRand == 1) // Track Player Position
					{
						// Player to Right
						if ((player.body.getPosition().x < enemyArray[counter].rect.getPosition().x) && (abs(player.body.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40)) {
							enemyArray[counter].direction = 3;
						}
						// Player to Left
						if ((player.body.getPosition().x > enemyArray[counter].rect.getPosition().x) && (abs(player.body.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40)) {
							enemyArray[counter].direction = 4;
						}
						// Player to Top
						if ((player.body.getPosition().y < enemyArray[counter].rect.getPosition().y) && (abs(player.body.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40)) {
							enemyArray[counter].direction = 1;
						}
						// Player to Bottom
						if ((player.body.getPosition().y > enemyArray[counter].rect.getPosition().y) && (abs(player.body.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40)) {
							enemyArray[counter].direction = 2;
						}
					}
					else if (tempRand == 2) // Enemy Chases Player
					{
						if (player.body.getPosition().y < enemyArray[counter].rect.getPosition().y) {
							enemyArray[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray[counter].rect.getPosition().y) {
							enemyArray[counter].direction = 2;
						}
						else if (player.body.getPosition().x < enemyArray[counter].rect.getPosition().x) {
							enemyArray[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray[counter].rect.getPosition().x) {
							enemyArray[counter].direction = 4;
						}
					}
					else // Enemy Chases Player
					{
						if (player.body.getPosition().x < enemyArray[counter].rect.getPosition().x) {
							enemyArray[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray[counter].rect.getPosition().x) {
							enemyArray[counter].direction = 4;
						}
						else if (player.body.getPosition().y < enemyArray[counter].rect.getPosition().y) {
							enemyArray[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray[counter].rect.getPosition().y) {
							enemyArray[counter].direction = 2;
						}
					}
				}
			}
			counter++;
		}
		enemyArray[counter2].chase = true;
		// Draw Enemies
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].update();
			enemyArray[counter].updateMovement();
			//window.draw(enemyArray[counter].rect);
			window.draw(enemyArray[counter].sprite);
			counter++;
		}
		//---------------------------------------------------------------------------------------------------------------


		//---------------------------------------------------------------------------------------------------------------
		//Miguel Draw Resources
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			resourceArray[counter].update();

			window.draw(resourceArray[counter].rect);
			window.draw(resourceArray[counter].sprite);
			counter++;
		}
		//---------------------------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------------------------
		//Miguel draw text
		window.draw(text);
		help == 0 ? window.draw(textHelp) : window.draw(textHelp2);
		//---------------------------------------------------------------------------------------------------------------

		//displaying Escape Menu
		if (exitgame == 1) window.draw(graphics.menuImage);
		else	graphics.menuImage.setTexture(&graphics.menuTexture);

		window.display();


	}
	return 0;
}