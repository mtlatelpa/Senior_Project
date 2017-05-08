#include "Graphic.h"

Graphic::Graphic()
{
	//Changed cave image 4/4
	background.setSize(sf::Vector2f(720.0f, 480.0f));
	background.setPosition(0.0f, 0.0f);
	backgroundImage.loadFromFile("cave3.png");
	background.setTexture(&backgroundImage);
	//East Background
	background2.setSize(sf::Vector2f(720.0f, 480.0f));
	background2.setPosition(720.0f, 0.0f);
	backgroundImage2.loadFromFile("cave_side.png");
	background2.setTexture(&backgroundImage2);
	//South Background
	background3.setSize(sf::Vector2f(720.0f, 480.0f));
	background3.setPosition(0.0f, 480.0f);
	backgroundImage3.loadFromFile("cave.png");
	background3.setTexture(&backgroundImage3);
	//Player starts at west
	//West Background
	background4.setSize(sf::Vector2f(720.0f, 480.0f));
	background4.setPosition(-720.0f, 0.0f);
	backgroundImage4.loadFromFile("cave_side.png");
	background4.setTexture(&backgroundImage4);
	//South west background
	background6.setSize(sf::Vector2f(720.0f, 480.0f));
	background6.setPosition(-720.0f, 480.0f);
	backgroundImage6.loadFromFile("cave_side.png");
	background6.setTexture(&backgroundImage6);
	//South East background 4/4
	background7.setSize(sf::Vector2f(720.0f, 480.0f));
	background7.setPosition(720.0f, 480.0f);
	backgroundImage7.loadFromFile("cave_side.png");
	background7.setTexture(&backgroundImage7);
	//Transparent Tree
	backgroundTree.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree.setPosition(500.0f, 100.0f);
	treeTexture.loadFromFile("dark_tree.png");
	backgroundTree.setTexture(&treeTexture);
	backgroundTree2.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree2.setPosition(-660.0f, 260.0f);
	backgroundTree2.setTexture(&treeTexture);
	backgroundTree3.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree3.setPosition(-680.0f, 690.0f);
	backgroundTree3.setTexture(&treeTexture);
	backgroundTree4.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree4.setPosition(-260.0f, 540.0f);
	backgroundTree4.setTexture(&treeTexture);
	backgroundTree5.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree5.setPosition(790.0f, 540.0f);
	backgroundTree5.setTexture(&treeTexture);
	backgroundTree6.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree6.setPosition(1040.0f, 700.0f);
	backgroundTree6.setTexture(&treeTexture);
	backgroundTree7.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree7.setPosition(890.0f, 110.0f);
	backgroundTree7.setTexture(&treeTexture);
	backgroundTree8.setSize(sf::Vector2f(150.0f, 150.0f));
	backgroundTree8.setPosition(1190.0f, 260.0f);
	backgroundTree8.setTexture(&treeTexture);
	//Miguel									4/2/17
	//CenterCenter Bottom Exit
	backgroundExitBottom.setPosition(50, 340);
	backgroundExitBottom.setSize(sf::Vector2f(100, 140));
	exitbottomTexture.loadFromFile("exitBottom.png");
	backgroundExitBottom.setTexture(&exitbottomTexture);
	//CenterCenter Top Exit
	backgroundExitTop.setPosition(310, 0);
	backgroundExitTop.setSize(sf::Vector2f(100, 160));
	exittopTexture.loadFromFile("exitTop.png");
	backgroundExitTop.setTexture(&exittopTexture);
	//CenterSouth Top Exit
	backgroundExitTop2.setPosition(50, 480);
	backgroundExitTop2.setSize(sf::Vector2f(100, 160));
	backgroundExitTop2.setTexture(&exittopTexture);

	//Towers
	towertex1.loadFromFile("tower1.png");
	tower1.setSize(sf::Vector2f(30.0f, 40.0f));
	towertex2.loadFromFile("tower2.png");
	tower2.setSize(sf::Vector2f(30.0f, 40.0f));
	towertex3.loadFromFile("tower3.png");
	tower3.setSize(sf::Vector2f(30.0f, 40.0f));
	tower1.setTexture(&towertex1);
	tower2.setTexture(&towertex2);
	tower3.setTexture(&towertex3);
	tower1.setPosition(930.0f, -48.0f);
	tower2.setPosition(960.0f, -48.0f);
	tower3.setPosition(990.0f, -48.0f);

	//Player Shade
	playerShade.setSize(sf::Vector2f(1920.0f, 1080.0f));
	playerShade.setPosition(-720.0f, 0.0f);
	playerShadeTexture.loadFromFile("shade_black.png");
	playerShade.setTexture(&playerShadeTexture);

	//Menu Image
	menuImage.setSize(sf::Vector2f(720.0f, 480.0f));
	menuTexture.loadFromFile("menu_1.png");
	menuImage.setTexture(&menuTexture);

}

Graphic::~Graphic()
{

}