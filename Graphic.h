#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Graphic
{
public:
	Graphic();
	~Graphic();

	//------Backgrounds----------//
	//Starting background image
	sf::RectangleShape background;
	sf::Texture backgroundImage;
	//East background image
	sf::RectangleShape background2;
	sf::Texture backgroundImage2;
	//South background image
	sf::RectangleShape background3;
	sf::Texture backgroundImage3;
	//West background image
	sf::RectangleShape background4;
	sf::Texture backgroundImage4;
	//North background image
	sf::RectangleShape background5;
	sf::Texture backgroundImage5;
	//Southwest background
	sf::RectangleShape background6;
	sf::Texture backgroundImage6;
	//Southeast background
	sf::RectangleShape background7;
	sf::Texture backgroundImage7;
	//Tree
	sf::RectangleShape backgroundTree, backgroundTree2, backgroundTree3, 
		backgroundTree4, backgroundTree5, backgroundTree6, backgroundTree7,
		backgroundTree8;
	sf::Texture treeTexture;

	//ExitTop image
	sf::RectangleShape backgroundExitTop;
	sf::RectangleShape backgroundExitTop2;
	sf::Texture exittopTexture;
	//ExitBottom image
	sf::RectangleShape backgroundExitBottom;
	sf::Texture exitbottomTexture;

	//-----Towers--------------//
	sf::RectangleShape tower1;
	sf::RectangleShape tower2;
	sf::RectangleShape tower3;
	sf::Texture towertex1;
	sf::Texture towertex2;
	sf::Texture towertex3;

	//-----Shaded---------------//
	sf::RectangleShape playerShade;
	sf::Texture playerShadeTexture;

	//-----Menu-----------------//
	sf::RectangleShape menuImage;
	sf::Texture menuTexture;

};