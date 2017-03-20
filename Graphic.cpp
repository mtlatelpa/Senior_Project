#include "Graphic.h"

Graphic::Graphic()
{

	//Main Background
	background.setSize(sf::Vector2f(720.0f, 480.0f));
	background.setPosition(0.0f, 0.0f);
	backgroundImage.loadFromFile("cave.png");
	background.setTexture(&backgroundImage);

	//East Background
	background2.setSize(sf::Vector2f(720.0f, 480.0f));
	background2.setPosition(720.0f, 0.0f);
	backgroundImage2.loadFromFile("mario.png");
	background2.setTexture(&backgroundImage2);

	//South Background
	background3.setSize(sf::Vector2f(720.0f, 480.0f));
	background3.setPosition(0.0f, 480.0f);
	backgroundImage3.loadFromFile("floor.jpg");
	background3.setTexture(&backgroundImage3);

	//West Background
	background4.setSize(sf::Vector2f(720.0f, 480.0f));
	background4.setPosition(-720.0f, 0.0f);
	backgroundImage4.loadFromFile("metal.jpg");
	background4.setTexture(&backgroundImage4);

	//North Background
	background5.setSize(sf::Vector2f(720.0f, 480.0f));
	background5.setPosition(0.0f, -480.0f);
	backgroundImage5.loadFromFile("fire.jpg");
	background5.setTexture(&backgroundImage5);

	//Transparent Tree
	backgroundTree.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree.setPosition(500.0f, 100.0f);
	treeTexture.loadFromFile("dark_tree.png");
	backgroundTree.setTexture(&treeTexture);

}

Graphic::~Graphic() { }