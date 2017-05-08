#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <sstream>
#include "Animation.h"
#include "Player.h"
#include "Audio.h"
#include "Graphic.h"
#include "Wall.h"
#include "Resource.h"
#include "enemy.h"
#include "Projectile.h"
#include "Tower.h"

using namespace std;
int exitgame = 0;
int pausedgame = 20;


int main() {

	//Window Opening
	sf::RenderWindow window(sf::VideoMode(720, 480), "Fight Hard Yeah! Tower Defense Game", sf::Style::Close | sf::Style::Titlebar);

	//Class Access Speicifiers
	Audio audio;
	Graphic graphics;
	Tower towers;	//Gerardo 4/15
	Tower towers2;
	Tower towers3;

	//Variables
	int flag = 0, counter = 0, help = 0, counter2 = 0;
	sf::Clock clock1; // clock for AI Cuong
	sf::Clock clock2;
	sf::Clock clock3;
	sf::Clock clock4;

	int tower_attack = 0;

	//Player character texture, rectangle bound to box
	sf::Texture playerTexture;
	playerTexture.loadFromFile("char_sprite_walk3.png");
	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 100.0f);


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
	textHelp2.setString("\n(H) Help?\n(F) - Flashlight\n(Space) - Shoot\n(1) - Melee\n(2) - Gun\n(3) - God\n");
	
	ostringstream totalScore;
	totalScore << "Score: " << player.score;
	sf::Text textScore, textScore2, textScore3, textScore4, textScore5, textScore6, textScore7;
	textScore.setFont(font);
	textScore.setCharacterSize(15);
	textScore2.setFont(font);
	textScore2.setCharacterSize(15);
	textScore3.setFont(font);
	textScore3.setCharacterSize(15);
	textScore4.setFont(font);
	textScore4.setCharacterSize(15);
	textScore5.setFont(font);
	textScore5.setCharacterSize(15);
	textScore6.setFont(font);
	textScore6.setCharacterSize(15);
	textScore7.setFont(font);
	textScore7.setCharacterSize(15);
	textScore.setPosition({ -111, 48 });
	textScore2.setPosition({ -111, 528 });
	textScore3.setPosition({ 609, 528 });
	textScore4.setPosition({ 1329, 528 });
	textScore5.setPosition({ 1329, 48 });
	textScore6.setPosition({ 609, -433 });
	textScore7.setPosition({ 609, 48 });
	textScore.setString(totalScore.str());
	textScore2.setString(totalScore.str());
	textScore3.setString(totalScore.str());
	textScore4.setString(totalScore.str());
	textScore5.setString(totalScore.str());
	textScore6.setString(totalScore.str());
	textScore7.setString(totalScore.str());
	//---------------------------------------------------------------------------------------------------------------

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//														4/2/17-4/7/17
	//Miguel Health+Ammo Bar
	sf::Texture textureHealthBar, textureAmmoBar;
	if (!textureHealthBar.loadFromFile("healthBar2.png")) {
		cout << "Health Bar texture not found!\n";
	}
	if (!textureAmmoBar.loadFromFile("ammoBar2.png")) {
		cout << "Ammo Bar texture not found!\n";
	}
	sf::Sprite spriteHealth[6][7]; //, spriteHealth1, spriteHealth2, spriteHealth3, spriteHealth4, spriteHealth5;
	sf::Sprite spriteAmmo[10][7];
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 6; i++) {
			spriteHealth[i][j].setTexture(textureHealthBar);
			spriteAmmo[i][j].setTexture(textureAmmoBar);
			spriteAmmo[i][j].setTextureRect(sf::IntRect(0, 47, 47, 47));
		}
		spriteHealth[5][j].setTextureRect(sf::IntRect(0, 0, 111, 47));
		spriteHealth[4][j].setTextureRect(sf::IntRect(0, 48, 111, 47));
		spriteHealth[3][j].setTextureRect(sf::IntRect(0, 94, 111, 47));
		spriteHealth[2][j].setTextureRect(sf::IntRect(0, 142, 111, 47));
		spriteHealth[1][j].setTextureRect(sf::IntRect(0, 190, 111, 47));
		spriteHealth[0][j].setTextureRect(sf::IntRect(0, 237, 111, 47));
	}
	for (int i = 0; i < 6; i++)
	{
		spriteHealth[i][0].setPosition(sf::Vector2f(609, -480));
		spriteAmmo[i][0].setPosition(sf::Vector2f(609, -433));
	}
	for (int i = 0; i < 6; i++) { spriteHealth[i][1].setPosition(sf::Vector2f(1329, 0)); }
	for (int i = 0; i < 6; i++) { spriteHealth[i][2].setPosition(sf::Vector2f(609, 480)); }
	for (int i = 0; i < 6; i++) { spriteHealth[i][3].setPosition(sf::Vector2f(-111, 0)); }
	for (int i = 0; i < 6; i++) { spriteHealth[i][4].setPosition(sf::Vector2f(609, 0)); }
	for (int i = 0; i < 6; i++) { spriteHealth[i][5].setPosition(sf::Vector2f(-111, 480)); }
	for (int i = 0; i < 6; i++) { spriteHealth[i][6].setPosition(sf::Vector2f(1329, 480)); }
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//---------------------------------------------------------------------------------------------------------------
	//Miguel Walls						4/2/17-4/7/17
	vector<Wall>::const_iterator wallit;
	vector<Wall> wallArray;
	class Wall wall0, wall1, wall2, wall3, wall4;

	sf::Texture textureWall, textureWall2;
	textureWall.loadFromFile("cave_block.png");
	wall0.rect.setTexture(&textureWall);
	textureWall2.loadFromFile("wall.jpg");
	wall1.rect.setTexture(&textureWall2);
	//East Walls
	///Top+Bottom+Right
	for (int i = 720; i <= 1370; i += 50)
	{
		wall0.rect.setPosition(i, 0);
		wallArray.push_back(wall0);
		for (int j = 0; j <= 960; j += 50)
		{
			wall0.rect.setPosition(1390, j);
			wallArray.push_back(wall0);
		}
	}
	wall0.rect.setPosition(720, 430);
	wallArray.push_back(wall0);
	///LeftTop
	for (int j = 0; j <= 100; j += 50)
	{
		wall0.rect.setPosition(720, j);
		wallArray.push_back(wall0);
	}
	wall0.rect.setPosition(720, 110);
	wallArray.push_back(wall0);

	//SouthEast Walls
	//Left
	for (int j = 480; j <= 580; j += 50)
	{
		wall0.rect.setPosition(720, j);
		wallArray.push_back(wall0);
	}

	//West Walls
	///Top+Left
	for (int i = -720; i <= -50; i += 50)
	{
		wall0.rect.setPosition(i, 0);
		wallArray.push_back(wall0);
		for (int j = 0; j <= 450; j += 50)
		{
			wall0.rect.setPosition(-720, j);
			wallArray.push_back(wall0);
		}
	}
	///RightTop
	for (int j = 0; j <= 100; j += 50)
	{
		wall0.rect.setPosition(-50, j);
		wallArray.push_back(wall0);
	}
	wall0.rect.setPosition(-50, 110);
	wallArray.push_back(wall0);
	///RightBottom
	for (int j = 340; j <= 450; j += 50)
	{
		wall0.rect.setPosition(-50, j);
		wallArray.push_back(wall0);
	}

	//SouthWest
	///Bottom+Left
	for (int i = -720; i <= -50; i += 50)
	{
		wall0.rect.setPosition(i, 910);
		wallArray.push_back(wall0);
		for (int j = 480; j <= 960; j += 50)
		{
			wall0.rect.setPosition(-720, j);
			wallArray.push_back(wall0);
		}
	}
	///RightTop
	for (int j = 480; j <= 580; j += 50)
	{
		wall0.rect.setPosition(-50, j);
		wallArray.push_back(wall0);
	}
	wall0.rect.setPosition(-50, 110);
	wallArray.push_back(wall0);
	///RightBottom
	for (int j = 820; j <= 960; j += 50)
	{
		wall0.rect.setPosition(-50, j);
		wallArray.push_back(wall0);
	}

	//CenterNorth
	///Top+Right+Left
	for (int i = 0; i <= 720; i += 50) {
		wall0.rect.setPosition(i, -480);
		wallArray.push_back(wall0);
		for (int j = -480; j <= -50; j += 50)
		{
			wall0.rect.setPosition(0, j);
			wallArray.push_back(wall0);
			wall0.rect.setPosition(670, j);
			wallArray.push_back(wall0);
		}
	}
	///Bottom Left
	for (int i = 0; i <= 250; i += 50)
	{
		wall0.rect.setPosition(i, -50);
		wallArray.push_back(wall0);
	}
	wall0.rect.setPosition(260, -50);
	wallArray.push_back(wall0);
	///Bottom Right
	for (int i = 410; i <= 720; i += 50)
	{
		wall0.rect.setPosition(i, -50);
		wallArray.push_back(wall0);
	}

	//CenterSouth
	///Bottom+Right
	for (int i = 150; i <= 1440; i += 50) {
		wall0.rect.setPosition(i, 910);
		wallArray.push_back(wall0);
	}
	///LeftTop
	for (int i = 480; i <= 590; i += 50)
	{
		wall0.rect.setPosition(0, i);
		wallArray.push_back(wall0);
	}

	///West+Center Random Walls
	for (int i = -310; i <= -50; i += 50)
	{
		wall0.rect.setPosition(i, 110);
		wallArray.push_back(wall0);
		wall0.rect.setPosition(i, 340);
		wallArray.push_back(wall0);
	}
	for (int j = 130; j <= 330; j += 50)
	{
		wall0.rect.setPosition(-310, j);
		wallArray.push_back(wall0);
	}
	for (int i = -200; i <= 150; i += 50)
	{
		wall0.rect.setPosition(i, 230);
		wallArray.push_back(wall0);
	}
	for (int j = 230; j <= 400; j += 50)
	{
		wall0.rect.setPosition(150, j);
		wallArray.push_back(wall0);
	}
	//CenterCenter Random Walls
	for (int j = 160; j <= 300; j += 50)
	{
		wall0.rect.setPosition(260, j);
		wallArray.push_back(wall0);
	}
	for (int i = 260; i <= 350; i += 50)
	{
		wall0.rect.setPosition(i, 300);
		wallArray.push_back(wall0);
	}
	for (int j = 300; j <= 400; j += 50)
	{
		wall0.rect.setPosition(350, j);
		wallArray.push_back(wall0);
	}

	//Walls
	for (int i = 220; i <= 650; i += 50)
	{
		wall0.rect.setPosition(i, 690);
		wallArray.push_back(wall0);
	}
	for (int i = 220; i <= 500; i += 50)
	{
		wall0.rect.setPosition(i, 810);
		wallArray.push_back(wall0);
	}
	for (int j = 630; j <= 730; j += 50)
	{
		wall0.rect.setPosition(670, j);
		wallArray.push_back(wall0);
		wall0.rect.setPosition(720, j);
		wallArray.push_back(wall0);
	}
	//Transparent Walls
	//CenterCenter
	///Bottom Left
	wall0.rect.setPosition(0, 340);
	wall0.rect.setSize(sf::Vector2f(50, 50));
	wallArray.push_back(wall0);
	wall0.rect.setPosition(0, 390);
	wall0.rect.setSize(sf::Vector2f(50, 50));
	wallArray.push_back(wall0);
	wall0.rect.setPosition(0, 440);
	wall0.rect.setSize(sf::Vector2f(50, 40));
	wallArray.push_back(wall0);
	///Top Left
	wall1.rect.setFillColor(sf::Color::Transparent);
	//wall1.rect.setFillColor(sf::Color::White);
	wall1.rect.setPosition(0, 0);
	wall1.rect.setSize(sf::Vector2f(310, 160));
	wallArray.push_back(wall1);
	///Top Right
	wall1.rect.setPosition(410, 0);
	wall1.rect.setSize(sf::Vector2f(320, 160));
	wallArray.push_back(wall1);
	///Bottom LeftRight
	wall1.rect.setPosition(149, 340);
	wall1.rect.setSize(sf::Vector2f(1, 140));
	wallArray.push_back(wall1);
	///Bottom Right
	wall1.rect.setPosition(150, 430);
	wall1.rect.setSize(sf::Vector2f(570, 50));
	wallArray.push_back(wall1);
	///Trees
	wall1.rect.setPosition(560, 240);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(-600, 400);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(-620, 830);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(-200, 680);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(850, 680);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(1100, 840);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(950, 250);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	wall1.rect.setPosition(1250, 400);
	wall1.rect.setSize(sf::Vector2f(30, 10));
	wallArray.push_back(wall1);
	//CenterSouth
	///Top Right
	wall1.rect.setPosition(149, 480);
	wall1.rect.setSize(sf::Vector2f(571, 150));
	wallArray.push_back(wall1);
	///Bottom LeftRight
	wall1.rect.setPosition(0, 820);
	wall1.rect.setSize(sf::Vector2f(149, 140));
	wallArray.push_back(wall1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//---------------------------------------------------------------------------------------------------------------
	//Miguel Resources					4/7/17
	vector<Resource>::const_iterator resourceit;
	vector<Resource> resourceArray;
	class Resource resource1;
	sf::Texture textureResource1, textureResource2, textureResource3, textureResource4, textureResource5, textureResource6;

	resource1.resource1 = true;
	resource1.resource2 = false;
	resource1.resource3 = false;
	resource1.resource4 = false;
	resource1.resource5 = false;
	resource1.resource6 = false;
	textureResource1.loadFromFile("res_health.png");
	resource1.rect.setTexture(&textureResource1);
	resource1.rect.setPosition(-100, 400);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(350, 750);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(1000, 800);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(1000, 100);
	resourceArray.push_back(resource1);
	resource1.resource1 = false;

	resource1.resource1 = false;
	resource1.resource2 = true;
	resource1.resource3 = false;
	resource1.resource4 = false;
	resource1.resource5 = false;
	resource1.resource6 = false;
	textureResource2.loadFromFile("res_bullet.png");
	resource1.rect.setTexture(&textureResource2);
	resource1.rect.setPosition(-100, 75);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(-250, 250);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(-200, 700);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(500, 400);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(1350, 880);
	resourceArray.push_back(resource1);
	resource1.resource2 = false;

	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = true;
	resource1.resource4 = false;
	resource1.resource5 = false;
	resource1.resource6 = false;
	textureResource3.loadFromFile("res_gun.png");
	resource1.rect.setTexture(&textureResource3);
	resource1.rect.setPosition(300, 400);
	resourceArray.push_back(resource1);
	resource1.resource3 = false;

	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = false;
	resource1.resource4 = true;
	resource1.resource5 = false;
	resource1.resource6 = false;
	textureResource4.loadFromFile("tower2.png");
	resource1.rect.setTexture(&textureResource4);
	resource1.rect.setPosition(640, 750);
	resourceArray.push_back(resource1);
	resource1.resource4 = false;

	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = false;
	resource1.resource4 = false;
	resource1.resource5 = true;
	resource1.resource6 = false;
	textureResource5.loadFromFile("tower3.png");
	resource1.rect.setTexture(&textureResource5);
	resource1.rect.setPosition(920, 180);
	resourceArray.push_back(resource1);
	resource1.resource5 = false;

	resource1.resource1 = false;
	resource1.resource2 = false;
	resource1.resource3 = false;
	resource1.resource4 = false;
	resource1.resource5 = false;
	resource1.resource6 = true;
	textureResource6.loadFromFile("res3.png");
	resource1.rect.setTexture(&textureResource6);
	resource1.rect.setPosition(630, 650);
	resourceArray.push_back(resource1);
	resource1.rect.setPosition(1350, 50);
	resourceArray.push_back(resource1);
	resource1.resource6 = false;
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Gerardo Player	Assigning Player Footstep Sounds
	if (!player.soundBuf.loadFromFile("foot.wav"))
		std::cout << "can't open sound file" << std::endl;
	player.sound.setBuffer(player.soundBuf);
	player.sound.setVolume(100);
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Cuong
	// Adding enemy texture type 1 Chasing At Beginning
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("enemySprite.png")) {
		return EXIT_FAILURE;
	}

	// Adding enemy texture type 2 chasing after get shot 
	sf::Texture textureEnemy2;
	if (!textureEnemy2.loadFromFile("enemySprite.png")) {
		return EXIT_FAILURE;
	}

	// Adding enemy texture type 3 cmove randomly - no chasing
	sf::Texture textureEnemy3;
	if (!textureEnemy3.loadFromFile("enemySprite.png")) {
		return EXIT_FAILURE;
	}

	vector<enemy>::const_iterator iter4;
	vector<enemy> enemyArray;  //type 1
	vector<enemy> enemyArray2; //type 2
	vector<enemy> enemyArray3; //type 3
	class enemy enemy1, enemy2, enemy3;

	//Cuong Locate enemies on the map   4/13
	//-------------------------------------------------------------------------------------------------------------------------

	// West Left map enemies - 3 enemies 
	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(-300, 500);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3

/*	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(-400, 700);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3
*/
	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(-500, 600);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3

	// South Bottom map enemies - 2 enemy
	enemy2.sprite.setTexture(textureEnemy2);
	enemy2.text.setFont(font);
	enemy2.text.setCharacterSize(15);
	enemy2.text.setFillColor(sf::Color::Red);
	enemy2.rect.setPosition(1000, 800);
	enemy2.spritexStart = 32 * 7;
	enemy2.spriteyStart = 32 * 0;
	enemyArray2.push_back(enemy2); // enemy type 2

	enemy2.sprite.setTexture(textureEnemy2);
	enemy2.text.setFont(font);
	enemy2.text.setCharacterSize(15);
	enemy2.text.setFillColor(sf::Color::Red);
	enemy2.rect.setPosition(600, 700);
	enemy2.spritexStart = 32 * 7;
	enemy2.spriteyStart = 32 * 0;
	enemyArray2.push_back(enemy2); // enemy type 2

	// East Right map enemies - 4 enemies
	enemy1.sprite.setTexture(textureEnemy);
	enemy1.text.setFont(font);
	enemy1.text.setCharacterSize(15);
	enemy1.text.setFillColor(sf::Color::Red);
	enemy1.rect.setPosition(1000, 700);
	enemy1.spritexStart = 32 * 10;
	enemy1.spriteyStart = 32 * 0;
	enemyArray.push_back(enemy1); // enemy type 1
/*
	enemy2.sprite.setTexture(textureEnemy2);
	enemy2.text.setFont(font);
	enemy2.text.setCharacterSize(15);
	enemy2.text.setFillColor(sf::Color::Red);
	enemy2.rect.setPosition(1000, 800);
	enemy2.spritexStart = 32 * 7;
	enemy2.spriteyStart = 32 * 0;
	enemyArray2.push_back(enemy2); // enemy type 2

	enemy1.sprite.setTexture(textureEnemy);
	enemy1.text.setFont(font);
	enemy1.text.setCharacterSize(15);
	enemy1.text.setFillColor(sf::Color::Red);
	enemy1.rect.setPosition(800, 300);
	enemy1.spritexStart = 32 * 10;
	enemy1.spriteyStart = 32 * 0;
	enemyArray.push_back(enemy1); // enemy type 1 
*/
	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(800, 300);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3

	// North map enemies - 2 enemies
	enemy2.sprite.setTexture(textureEnemy2);
	enemy2.text.setFont(font);
	enemy2.text.setCharacterSize(15);
	enemy2.text.setFillColor(sf::Color::Red);
	enemy2.rect.setPosition(300, 400);
	enemy2.spritexStart = 32 * 7;
	enemy2.spriteyStart = 32 * 0;
	enemyArray2.push_back(enemy2); // enemy type 2

	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(100, 400);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3

	// North upper map - 3 enemies
	enemy1.sprite.setTexture(textureEnemy);
	enemy1.text.setFont(font);
	enemy1.text.setCharacterSize(15);
	enemy1.text.setFillColor(sf::Color::Red);
	enemy1.rect.setPosition(450, -15);
	enemy1.spritexStart = 32 * 10;
	enemy1.spriteyStart = 32 * 0;
	enemyArray.push_back(enemy1); // enemy type 1 

	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(400, -10);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3
/*
	enemy3.sprite.setTexture(textureEnemy3);
	enemy3.text.setFont(font);
	enemy3.text.setCharacterSize(15);
	enemy3.text.setFillColor(sf::Color::Red);
	enemy3.rect.setPosition(450, -15);
	enemy3.spritexStart = 32 * 4;
	enemy3.spriteyStart = 32 * 0;
	enemyArray3.push_back(enemy3); // enemy type 3		
	*/							   
	//-----------------------------------------------------------------------------------------------------------------------------------------					  
								   /*
								   enemy1.sprite.setTexture(textureEnemy);
								   enemy1.rect.setPosition(700, 250); // enemy type 1
								   enemyArray.push_back(enemy1);

								   enemy2.sprite.setTexture(textureEnemy);
								   enemy2.rect.setPosition(1000, 260); // enemy type 1
								   enemyArray.push_back(enemy2);

								   enemy3.sprite.setTexture(textureEnemy);
								   enemy3.rect.setPosition(-400, 280); // enemy type 1

								   enemy1.sprite.setTexture(textureEnemy2);
								   enemy1.rect.setPosition(500, 260);
								   enemy1Array.push_back(enemy2);

								   enemy2.sprite.setTexture(textureEnemy2);
								   enemy2.rect.setPosition(400, 260);
								   enemy1Array.push_back(enemy2);

								   enemy1.sprite.setTexture(textureEnemy2);
								   enemy1.rect.setPosition(500, 260);
								   enemy1Array.push_back(enemy2);

								   enemy2.sprite.setTexture(textureEnemy2);
								   enemy2.rect.setPosition(400, 260);
								   enemy1Array.push_back(enemy2);
								   */

	//Cuong
	//projectile vector
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;
	class projectile projectile1;

	//Gerardo Attempting Tower Attacks 4/15
	//vector<Tower>::const_iterator tower_iter;
	//vector<Tower> t_projectileArray;
	//class Tower t_projectile;

	//vector<projectile>::const_iterator t_iter;
	//vector<projectile> t_projectileArray;
	//class projectile t_projectile;
	//---------------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------------
	//Gerardo Clock
	float deltaTime = 0.0f;
	sf::Clock clock;
	//if(music = 1) play
	cout << "Playing background music" << endl;
	audio.backgroundmusic1.play();
	audio.backgroundmusic1.setVolume(25);
	//---------------------------------------------------------------------------------------------------------------

	sf::Time elapsed1 = clock1.getElapsedTime();
	player.tower = 3;

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
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::P) {
					if (pausedgame > 0) {
						sf::sleep(sf::seconds(10));
						std::cout << "Game Paused" << std::endl;
						pausedgame -= 10;
					}
				}
				if (evnt.key.code == sf::Keyboard::Space) {
					if (player.gun == 1 && flag == 1) {
						if (player.ammo > 0) {
							audio.gunSound.play();
							std::cout << "playing gunshot " << std::endl;

							if (player.ammo == 0)
								player.ammo = 0;
							else
								player.ammo -= 1;
							std::cout << "ammo left: " << player.ammo << std::endl;
							if (elapsed1.asSeconds() >= 0.1)
							{
								clock1.restart();
								projectile1.rect.setPosition(player.body.getPosition().x + player.body.getSize().x / 2 - projectile1.rect.getSize().x / 2, player.body.getPosition().y + player.body.getSize().y / 2 - projectile1.rect.getSize().y / 2);
								projectile1.direction = player.direction;
								projectileArray.push_back(projectile1);
								std::cout << "space bar hit" << std::endl;
							}
							//Gerardo Tower Attack Speed
							if (tower_attack == 1) {
								tower_attack = 0;
							}
							else
								tower_attack++;
						}
						else {
							audio.gunEmptySound.play();
						}
					}
					else {
						std::cout << "!no gun equipped!" << std::endl;
					}
				}
				if (evnt.key.code == sf::Keyboard::H) {
					help ^= 1;
					cout << "Health: " << player.health << endl;
					cout << "Ammo  : " << player.ammo << endl;
					cout << "Tower : " << player.tower << endl;
					cout << "Tower1 : " << player.tower1 << endl;
					cout << "Tower2 : " << player.tower2 << endl;
					cout << "Tower3 : " << player.tower3 << endl;
				}
			}
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.key.code == sf::Mouse::Right)
				{
					//Gerardo 4/15
					//Have player have different towers to be placed
					//if player.tower == tower1;
					//if player.tower == tower2;

					//Gerardo 4/15
					//Make it so the player can only place towers when they have one
					//in inventory
					//and then place that tower with attacks down
					//tower1 = 1 attack
					//tower2 = 2 attacks
					//tower3 = 4 attacks

					std::cout << "player towers left" << player.tower << std::endl;
					sf::Vector2i positionTower = sf::Mouse::getPosition(window);
					//std::cout << "right click X(" << positionTower.x << ")" << std::endl;
					//std::cout << "right click Y(" << positionTower.y << ")" << std::endl;


					//Gerardo 4/15
					//Last changes, tower differentiality
					if (player.tower1 == 1) {
						//if (player.tower == 3)
						//{
						towers.active1 = 1;
						if (player.W == true) {
							graphics.tower1.setPosition(positionTower.x - 720.0f, positionTower.y);
							towers.rect.setPosition(positionTower.x - 720.0f, positionTower.y);
						}
						else if (player.SW == true) {
							graphics.tower1.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
							towers.rect.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
						}
						else if (player.S == true) {
							graphics.tower1.setPosition(positionTower.x, positionTower.y + 480.0f);
							towers.rect.setPosition(positionTower.x, positionTower.y + 480.0f);

						}
						else if (player.SE == true) {
							graphics.tower1.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);
							towers.rect.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);

						}
						else if (player.E == true) {
							graphics.tower1.setPosition(positionTower.x + 720.0f, positionTower.y);
							towers.rect.setPosition(positionTower.x + 720.0f, positionTower.y);

						}
						else if (player.N == true) {
							graphics.tower1.setPosition(positionTower.x, positionTower.y - 480.0f);
							towers.rect.setPosition(positionTower.x, positionTower.y - 480.0f);

						}
						else {
							graphics.tower1.setPosition(positionTower.x, positionTower.y);
							towers.rect.setPosition(positionTower.x, positionTower.y);

						}
						//player.tower--;
					}
					if (player.tower2 == 1) {
						//if (player.tower == 3)
						//{
						towers2.active2 = 1;
						if (player.W == true) {
							graphics.tower1.setPosition(positionTower.x - 720.0f, positionTower.y);
							towers2.rect.setPosition(positionTower.x - 720.0f, positionTower.y);
						}
						else if (player.SW == true) {
							graphics.tower1.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
							towers2.rect.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
						}
						else if (player.S == true) {
							graphics.tower1.setPosition(positionTower.x, positionTower.y + 480.0f);
							towers2.rect.setPosition(positionTower.x, positionTower.y + 480.0f);

						}
						else if (player.SE == true) {
							graphics.tower1.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);
							towers2.rect.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);

						}
						else if (player.E == true) {
							graphics.tower1.setPosition(positionTower.x + 720.0f, positionTower.y);
							towers2.rect.setPosition(positionTower.x + 720.0f, positionTower.y);

						}
						else if (player.N == true) {
							graphics.tower1.setPosition(positionTower.x, positionTower.y - 480.0f);
							towers2.rect.setPosition(positionTower.x, positionTower.y - 480.0f);

						}
						else {
							graphics.tower1.setPosition(positionTower.x, positionTower.y);
							towers2.rect.setPosition(positionTower.x, positionTower.y);

						}
						//player.tower--;
					}
					if (player.tower3 == 1) {
						//if (player.tower == 3)
						//{
						towers3.active3 = 1;
						if (player.W == true) {
							graphics.tower1.setPosition(positionTower.x - 720.0f, positionTower.y);
							towers3.rect.setPosition(positionTower.x - 720.0f, positionTower.y);
						}
						else if (player.SW == true) {
							graphics.tower1.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
							towers3.rect.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
						}
						else if (player.S == true) {
							graphics.tower1.setPosition(positionTower.x, positionTower.y + 480.0f);
							towers3.rect.setPosition(positionTower.x, positionTower.y + 480.0f);

						}
						else if (player.SE == true) {
							graphics.tower1.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);
							towers3.rect.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);

						}
						else if (player.E == true) {
							graphics.tower1.setPosition(positionTower.x + 720.0f, positionTower.y);
							towers3.rect.setPosition(positionTower.x + 720.0f, positionTower.y);

						}
						else if (player.N == true) {
							graphics.tower1.setPosition(positionTower.x, positionTower.y - 480.0f);
							towers3.rect.setPosition(positionTower.x, positionTower.y - 480.0f);

						}
						else {
							graphics.tower1.setPosition(positionTower.x, positionTower.y);
							towers3.rect.setPosition(positionTower.x, positionTower.y);

						}
						//player.tower--;
					}




					/*
					else if (player.tower == 2)
					{
					towers2.rect.setPosition(positionTower.x - 720.0f, positionTower.y);
					towers2.active2 = 1;

					if (player.W == true) {
					graphics.tower2.setPosition(positionTower.x - 720.0f, positionTower.y);
					}
					else if (player.SW == true) {
					graphics.tower2.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
					}
					else if (player.S == true) {
					graphics.tower2.setPosition(positionTower.x, positionTower.y + 480.0f);
					}
					else if (player.SE == true) {
					graphics.tower2.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);
					}
					else if (player.E == true) {
					graphics.tower2.setPosition(positionTower.x + 720.0f, positionTower.y);
					}
					else if (player.N == true) {
					graphics.tower2.setPosition(positionTower.x, positionTower.y - 480.0f);
					}
					else {
					graphics.tower2.setPosition(positionTower.x, positionTower.y);
					}
					player.tower--;
					}
					else if (player.tower == 1)
					{
					if (player.W == true) {
					graphics.tower3.setPosition(positionTower.x - 720.0f, positionTower.y);
					}
					else if (player.SW == true) {
					graphics.tower3.setPosition(positionTower.x - 720.0f, positionTower.y + 480.0f);
					}
					else if (player.S == true) {
					graphics.tower3.setPosition(positionTower.x, positionTower.y + 480.0f);
					}
					else if (player.SE == true) {
					graphics.tower3.setPosition(positionTower.x + 720.0f, positionTower.y + 480.0f);
					}
					else if (player.E == true) {
					graphics.tower3.setPosition(positionTower.x + 720.0f, positionTower.y);
					}
					else if (player.N == true) {
					graphics.tower3.setPosition(positionTower.x, positionTower.y - 480.0f);
					}
					else {
					graphics.tower3.setPosition(positionTower.x, positionTower.y);
					}
					player.tower--;
					std::cout << "Placing tower on x: " << positionTower.x << ",y: " << positionTower.y << std::endl;
					}
					*/
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			flag = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			if (player.gun == 1) {
				flag = 1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			//For debugging purposes ONLY
			player.ammo = 5;
			player.health = 30;
			player.tower = 3;
			player.gun = 1;
		}
		if (flag == 0)
		{
			playerTexture.loadFromFile("char_sprite_walk3.png");
		}
		else if (flag == 1)
		{
			playerTexture.loadFromFile("char_sprite_walk_gun_1.png");
		}

		//---------------------------------------------------------------------------------------------------------------
		//Cuong Enemy Wall Collision
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			int counter2 = 0;

			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{	//Hit wall
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


		//Enemy Wall Collision type 2
		counter = 0;
		for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
		{
			int counter2 = 0;

			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemyArray2[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{	//Hit wall
					if (enemyArray2[counter].direction == 1) //Up
					{
						enemyArray2[counter].faceUp = false;
						enemyArray2[counter].rect.move(0, 1);
					}
					else if (enemyArray2[counter].direction == 2) //Down
					{
						enemyArray2[counter].faceDown = false;
						enemyArray2[counter].rect.move(0, -1);
					}
					else if (enemyArray2[counter].direction == 3) //Left
					{
						enemyArray2[counter].faceLeft = false;
						enemyArray2[counter].rect.move(1, 0);
					}
					else if (enemyArray2[counter].direction == 4) //Right
					{
						enemyArray2[counter].faceRight = false;
						enemyArray2[counter].rect.move(-1, 0);
					}
					else
					{
					}
				}
				counter2++;
			}
			counter++;
		}

		//Enemy type 3 Wall Collision      4/19
		counter = 0;
		for (iter4 = enemyArray3.begin(); iter4 != enemyArray3.end(); iter4++)
		{
			int counter2 = 0;
			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (enemyArray3[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{	//Hit wall
					if (enemyArray3[counter].direction == 1) //Up
					{
						enemyArray3[counter].faceUp = false;
						enemyArray3[counter].rect.move(0, 1);
					}

					else if (enemyArray3[counter].direction == 2) //Down
					{
						enemyArray3[counter].faceDown = false;
						enemyArray3[counter].rect.move(0, -1);
					}

					else if (enemyArray3[counter].direction == 3) //Left
					{
						enemyArray3[counter].faceLeft = false;
						enemyArray3[counter].rect.move(1, 0);
					}

					else if (enemyArray3[counter].direction == 4) //Right
					{
						enemyArray3[counter].faceRight = false;
						enemyArray3[counter].rect.move(-1, 0);
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

		window.setView(player.view);

		//Miguel ---------------------------------------------------------------------------------------------------------------
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

		//Collision with Resources
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++) {
			if (player.body.getGlobalBounds().intersects(resourceArray[counter].rect.getGlobalBounds()))
			{
				//Hit Resource
				if (resourceArray[counter].resource1 == true) //resource 1
				{
					player.health += 1;
					if (player.health >= player.maxHealth)
					{
						player.health = player.maxHealth;
					}
					cout << "health: " << player.health << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource2 == true) //resource 2
				{
					player.ammo += 1;
					cout << "ammo: " << player.ammo << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource3 == true) //resource 3
				{
					audio.gunPickupSound.play();
					player.gun = 1;
					player.tower2 = 1;
					cout << "gun: " << player.gun << endl;
					cout << "tower1: " << player.tower2 << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource4 == true) //resource 4
				{
					audio.gunPickupSound.play();
					player.tower1 = 1;
					cout << "tower1: " << player.tower1 << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource5 == true) //resource 5
				{
					audio.gunPickupSound.play();
					player.tower3 = 1;
					cout << "tower3: " << player.tower3 << endl;
					resourceArray[counter].gathered = true;
				}
				if (resourceArray[counter].resource6 == true) //resource 6
				{
					player.ammo += 2;
					player.health += 1.5;
					resourceArray[counter].gathered = true;
				}
			}
			counter++;
		}
		//Remove Resource
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			if (resourceArray[counter].gathered == true)
			{
				resourceArray.erase(resourceit);  //clear() removes all
				break;
			}
			counter++;
		}
		//end---------------------------------------------------------------------------------------------------------------




		//Player shaded area location
		int temp = player.playerposx;
		int temp2 = player.playerposy;
		graphics.playerShade.setPosition(temp - 950.0f, temp2 - 520.0f);

		//if (player.ammo < 3)
		//	graphics.playerShadeTexture.loadFromFile("shade_black_big.png");


		//Instead have onely 1 towers class?
		//Towers shoot different directions
		//Gerardo Tower Attacks 4/15
		//player.tower2 = 1;
		//player.tower3 = 1;
		//player.tower1 = 1;

		if (tower_attack == 1) {
			if (towers.active1 == 1) {
				towers.direction = player.direction;
				projectileArray.push_back(towers);
			}

			if (towers2.active2 == 1) {
				towers2.direction = player.direction;
				projectileArray.push_back(towers2);

				//if player.direction 1
				//	then direction = 2

				if (player.direction == 1)
					towers2.direction = 3;
				else if (player.direction == 2)
					towers2.direction = 3;
				else if (player.direction == 3)
					towers2.direction = 2;
				else
					towers2.direction = 2;
				//towers2.direction = 3;
				projectileArray.push_back(towers2);
			}

			if (towers3.active3 == 1) {

				towers3.direction = player.direction;
				projectileArray.push_back(towers3);

				towers3.direction = 1;
				projectileArray.push_back(towers3);

				towers3.direction = 4;
				projectileArray.push_back(towers3);

			}

			tower_attack = 0;
		}


		player.Update(deltaTime);
		window.clear(sf::Color(125, 125, 125));

		//Drawing Backgrounds
		window.draw(graphics.background);
		window.draw(graphics.background2);
		window.draw(graphics.background3);
		window.draw(graphics.background4);
		window.draw(graphics.background6);
		window.draw(graphics.background7);


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

		//Miguel	4/2/17  
		window.draw(wall0.sprite);
		window.draw(graphics.backgroundTree);
		window.draw(graphics.backgroundExitBottom);
		window.draw(graphics.backgroundExitTop);
		window.draw(graphics.backgroundExitTop2);

		//Cuong Enemy Vector Array
		sf::Time elapsed2 = clock2.getElapsedTime();
		sf::Time elapsed3 = clock3.getElapsedTime();
		sf::Time elapsed4 = clock4.getElapsedTime();

		// Enemy type 1 Chasing (AI) at Beginning (Boss)
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].chase == true)
				if (elapsed2.asSeconds() >= 0.5) //Changed to .5 on 04/01
				{
					clock2.restart();
					int tempRand = generateRandom(3);
					//Added 04/01
					if (tempRand == 1) // Enemy Chases Player
					{
						projectile1.attackDamage = enemyArray[counter].attackDamage;
					}
					if (tempRand == 2)
					{
						if (player.body.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
						else if (player.body.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
					}
					else // Enemy Chases Player
					{
						if (player.body.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
						else if (player.body.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;						
						}
					}
				}
			counter++;
		}

		//---------------------------------------------------------------------------
		// Enemy type 2 Chasing (AI) if get shot
		counter = 0;
		for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
		{
			if (elapsed3.asSeconds() >= 0.5) //Changed to .5 on 04/01
			{
				if (enemyArray2[counter].aggroed == true)
				{
					clock3.restart();
					int tempRand = generateRandom(3);
					//Added 04/01
					if (tempRand == 1) // Enemy Chases Player
					{
						projectile1.attackDamage = enemyArray2[counter].attackDamage;
					}
					if (tempRand == 2)
					{
						if (player.body.getPosition().y < enemyArray2[counter].rect.getPosition().y)
						{
							enemyArray2[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray2[counter].rect.getPosition().y)
						{
							enemyArray2[counter].direction = 2;
						}
						else if (player.body.getPosition().x < enemyArray2[counter].rect.getPosition().x)
						{
							enemyArray2[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray2[counter].rect.getPosition().x)
						{
							enemyArray2[counter].direction = 4;
						}
					}
					else // Enemy Chases Player
					{
						if (player.body.getPosition().x < enemyArray2[counter].rect.getPosition().x)
						{
							enemyArray2[counter].direction = 3;
						}
						else if (player.body.getPosition().x > enemyArray2[counter].rect.getPosition().x)
						{
							enemyArray2[counter].direction = 4;
						}
						else if (player.body.getPosition().y < enemyArray2[counter].rect.getPosition().y)
						{
							enemyArray2[counter].direction = 1;
						}
						else if (player.body.getPosition().y > enemyArray2[counter].rect.getPosition().y)
						{
							enemyArray2[counter].direction = 2;
						}
					}
				}
			}
			counter++;
		}

		// Enemy type 3 Movement Randomly     4-19
		//Cuong
		//Projectiles colliding with enemies type 1  3/31
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds()))
				{
					cout << "bullet collision with enemy" << endl;
					projectileArray[counter].destroy = true;
					enemyArray[counter2].hp -= projectileArray[counter].attackDamage;
					if (enemyArray[counter2].hp <= 0)
					{
						enemyArray[counter2].alive = false;
					}
					// Chasing
					enemyArray[counter2].chase = true;

				}

				counter2++;

			}
			counter++;
		}
		//--------------------------------------------------------------------------------------------------------------------

		//Cuong
		//Projectiles colliding with enemies type 2 
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray2[counter2].rect.getGlobalBounds()))
				{
					cout << "bullet collision with enemy" << endl;
					projectileArray[counter].destroy = true;
					enemyArray2[counter2].hp2 -= projectileArray[counter].attackDamage;
					if (enemyArray2[counter2].hp2 <= 0)
					{
						enemyArray2[counter2].alive = false;
					}
					// Chasing
					enemyArray2[counter2].aggroed = true;
				}
				counter2++;
			}
			counter++;
		}

		//Projectiles colliding with enemies type 3     4/19
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (iter4 = enemyArray3.begin(); iter4 != enemyArray3.end(); iter4++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray3[counter2].rect.getGlobalBounds()))
				{
					cout << "bullet collision with enemy" << endl;
					projectileArray[counter].destroy = true;
					enemyArray3[counter2].hp3 -= projectileArray[counter].attackDamage;
					if (enemyArray3[counter2].hp3 <= 0)
					{
						enemyArray3[counter2].alive = false;
					}
				}
				counter2++;
			}
			counter++;
		}

		//-------------------------------------------------------------------------------------------------------
		//Miguel					4/7/17
		//Enemy Player Collision
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (player.body.getGlobalBounds().intersects(enemyArray[counter].rect.getGlobalBounds()))
			{
				player.health -= enemy1.enemyAttackDamage1;
				if (player.health <= 0) {
					player.health = 0;
				}
				cout << "Enemy1 attacked Player by: " << player.health << " damage!" << endl;
			}
			counter++;
		}

		counter = 0;
		for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
		{
			if (player.body.getGlobalBounds().intersects(enemyArray2[counter].rect.getGlobalBounds()))
			{
				player.health -= enemy2.enemyAttackDamage2;
				if (player.health <= 0) {
					player.health = 0;
				}
				cout << "Enemy2 attacked Player" << player.health << " damage!" << endl;
			}
			counter++;
		}

		counter = 0;            //4/19
		for (iter4 = enemyArray3.begin(); iter4 != enemyArray3.end(); iter4++)
		{
			if (player.body.getGlobalBounds().intersects(enemyArray3[counter].rect.getGlobalBounds()))
			{
				player.health -= enemy2.enemyAttackDamage3;
				if (player.health <= 0) {
					player.health = 0;
				}
				cout << "Enemy3 attacked Player" << player.health << " damage!" << endl;
			}
			counter++;
		}

		//Cuong
		//Projectile Wall Collision
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			counter2 = 0;
			for (wallit = wallArray.begin(); wallit != wallArray.end(); wallit++)
			{
				if (projectileArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
				{
					cout << "bullet collision with wall" << endl;
					projectileArray[counter].destroy = true;
				}
				counter2++;
			}
			counter++;
		}

		//Cuong
		// Delete Dead Enemy type 1
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			if (enemyArray[counter].alive == false)
			{
				player.score += 500;
				totalScore.str("");
				totalScore << "Score: " << player.score;
				textScore.setString(totalScore.str());
				textScore2.setString(totalScore.str());
				textScore3.setString(totalScore.str());
				textScore4.setString(totalScore.str());
				textScore5.setString(totalScore.str());
				textScore6.setString(totalScore.str());
				textScore7.setString(totalScore.str());
				cout << "Enemy1 was killed" << endl;
				enemyArray.erase(iter4);
				break;
			}
			counter++;
		}

		// Delete Dead Enemy type 2
		counter = 0;
		for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
		{
			if (enemyArray2[counter].alive == false)
			{
				player.score += 300;
				totalScore.str("");
				totalScore << "Score: " << player.score;
				textScore.setString(totalScore.str());
				textScore2.setString(totalScore.str());
				textScore3.setString(totalScore.str());
				textScore4.setString(totalScore.str());
				textScore5.setString(totalScore.str());
				textScore6.setString(totalScore.str());
				textScore7.setString(totalScore.str());
				cout << "Enemy2 was killed" << endl;
				enemyArray2.erase(iter4);
				break;
			}
			counter++;
		}

		// Delete Dead Enemy type 3     4/19
		counter = 0;
		for (iter4 = enemyArray3.begin(); iter4 != enemyArray3.end(); iter4++)
		{
			if (enemyArray3[counter].alive == false)
			{
				player.score += 100;
				totalScore.str("");
				totalScore << "Score: " << player.score;
				textScore.setString(totalScore.str());
				textScore2.setString(totalScore.str());
				textScore3.setString(totalScore.str());
				textScore4.setString(totalScore.str());
				textScore5.setString(totalScore.str());
				textScore6.setString(totalScore.str());
				textScore7.setString(totalScore.str());
				cout << "Enemy3 was killed" << endl;
				enemyArray3.erase(iter4);
				break;
			}
			counter++;
		}

		//Cuong
		// Delete Projectile
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			if (projectileArray[counter].destroy == true)
			{
				cout << "projectile deleted" << endl;
				projectileArray.erase(iter);
				break;
			}
			counter++;
		}

		//Cuong
		// Draw Projectiles
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
		{
			projectileArray[counter].update(); // Update Projectile
			window.draw(projectileArray[counter].rect);
			counter++;
		}

		//Cuong
		// Draw Enemies type 1
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].update();
			enemyArray[counter].updateMovement();
			window.draw(enemyArray[counter].sprite);
			counter++;
		}

		// hp
		counter = 0;
		for (iter4 = enemyArray.begin(); iter4 != enemyArray.end(); iter4++)
		{
			enemyArray[counter].text.setString("blood " + to_string(enemyArray[counter].hp) + "/" + to_string(enemyArray[counter].maxhp1));
			window.draw(enemyArray[counter].text);
			counter++;
		}

		//Cuong		
		//Draw Enemies type 2  
		counter = 0;
		for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
		{
			enemyArray2[counter].update();
			enemyArray2[counter].updateMovement();
			window.draw(enemyArray2[counter].sprite);
			counter++;
		}

		counter = 0;
		for (iter4 = enemyArray2.begin(); iter4 != enemyArray2.end(); iter4++)
		{
			enemyArray2[counter].text.setString("blood " + to_string(enemyArray2[counter].hp2) + "/" + to_string(enemyArray2[counter].maxhp2));
			window.draw(enemyArray2[counter].text);
			counter++;
		}

		//Cuong		  4/19
		//Draw Enemies type 3  
		counter = 0;
		for (iter4 = enemyArray3.begin(); iter4 != enemyArray3.end(); iter4++)
		{
			enemyArray3[counter].update();
			enemyArray3[counter].updateMovement();
			window.draw(enemyArray3[counter].sprite);
			counter++;
		}

		counter = 0;
		for (iter4 = enemyArray3.begin(); iter4 != enemyArray3.end(); iter4++)
		{
			enemyArray3[counter].text.setString("blood " + to_string(enemyArray3[counter].hp3) + "/" + to_string(enemyArray3[counter].maxhp3));
			window.draw(enemyArray3[counter].text);
			counter++;
		}
		//-------------------------------------------------------------------------------------------------------------

		//Miguel Draw Resources
		counter = 0;
		for (resourceit = resourceArray.begin(); resourceit != resourceArray.end(); resourceit++)
		{
			resourceArray[counter].update();
			window.draw(resourceArray[counter].rect);
			window.draw(resourceArray[counter].sprite);
			counter++;
		}

		//Draw Trees
		window.draw(graphics.backgroundTree);
		window.draw(graphics.backgroundTree2);
		window.draw(graphics.backgroundTree3);
		window.draw(graphics.backgroundTree4);
		window.draw(graphics.backgroundTree5);
		window.draw(graphics.backgroundTree6);
		window.draw(graphics.backgroundTree7);
		window.draw(graphics.backgroundTree8);

		//Drawing Towers
		window.draw(graphics.tower1);
		window.draw(graphics.tower2);
		window.draw(graphics.tower3);

		//Drawing player shade region
		window.draw(graphics.playerShade);

		//Miguel draw Health Bar		4/2/17-4/7/17
		window.draw(text);
		help == 0 ? window.draw(textHelp) : window.draw(textHelp2);

		for (int j = 0; j < 7; j++) {
			if (player.health > 4)
				window.draw(spriteHealth[5][j]);
			else if (player.health <= 4 && player.health > 3)
				window.draw(spriteHealth[4][j]);
			else if (player.health <= 3 && player.health > 2)
				window.draw(spriteHealth[3][j]);
			else if (player.health <= 2 && player.health > 1)
				window.draw(spriteHealth[2][j]);
			else if (player.health <= 1 && player.health > 0)
				window.draw(spriteHealth[1][j]);
			else
				window.draw(spriteHealth[0][j]);
		}
		window.draw(textScore);
		window.draw(textScore2);
		window.draw(textScore3);
		window.draw(textScore4);
		window.draw(textScore5);
		window.draw(textScore6);
		window.draw(textScore7);

		//displaying Escape Menu
		if (exitgame == 1) window.draw(graphics.menuImage);
		else	graphics.menuImage.setTexture(&graphics.menuTexture);

		window.display();
	}
	return 0;
}


