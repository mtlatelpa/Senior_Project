#include "Entity.h"
#include "Random.h"

class Enemy : public Entity
{
public:
	//float movementSpeed = 0.5; //slower
	int movementSpeed = 1;
	int movementLength = 100; //50 move shorter
	int attackDamage = 2;
	int counterWalking = 0;
	int direction = 0; // 1 - up, 2 - down, 3 - left, 4 - right
	int counter = 0;
	// Add for collision with wall
	bool faceRight = true;
	bool faceLeft = true;
	bool faceUp = true;
	bool faceDown = true;

	// Add for chasing AI
	bool chase = true;

	Enemy();
	void update();
	void updateMovement();
};