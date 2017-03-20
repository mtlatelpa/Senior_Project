#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Animation.h"
#include "Audio.h"
#include "Graphic.h"
#include "Player.h"
#include "Resource.h"
#include "Wall.h"

using namespace std;
int exitgame = 0;

int main() {

	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Resize);
	Audio audio;
	Graphic graphic;
	int flag = 0, counter = 0, help = 0;

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

	/*
	sf::View view1(sf::FloatRect(200, 200, 300, 200));
	view1.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	view1.setCenter(sf::Vector2f(view1.getSize().x / 2, view1.getSize().y / 2));
	window.setView(view1);
	*/

	//Main Music Sound
	/*sf::SoundBuffer mainsoundBuf;
	sf::Sound mainSound;
	std::cout << "loading in background music" << std::endl;
	if (!mainsoundBuf.loadFromFile("Punks.wav"))
		std::cout << "can't open sound file" << std::endl;
	mainSound.setBuffer(mainsoundBuf);
	mainSound.play();
	*/

	//Playing Background Music
	cout << "Playing background music" << endl;
	audio.backgroundmusic1.play();
	audio.backgroundmusic1.setVolume(25);

//Attempting to put the background Image in
//sf::RectangleShape background(sf::Vector2f(720.0f, 480.0f));
//background.setPosition(0.0f, 0.0f);

	///background.setOrigin(250.0f, 250.0f);
	///background.setPosition(250.0f, 250.0f);
//sf::Texture backgroundImage;
	///backgroundImage.loadFromFile("Woods.png");
	///backgroundImage.loadFromFile("mario.png");
//backgroundImage.loadFromFile("floor.jpg");
//background.setTexture(&backgroundImage);


	//sf::RectangleShape backgroundTree(sf::Vector2f(150.0f, 150.0f));
	//backgroundTree.setPosition(330.0f, 180.0f);

	//sf::Texture treeTexture;
	//treeTexture.loadFromFile("transparent_tree.png");
	//backgroundTree.setTexture(&treeTexture);
	
	//Player Texture
	sf::Texture playerTexture;
	//playerTexture.loadFromFile("char_sprite_walk2.png");
	playerTexture.loadFromFile("char_sprite_walk_swords.png");

	// Wall creation + texture
	vector<Wall>::const_iterator wallit;
	vector<Wall> wallArray;

	class Wall wall1, wall2, wall3;
	sf::Texture textureWall;
	textureWall.loadFromFile("cave_top.png");
	wall1.rect.setTexture(&textureWall);
	sf::Texture textureWall2;
	textureWall2.loadFromFile("cave_bottom_left.png");
	wall2.rect.setTexture(&textureWall2);
	sf::Texture textureWall3;
	textureWall3.loadFromFile("cave_bottom_right.png");
	wall3.rect.setTexture(&textureWall3);
	/*sf::Texture textureWall;
	textureWall.loadFromFile("wall.jpg");
	wall1.rect.setTexture(&textureWall);*/

	// Resource creation + texture
	vector<Resource>::const_iterator resourceit;
	vector<Resource> resourceArray;

	class Resource resource1;
	sf::Texture textureResource1;
	//textureResource1.loadFromFile("res2.png");
	//resource1.sprite.setTexture(textureResource1);

	/*for (int i = 0; i <= 720; i += 50) {
		wall1.rect.setPosition(i, 0);
		wallArray.push_back(wall1);
		wall1.rect.setPosition(i, 450);
		wallArray.push_back(wall1);
		for (int j = 100; j <= 480; j += 50) {
			wall1.rect.setPosition(0, j);
			wallArray.push_back(wall1);
			wall1.rect.setPosition(700, j);
			wallArray.push_back(wall1);
		}
	}*/
	//for (int i = 0; i <= 720; i += 50) {
		wall1.rect.setPosition(0, 0);
		wall1.rect.setSize(sf::Vector2f(720, 200));
		wallArray.push_back(wall1);

		wall2.rect.setPosition(0, 330);
		wall2.rect.setSize(sf::Vector2f(150, 150));
		wallArray.push_back(wall2);

		wall3.rect.setPosition(150, 430);
		wall3.rect.setSize(sf::Vector2f(570, 50));
		wallArray.push_back(wall3);
	//}
	/*for (int i = 100; i <= 250; i += 50) {
		wall1.rect.setPosition(i, 100);
		wallArray.push_back(wall1);
	}
	for (int i = 150; i <= 200; i += 50) {
		wall1.rect.setPosition(100, i);
		wallArray.push_back(wall1);
	}
	for (int i = 150; i <= 500; i += 50) {
		wall1.rect.setPosition(i, 350);
		wallArray.push_back(wall1);
	}
	for (int i = 400; i <= 550; i += 50) {
		wall1.rect.setPosition(i, 100);
		wallArray.push_back(wall1);
	}
	for (int i = 150; i <= 200; i += 50) {
		wall1.rect.setPosition(600, i);
		wallArray.push_back(wall1);
	}*/

	resource1.resource1 = true;
	resource1.resource2 = false;
	resource1.resource3 = false;
	resource1.rect.setFillColor(sf::Color::Green);
	//resource1.sprite.setTexture(textureResource1);
	//resource1.sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
	resource1.rect.setPosition(300, 350);
	resourceArray.push_back(resource1);

	resource1.resource1 = false;
	resource1.resource2 = true;
	resource1.resource3 = false;
	resource1.rect.setFillColor(sf::Color::Blue);
	//resource1.sprite.setTexture(textureResource1);
	//resource1.sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
	resource1.rect.setPosition(400, 250);
	resourceArray.push_back(resource1);

	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = true;
	resource1.rect.setFillColor(sf::Color::Red);
	//resource1.sprite.setTexture(textureResource1);
	//resource1.sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
	resource1.rect.setPosition(200, 250);
	resourceArray.push_back(resource1);

	//New texture coordinates
	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);

	//Player footsteps
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);

	//Menu
	sf::RectangleShape menuImage(sf::Vector2f(720.0f, 480.0f));
	menuImage.setPosition(0.0f, 0.0f);
	sf::Texture menuTexture;
	menuTexture.loadFromFile("menu_1.png");
	menuImage.setTexture(&menuTexture);

	float deltaTime = 0.0f;
	sf::Clock clock;

	//putting the character on the screen bound to the box
	/*
	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 3;
	textureSize.y /= 9;
	player.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 8, textureSize.x, textureSize.y));
	*/

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
				//if (evnt.key.code == sf::Keyboard::H)
				//{
				//	help ^= 1;
				//}
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

		//Player Wall Collision
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++) {
			if (player.body.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()) || player.body.getGlobalBounds().intersects(graphic.backgroundTree.getGlobalBounds()))
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
				else { }
			}
			counter++;
		}

		window.setView(player.view);
		player.Update(deltaTime);

		window.clear(sf::Color(125, 125, 125));
		window.draw(graphic.background);
		window.draw(graphic.background2);
		window.draw(graphic.background3);
		window.draw(graphic.background4);
		window.draw(graphic.background5);
		//player view
		/*
		window.setView(view1);
		view1.setCenter(player.body.getPosition());
		*/

		//Draw Wall
		counter = 0;
		for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
		{
			wallArray[counter].update();

			window.draw(wallArray[counter].rect);
			window.draw(wallArray[counter].sprite);
			counter++;
		}

		player.Draw(window);

		//window.clear();
		window.draw(wall1.sprite);
		window.draw(wall2.sprite);
		window.draw(wall3.sprite);
		//window.draw(resource1.sprite);

		//Draw resource
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			resourceArray[counter].update();

			window.draw(resourceArray[counter].rect);
			window.draw(resourceArray[counter].sprite);
			counter++;
		}

		//window.draw(player);
		window.draw(graphic.backgroundTree);
		
		//draw text
		window.draw(text);

		help == 0 ? window.draw(textHelp) : window.draw(textHelp2);

		//displaying Escape Menu
		if (exitgame == 1)
			window.draw(menuImage);
		else
			menuImage.setTexture(&menuTexture);

		//Update the window
		window.display();
	}

	return 0;
}

